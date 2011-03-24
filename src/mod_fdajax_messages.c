#include "mod_fdajax_defs.h"

mes_info_p message_init(user_request_p req)
{
    mes_info_p mes = malloc(sizeof(mes_info_t));

    if (!mes) {
        return NULL;
    }
    mes->mes = req->mes;
    req->mes = NULL;
    gettimeofday(&mes->created_at, NULL);
    mes->next = NULL;
    mes->prev = NULL;
    mes->send_count = 0;
    mes->to_remove = 0;
    mes->amode = req->amode;
    mes->ev = req->ev;
    return mes;
}

mes_info_p message_init_peer(server *srv, plugin_data *p, user_info_p user, user_request_p req)
{
    int cs, ev_nr;
    buffer *js_call;
    mes_info_p mes = malloc(sizeof(mes_info_t));

    UNUSED(srv);
    if (!mes) {
        return NULL;
    }
    gettimeofday(&mes->created_at, NULL);
    mes->next = NULL;
    mes->prev = NULL;
    mes->mes = NULL;
    mes->send_count = 0;
    mes->to_remove = 0;
    mes->amode = req->amode;

    mes->ev = req->ev;
    if (req->ev.count != 1 || (mes->ev.types & p->allow_peer_call_mask) == 0) {
        message_free(mes);
        return NULL;
    }
    ev_nr = event_bit_to_index(req->ev.types);
    if (ev_nr < FDA_GRP_START && mes->ev.ids_len[ev_nr] != 1) {
        message_free(mes);
        return NULL;
    }

    /* check posted params syntax */
    mod_fdajax_cinit(&cs);
    mod_fdajax_cexec(&cs, req->mes->ptr, req->mes->used - 1);
    if (mod_fdajax_cfinish(&cs) < 1) {
        message_free(mes);
        return NULL;
    }

    /* build js function call */
    js_call = buffer_init();
    buffer_prepare_append(js_call, 32 + p->js_peer_func->used + req->mes->used);
    if (ev_nr < FDA_GRP_START) {
        buffer_copy_string_buffer(js_call, p->js_peer_func);
    } else {
        buffer_copy_string_buffer(js_call, p->js_grp_peer_func);
    }
    buffer_append_string(js_call, "(");
    buffer_append_long(js_call, user->user_id);
    buffer_append_string(js_call, ",\"");
    buffer_append_string(js_call, g_ev_name_by_index[ev_nr]);
    buffer_append_string(js_call, "\",");
    if (ev_nr < FDA_GRP_START) {
        buffer_append_long(js_call, mes->ev.ids[ev_nr][0]);
        buffer_append_string(js_call, ",");
    }
    buffer_append_string_buffer(js_call, req->mes);
    buffer_append_string(js_call, ");");
    mes->mes = js_call;
    user->send_peer_count++;
    return mes;
}

void message_free(mes_info_p mes)
{
    if (mes->mes) {
        buffer_free(mes->mes);
    }
    free(mes);
}

void message_list_init(mes_list_p list)
{
    list->first_mes = list->last_mes = NULL;
}

void message_attach(mes_list_p list, mes_info_p mes)
{
    if (NULL == list->first_mes) {
        list->first_mes = list->last_mes = mes;
        return;
    }
    assert(NULL != list->last_mes);
    list->last_mes->next = mes;
    mes->prev = list->last_mes;
    list->last_mes = mes;
}

void message_detach(mes_list_p list, mes_info_p mes)
{
    if (list->first_mes == mes) { list->first_mes = mes->next; }
    if (list->last_mes == mes)  { list->last_mes = mes->prev; }
    if (mes->next)              { mes->next->prev = mes->prev; }
    if (mes->prev)              { mes->prev->next = mes->next; }
    mes->next = mes->prev = NULL;
}


void message_remove_all(mes_list_p list)
{
    mes_info_p pm2, pm = list->first_mes;

    while (pm) {
        pm2 = pm->next;
        message_free(pm);
        pm = pm2;
    }
    list->first_mes = list->last_mes = NULL;
}

int message_is_old(mes_info_p mes, struct timeval now, int mes_live_max)
{
    double diff = ((now.tv_sec - mes->created_at.tv_sec) * 1000000) + now.tv_usec - mes->created_at.tv_usec;
    return (diff > mes_live_max) ? TRUE : FALSE;
}

