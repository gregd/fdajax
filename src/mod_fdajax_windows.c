#include "mod_fdajax_defs.h"

win_info_p window_init(plugin_data *p, connection *con, user_info_p user, user_request_p req, enum fda_win_type win_type, int slot)
{
    struct timeval now, back, from_point;
    unsigned int bits;
    win_info_p win;
    size_t i;

    win = calloc(1, sizeof(win_info_t));
    if (!win) {
        return NULL;
    }
    win->win_id =   req->win_id;
    win->win_st =   req->win_st;
    win->www_id =   req->www_id;
    win->win_type = win_type;
    win->owner =    user;
    user->windows[slot] = win;
    win->con =      con;
    win->to_send =  NULL;
    win->send_count = 0;
    win->last_alert = 0;

    gettimeofday(&now, 0);
    win->created_at = now;
    if (req->tv.tv_sec > 0) {
        from_point = req->tv;
    } else {
        from_point = now;
        back.tv_sec = 1;
        back.tv_usec = 0;
        timeval_sub(from_point, back);
    }
    win->last_send = from_point;

    win->ev = req->ev;
    for (i = 0; i < FDA_TYPES_MAX; i++) {
        win->last_mes_at[i] = from_point;
    }

    for (i = FDA_GRP_START; i < FDA_GRP_END; i++) {
        bits = g_ev_mask_by_index[i];
        if (win->ev.types & bits) {
            group_add_window(group_find(p, bits), win);
        }
    }

    return win;
}

void window_free(plugin_data *p, win_info_p win)
{
    unsigned int bits;
    int i;

    for (i = FDA_GRP_START; i < FDA_GRP_END; i++) {
        bits = g_ev_mask_by_index[i];
        if (win->ev.types & bits) {
            group_rm_window(group_find(p, bits), win);
        }
    }

    free(win);
}

int window_find_slot(user_info_p user)
{
    int i;
    for (i = 0; i < WINDOWS_MAX; i++) {
        if (NULL == user->windows[i]) {
            return i;
        }
    }
    return -1;
}

win_info_p window_find(connection *con, user_info_p user, user_request_p req)
{
    size_t i;

    UNUSED(con);
    for (i = 0; i < WINDOWS_MAX; i++) {
        if (user->windows[i] && (req->win_id == user->windows[i]->win_id)) {
            assert(user->windows[i]->owner == user);
            return user->windows[i];
        }
    }
    return FALSE;
}

void window_close_all(server *srv, plugin_data *p, connection *con, user_info_p user)
{
    win_info_p win;
    size_t i;

    for (i = 0; i < WINDOWS_MAX; i++) {
        win = user->windows[i];
        if (win) {
            log_avg(srv, __FILE__, __LINE__, "ssdsd", (con == NULL) ? "0.0.0.0" : con->dst_addr_buf->ptr, "close_win uid ",
                    user->user_id, " win_id ", win->win_id);
            if (win->con) {
                if (0 == win->con->file_finished) {
                    con_set_response(srv, p, win->con, p->js_logout_code, win->win_st);
                }
                win->con->plugin_ctx[p->id] = NULL;
            }
            window_free(p, win);
            user->windows[i] = NULL;
        }
    }
}

void window_close(server *srv, plugin_data *p, user_info_p user, win_info_p win, buffer *close_message)
{
    size_t i;

    for (i = 0; i < WINDOWS_MAX; i++) {
        if (user->windows[i] && (win->win_id == user->windows[i]->win_id)) {
            if (win->con) {
                if (0 == win->con->file_finished) {
                    con_set_response(srv, p, win->con, close_message ? close_message : p->js_logout_code, win->win_st);
                }
                win->con->plugin_ctx[p->id] = NULL;
            }
            window_free(p, win);
            user->windows[i] = NULL;
            return;
        }
    }
}

int window_remove_old(server *srv, plugin_data *p, connection *con, user_info_p user)
{
    struct timeval now;
    size_t i;
    int left_count = 0;

    gettimeofday(&now, NULL);
    UNUSED(srv);
    UNUSED(p);

    for (i = 0; i < WINDOWS_MAX; i++) {
        if (NULL == user->windows[i]) {
            continue;
        }
        if (NULL != user->windows[i]->con) {
            if (!is_tcp_socket_open(srv, p, user->windows[i]->con)) {
                /* remote side has closed connection */
                connection *dcon = user->windows[i]->con;
                log_avg(srv, __FILE__, __LINE__, "bsdss", con->dst_addr_buf, "rm_ow closed win_id", user->windows[i]->win_id,
                        "c_at", tv2s(user->windows[i]->created_at));
                dcon->plugin_ctx[p->id] = NULL;
                connection_set_state(srv, dcon, CON_STATE_ERROR);
                joblist_append(srv, dcon);
                window_free(p, user->windows[i]);
                user->windows[i] = NULL;
            } else {
                left_count++;
            }
        } else {
            if (window_is_old(user->windows[i], now, p->win_timeout)) {
                window_free(p, user->windows[i]);
                user->windows[i] = NULL;
            } else {
                left_count++;
            }
        }
    }
    return left_count;
}

void window_update_last_send(win_info_p win, struct timeval tv)
{
    if (timeval_less(win->last_send, tv)) {
        win->last_send = tv;
    }
}

int window_is_old(win_info_p win, struct timeval now, unsigned long win_timeout)
{
    double diff = ((now.tv_sec - win->last_send.tv_sec) * 1000000) + now.tv_usec - win->last_send.tv_usec;
    return (diff > win_timeout) ? TRUE : FALSE;
}

buffer *window_get_buffer(win_info_p win)
{
    if (NULL == win->to_send) {
        win->to_send = buffer_init();
        buffer_prepare_append(win->to_send, 4096);
    }
    return win->to_send;
}

void window_append_string_buffer(win_info_p win, buffer *sb)
{
    buffer_append_string_buffer(window_get_buffer(win), sb);
}

void window_append_string(win_info_p win, char *s)
{
    buffer_append_string(window_get_buffer(win), s);
}

win_info_p window_first_with_unw(server *srv, plugin_data *p, user_info_p user)
{
    win_info_p win;
    int i;

    UNUSED(srv);
    UNUSED(p);
    for(i = 0; i < WINDOWS_MAX; i++) {
        win = user->windows[i];
        if (NULL != win && NULL != win->con && (win->ev.types & FDA_EV_UNW) != 0) {
            return win;
        }
    }
    return NULL;
}

int window_can_receive(win_info_p win, mes_info_p mes, int check_time)
{
    int ev_nr;

    if (mes->ev.types & win->ev.types) {
        ev_nr = event_bit_to_index(mes->ev.types);
        if (check_time && (!timeval_less(win->last_mes_at[ev_nr], mes->created_at))) {
            return FALSE;
        }
        if (event_check_ids(win, mes, ev_nr)) {
            return TRUE;
        }
    }
    return FALSE;
}

int window_check_groups(server *srv, plugin_data *p, win_info_p win)
{
    unsigned int bits;
    grp_info_p grp;
    int i;

    for (i = FDA_GRP_START; i < FDA_GRP_END; i++) {
        bits = g_ev_mask_by_index[i];
        if (win->ev.types & bits) {
            grp = group_find(p, bits);
            message_send_pending(srv, p, grp->mes_list.first_mes, win);
        }
    }
    return 0;
}

int window_flush_all(server *srv, plugin_data *p, user_info_p user)
{
    int i;

    for(i = 0; i < WINDOWS_MAX; i++) {
        if (NULL != user->windows[i]) {
            window_flush(srv, p, user->windows[i]);
        }
    }
    return 0;
}

int window_flush(server *srv, plugin_data *p, win_info_p win)
{
    struct timeval now;
    buffer *b;

    if (NULL == win->con || NULL == win->to_send) {
        return FALSE;
    }
    switch (win->win_type) {
    case fda_win_chunked:
        con_set_response(srv, p, win->con, win->to_send, win->win_st);
        break;

    case fda_win_stream:
        b = chunkqueue_get_append_buffer(win->con->write_queue);
        if (1 == win->win_st) {
            BUFFER_APPEND_STRING_CONST(b, SCRIPT_JS_BEGIN);
        }
        buffer_append_string_buffer(b, win->to_send);
        if (1 == win->win_st) {
            buffer_append_nl(b);
            BUFFER_APPEND_STRING_CONST(b, SCRIPT_JS_END);
        }
        http_chunk_append_mem(srv, win->con, NULL, 0);
        joblist_append(srv, win->con);
        break;
    }
    buffer_free(win->to_send);
    win->to_send = NULL;
    gettimeofday(&now, 0);
    window_update_last_send(win, now);
    win->send_count++;
    win->owner->send_count++;

    return TRUE;
}

win_info_p window_find_oldest(user_info_p user)
{
    win_info_p win;
    int j, i = 0;

    while (i < WINDOWS_MAX && NULL == (win = user->windows[i])) {
        i++;
    }
    if (NULL == win) {
        return NULL;
    }
    for (j = i + 1; j < WINDOWS_MAX; j++) {
        if (user->windows[j]) {
            if (timeval_less(user->windows[j]->created_at, win->created_at)) {
                win = user->windows[j];
            }
        }
    }
    return win;
}

int window_should_redirect(server *srv, plugin_data *p, connection *con, user_info_p user, user_request_p req)
{
    char slot[WINDOWS_MAX] = { 1, 1, 1, 1, 1 };
    win_info_p oldest_win;
    size_t i, j;
    int redir = 0, redir_to = -1;

    UNUSED(con);
    for (i = 0; i < WINDOWS_MAX; i++) {
        if (user->windows[i]) {
            slot[user->windows[i]->www_id] = 0;
            if (req->www_id == user->windows[i]->www_id) {
                if (p->send_redirects && (0 == req->force_old_close)) {
                    redir = 1;
                } else {
                    window_close(srv, p, user, user->windows[i], p->js_maxwin_code);
                    return -1;
                }
            }
        }
    }
    if (!redir) {
        return -1;
    }
    for (j = 0; j < WINDOWS_MAX; j++) {
        if (slot[j]) {
            redir_to = j;
            break;
        }
    }
    if (-1 == redir_to) {
        oldest_win = window_find_oldest(user);
        redir_to = oldest_win->www_id;
        window_close(srv, p, user, oldest_win, p->js_maxwin_code);
        if (redir_to == req->www_id) {
            /* No need to redirect. The new window has the same win id. */
            return -1;
        }
    }
    return redir_to;
}