void message_remove_old(server *srv, plugin_data *p, mes_list_p list)
{
    struct timeval now;
    mes_info_p mes, next;

    UNUSED(srv);
    gettimeofday(&now, NULL);

    mes = list->first_mes;
    while (mes) {
        if (mes->to_remove || message_is_old(mes, now, p->mes_live_max)) {
            next = mes->next;
            message_detach(list, mes);
            message_free(mes);
            mes = next;
        } else {
            mes = mes->next;
        }
    }
}

int message_append_to_win(server *srv, plugin_data *p, win_info_p win, mes_info_p mes, int ev_index, int nl)
{
    buffer *buf = window_get_buffer(win);
    UNUSED(srv);
    UNUSED(p);

    win->last_mes_at[ev_index] = mes->created_at;
    mes->send_count++;
    if (nl) {
        buffer_append_nl(buf);
    }
    buffer_append_string_buffer(buf, mes->mes);
    return 1;
}

int message_append_as_unwanted(server *srv, plugin_data *p, win_info_p win, mes_info_p mes)
{
    buffer *buf = window_get_buffer(win);

    buffer_append_nl(buf);
    buffer_append_string_buffer(buf, p->unw_prefix);
    message_append_to_win(srv, p, win, mes, FDA_EV_UNW_INDEX, 0);
    return TRUE;
}

enum cmd_res_t message_send_pending(server *srv, plugin_data *p, mes_info_p mes, win_info_p win)
{
    while (mes) {
        if (window_can_receive(win, mes, TRUE)) {
            message_append_to_win(srv, p, win, mes, event_bit_to_index(mes->ev.types), 1);
            if (!p->merge_messages) {
                break;
            }
        }
        mes = mes->next;
    }

    return cmdr_ok;
}

int message_handle_unsend(server *srv, plugin_data *p, user_info_p user, mes_info_p mes, win_info_p recv_win)
{
    win_info_p win;
    size_t i;

    if (0 < mes->send_count) {
        return 0;
    }

    for(i = 0; i < WINDOWS_MAX; i++) {
        if (NULL != user->windows[i]) {
            if (window_can_receive(user->windows[i], mes, FALSE)) {
                return 0;
            }
        }
    }

    switch (mes->amode) {
    case 0:
        alert_add_from_mes(srv, p, user, mes);
        mes->to_remove = 1;
        break;

    case 1:
        if (NULL == recv_win) {
            win = window_first_with_unw(srv, p, user);
        } else {
            win = recv_win;
        }
        if (NULL != win) {
            message_append_as_unwanted(srv, p, win, mes);
        }
        break;

    case 2:
    default:
        mes->to_remove = 1;
        break;
    }

    return 1;
}

int message_check_unsend(server *srv, plugin_data *p, user_info_p user, win_info_p recv_win)
{
    mes_info_p mes;

    UNUSED(srv);
    UNUSED(p);

    mes = user->mes_list.first_mes;
    while (mes) {
        if (mes->send_count == 0) {
            message_handle_unsend(srv, p, user, mes, recv_win);
        }
        mes = mes->next;
    }

    return 0;
}

enum gdc_cmd_t message_push(server *srv, plugin_data *p, user_info_p user, mes_info_p mes)
{
    win_info_p win;
    size_t i;

    message_attach(&(user->mes_list), mes);

    for(i = 0; i < WINDOWS_MAX; i++) {
        win = user->windows[i];
        if (NULL == win || NULL == win->con) {
            continue;
        }
        message_send_pending(srv, p, user->mes_list.first_mes, win);
    }

    if (0 == mes->send_count) {
        message_handle_unsend(srv, p, user, mes, NULL);
    }

    return cmdr_ok;
}

int message_grp_push(server *srv, plugin_data *p, grp_info_p grp, mes_info_p mes)
{
    win_node_p node = grp->first_node;

    message_attach(&(grp->mes_list), mes);

    while(node) {
        if (node->win->con) {
            message_send_pending(srv, p, grp->mes_list.first_mes, node->win);
            window_flush(srv, p, node->win);
        }
        node = node->next;
    }

    return 0;
}
