#include "mod_fdajax_defs.h"

/* Code generated with Ragel v. 5.22 */
/* ragel mod_fdajax_parser.rl   | rlgen-cd -G2 -o mod_fdajax_parser.c */
/* ragel mod_fdajax_peercall.rl | rlgen-cd -G2 -o mod_fdajax_peercall.c */

/* strings sent to browser as response */
char *g_answer[] = { "CMD_OK",                      /* 0 */
                     "MEM_RESOURCES_PROBLEM",       /* 1 */
                     "NOT_IN_CHAT",                 /* 2 */
                     "MESSAGE_SENT",                /* 3 */
                     "USER_NOT_LOGGED",             /* 4 */
                     "ALREADY_LOGGED",              /* 5 */
                     "LOGIN_OK",                    /* 6 */
                     "LOGOUT_OK",                   /* 7 */
                     "USER_NOT_FOUND",              /* 8 */
                     "CHAT_PEER_ADD",               /* 9 */
                     "CHAT_PEER_RM_1",              /* 10 */
                     "CHAT_PEER_RM_2",              /* 11 */
                     "CUSER_NOT_FOUND",             /* 12 */
                     "CUSER_TOO_MANY",              /* 13 */
                     "WRONG_SYNTAX",                /* 14 */
                     "USER_ACTIVE",                 /* 15 */
                     "LOGIN_BAD_ID",                /* 16 */
                     "LOGIN_OLD_SESS",              /* 17 */
                     "GRP_NOT_FOUND"                /* 18 */
};

char g_timeval_buf[64];
char *tv2s(struct timeval atv)
{
    char dt[32];
    strftime(dt, sizeof(dt), "%F %T", gmtime(&(atv.tv_sec)));
    sprintf(g_timeval_buf, "%s:%ld", dt, atv.tv_usec);
    return g_timeval_buf;
}

void buffer_append_nl(buffer *buf)
{
    if (buf->used > 1 && buf->ptr[buf->used - 2] != '\n') {
        buffer_append_string(buf, "\n");
    }
}

/* handle plugin config and check values */
SETDEFAULTS_FUNC(mod_fdajax_set_defaults)
{
    plugin_data *p = p_d;
    data_string *ds;
    size_t j, i = 0;
    int k;

    config_values_t cv[] = {
        { "fdajax.ext",                NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 0 */
        { "fdajax.admin_ips",          NULL, T_CONFIG_ARRAY,   T_CONFIG_SCOPE_SERVER },       /* 1 */
        { "fdajax.mes_live_max",       NULL, T_CONFIG_SHORT,   T_CONFIG_SCOPE_SERVER },       /* 2 */
        { "fdajax.win_timeout",        NULL, T_CONFIG_SHORT,   T_CONFIG_SCOPE_SERVER },       /* 3 */
        { "fdajax.log_level",          NULL, T_CONFIG_SHORT,   T_CONFIG_SCOPE_SERVER },       /* 4 */
        { "fdajax.log_security",       NULL, T_CONFIG_SHORT,   T_CONFIG_SCOPE_SERVER },       /* 5 */
        { "fdajax.js_peer_func",       NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 6 */
        { "fdajax.js_logout_code",     NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 7 */
        { "fdajax.js_maxwin_code",     NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 8 */
        { "fdajax.merge_messages",     NULL, T_CONFIG_BOOLEAN, T_CONFIG_SCOPE_SERVER },       /* 9 */
        { "fdajax.js_nocookies",       NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 10 */
        { "fdajax.js_notfound",        NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 11 */
        { "fdajax.js_relogin",         NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 12 */
        { "fdajax.js_redirect",        NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 13 */
        { "fdajax.session_cookie",     NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 14 */
        { "fdajax.send_redirects",     NULL, T_CONFIG_BOOLEAN, T_CONFIG_SCOPE_SERVER },       /* 15 */
        { "fdajax.check_user_ip",      NULL, T_CONFIG_BOOLEAN, T_CONFIG_SCOPE_SERVER },       /* 16 */
        { "fdajax.js_alert_id_func",   NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 17 */
        { "fdajax.unw_prefix",         NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 18 */
        { "fdajax.send_pings",         NULL, T_CONFIG_SHORT,   T_CONFIG_SCOPE_SERVER },       /* 19 */
        { "fdajax.js_ping_code",       NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 20 */
        { "fdajax.allow_guests",       NULL, T_CONFIG_BOOLEAN, T_CONFIG_SCOPE_SERVER },       /* 21 */
        { "fdajax.js_no_guests",       NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 22 */
        { "fdajax.html_begin",         NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 23 */
        { "fdajax.allow_peer_call",    NULL, T_CONFIG_ARRAY,   T_CONFIG_SCOPE_SERVER },       /* 24 */
        { "fdajax.js_grp_peer_func",   NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 25 */
        { "fdajax.admin_password",     NULL, T_CONFIG_STRING,  T_CONFIG_SCOPE_SERVER },       /* 26 */
        { NULL,                        NULL, T_CONFIG_UNSET,   T_CONFIG_SCOPE_UNSET }
    };

    if (!p) return HANDLER_ERROR;
    p->config_storage = calloc(1, srv->config_context->used * sizeof(specific_config *));

    for (i = 0; i < srv->config_context->used; i++) {
        plugin_config *s;

        s = calloc(1, sizeof(plugin_config));
        s->ext          = buffer_init();
        buffer_copy_string(s->ext, "fdajax");
        s->admin_ips    = array_init();
        s->allow_peer_call = array_init();
        s->mes_live_max = 500;
        s->log_level    = LOG_LEVEL_NORMAL;
        s->log_security = LOG_LEVEL_AVG;
        s->js_peer_func = buffer_init();
        s->js_grp_peer_func = buffer_init();
        s->js_logout_code = buffer_init();
        s->js_maxwin_code = buffer_init();
        s->merge_messages = TRUE;
        s->send_redirects = TRUE;
        s->check_user_ip = TRUE;
        s->send_pings = 0;
        s->allow_guests = TRUE;
        s->js_nocookies_code = buffer_init();
        s->js_notfound_code =  buffer_init();
        s->js_relogin_func =   buffer_init();
        s->js_redirect_func =  buffer_init();
        s->js_alert_id_func =  buffer_init();
        s->js_ping_code =      buffer_init();
        s->js_no_guests =      buffer_init();
        s->unw_prefix =        buffer_init();
        s->session_cookie =    buffer_init();
        s->html_begin =        buffer_init();
        s->admin_password =    buffer_init();

        buffer_copy_string(s->js_peer_func, "js_peer_func");
        buffer_copy_string(s->js_grp_peer_func, "js_grp_peer_func");
        buffer_copy_string(s->js_logout_code, "js_logout_code();");
        buffer_copy_string(s->js_maxwin_code, "js_maxwin_code();");
        buffer_copy_string(s->js_nocookies_code, "js_nocookies_code();");
        buffer_copy_string(s->js_notfound_code, "js_notfound_code();");
        buffer_copy_string(s->js_relogin_func, "js_relogin_func");
        buffer_copy_string(s->js_redirect_func, "js_redirect_func");
        buffer_copy_string(s->js_alert_id_func, "js_alert_id_func");
        buffer_copy_string(s->js_ping_code, "js_ping_code();");
        buffer_copy_string(s->js_no_guests, "js_no_guests();");
        buffer_copy_string(s->unw_prefix, "unw.");
        buffer_copy_string(s->session_cookie, "_session_id");
        buffer_copy_string(s->html_begin, FDA_HTML_BEGIN);

        cv[0].destination = s->ext;
        cv[1].destination = s->admin_ips;
        cv[2].destination = &(s->mes_live_max);
        cv[3].destination = &(s->win_timeout);
        cv[4].destination = &(s->log_level);
        cv[5].destination = &(s->log_security);
        cv[6].destination = s->js_peer_func;
        cv[7].destination = s->js_logout_code;
        cv[8].destination = s->js_maxwin_code;
        cv[9].destination = &(s->merge_messages);
        cv[10].destination = s->js_nocookies_code;
        cv[11].destination = s->js_notfound_code;
        cv[12].destination = s->js_relogin_func;
        cv[13].destination = s->js_redirect_func;
        cv[14].destination = s->session_cookie;
        cv[15].destination = &(s->send_redirects);
        cv[16].destination = &(s->check_user_ip);
        cv[17].destination = s->js_alert_id_func;
        cv[18].destination = s->unw_prefix;
        cv[19].destination = &(s->send_pings);
        cv[20].destination = s->js_ping_code;
        cv[21].destination = &(s->allow_guests);
        cv[22].destination = s->js_no_guests;
        cv[23].destination = s->html_begin;
        cv[24].destination = s->allow_peer_call;
        cv[25].destination = s->js_grp_peer_func;
        cv[26].destination = s->admin_password;

        p->config_storage[i] = s;

        if (0 != config_insert_values_global(srv, ((data_config *)srv->config_context->data[i])->value, cv)) {
            return HANDLER_ERROR;
        }

        /* convert ip addresses only once */
        if (0 == i) {
            for (j = 0; j < s->admin_ips->used; j++) {
                if (s->admin_ips->data[j]->type != TYPE_STRING) {
                    log_error_write(srv, __FILE__, __LINE__, "s", "admin_ips must contain strings");
                    return HANDLER_ERROR;
                }
                ds = (data_string *)s->admin_ips->data[j];
                p->admin_allowed_ips[p->admin_allowed_used++].s_addr = inet_addr(ds->value->ptr);
                if (p->admin_allowed_ips[p->admin_allowed_used - 1].s_addr == INADDR_NONE) {
                    log_error_write(srv, __FILE__, __LINE__, "ss", "admin_ips has invalid addr: ", ds->value->ptr);
                    return HANDLER_ERROR;
                }
            }
            if (p->admin_allowed_used == 0) {
                log_error_write(srv, __FILE__, __LINE__, "s", "admin_ips should have at least one addr");
                return HANDLER_ERROR;
            }

            p->allow_peer_call_mask = 0;
            for (j = 0; j < s->allow_peer_call->used; j++) {
                if (s->allow_peer_call->data[j]->type != TYPE_STRING) {
                    log_error_write(srv, __FILE__, __LINE__, "s", "allow_peer_call must contain strings");
                    return HANDLER_ERROR;
                }
                ds = (data_string *)s->allow_peer_call->data[j];
                k = event_find_index_by_name(ds->value->ptr);
                if (-1 == k) {
                    log_error_write(srv, __FILE__, __LINE__, "ss", "allow_peer_call has invalid name: ", ds->value->ptr);
                    return HANDLER_ERROR;
                }
                p->allow_peer_call_mask |= g_ev_mask_by_index[k];
            }

            p->merge_messages = s->merge_messages;
            p->send_redirects = s->send_redirects;
            p->check_user_ip = s->check_user_ip;
            p->log_security = s->log_security;
            p->log_level =    s->log_level;
            p->mes_live_max = s->mes_live_max * 1000;
            p->win_timeout  = s->win_timeout * 1000;
            p->send_pings = s->send_pings;
            p->allow_guests = s->allow_guests;
            buffer_copy_string_buffer(p->js_peer_func, s->js_peer_func);
            buffer_copy_string_buffer(p->js_grp_peer_func, s->js_grp_peer_func);
            buffer_copy_string_buffer(p->js_logout_code, s->js_logout_code);
            buffer_copy_string_buffer(p->js_maxwin_code, s->js_maxwin_code);
            buffer_copy_string_buffer(p->js_nocookies_code, s->js_nocookies_code);
            buffer_copy_string_buffer(p->js_notfound_code, s->js_notfound_code);
            buffer_copy_string_buffer(p->js_relogin_func, s->js_relogin_func);
            buffer_copy_string_buffer(p->js_redirect_func, s->js_redirect_func);
            buffer_copy_string_buffer(p->js_alert_id_func, s->js_alert_id_func);
            buffer_copy_string_buffer(p->js_ping_code, s->js_ping_code);
            buffer_copy_string_buffer(p->unw_prefix, s->unw_prefix);
            buffer_copy_string_buffer(p->session_cookie, s->session_cookie);
            buffer_copy_string_buffer(p->js_no_guests, s->js_no_guests);
            buffer_copy_string_buffer(p->html_begin, s->html_begin);
            if (s->admin_password->used > 0) {
                buffer_copy_string_buffer(p->admin_password, s->admin_password);
            }
        }
    }
    return HANDLER_GO_ON;
}

#define PATCH(x) p->conf.x = s->x;

static int mod_fdajax_patch_connection(server *srv, connection *con, plugin_data *p) {
    plugin_config *s = p->config_storage[0];
    UNUSED(srv);
    UNUSED(con);
    PATCH(ext);

    return 0;
}
#undef PATCH

/* init the plugin data */
INIT_FUNC(mod_fdajax_init)
{
    plugin_data *p;
    int i;

    p = calloc(1, sizeof(*p));
    p->match_buf =          buffer_init();
    p->js_peer_func =       buffer_init();
    p->js_grp_peer_func =   buffer_init();
    p->js_logout_code =     buffer_init();
    p->js_maxwin_code =     buffer_init();
    p->js_nocookies_code =  buffer_init();
    p->js_notfound_code =   buffer_init();
    p->js_relogin_func =    buffer_init();
    p->js_redirect_func =   buffer_init();
    p->js_alert_id_func =   buffer_init();
    p->js_ping_code =       buffer_init();
    p->js_no_guests =       buffer_init();
    p->unw_prefix =         buffer_init();
    p->session_cookie =     buffer_init();
    p->html_begin =         buffer_init();
    p->admin_password =     buffer_init();
    p->next_check_dcons =   FDA_CHECK_CON_INTERVAL;
    p->users_by_sess =      NULL;
    p->users_by_id =        NULL;
    p->admin_allowed_used = 0;
    p->allow_peer_call_mask = 0;
    bzero(p->admin_allowed_ips, sizeof(p->admin_allowed_ips));

    for (i = 0; i < FDA_MAX_GROUPS; i++) {
        group_init(&(p->groups[i]), i);
    }

    return p;
}

/* detroy the plugin data */
FREE_FUNC(mod_fdajax_free)
{
    plugin_data *p = p_d;
    size_t i;

    if (!p) {
        return HANDLER_GO_ON;
    }
    if (p->config_storage) {
        for (i = 0; i < srv->config_context->used; i++) {
            plugin_config *s = p->config_storage[i];
            if (!s) continue;
            buffer_free(s->ext);
            buffer_free(s->js_peer_func);
            buffer_free(s->js_grp_peer_func);
            buffer_free(s->js_logout_code);
            buffer_free(s->js_maxwin_code);
            buffer_free(s->js_nocookies_code);
            buffer_free(s->js_notfound_code);
            buffer_free(s->js_relogin_func);
            buffer_free(s->js_redirect_func);
            buffer_free(s->js_alert_id_func);
            buffer_free(s->js_ping_code);
            buffer_free(s->js_no_guests);
            buffer_free(s->unw_prefix);
            buffer_free(s->session_cookie);
            buffer_free(s->html_begin);
            buffer_free(s->admin_password);
            array_free(s->admin_ips);
            array_free(s->allow_peer_call);
            free(s);
        }
        free(p->config_storage);
    }
    buffer_free(p->match_buf);
    buffer_free(p->js_peer_func);
    buffer_free(p->js_grp_peer_func);
    buffer_free(p->js_logout_code);
    buffer_free(p->js_maxwin_code);
    buffer_free(p->js_nocookies_code);
    buffer_free(p->js_notfound_code);
    buffer_free(p->js_relogin_func);
    buffer_free(p->js_redirect_func);
    buffer_free(p->js_alert_id_func);
    buffer_free(p->js_ping_code);
    buffer_free(p->js_no_guests);
    buffer_free(p->unw_prefix);
    buffer_free(p->session_cookie);
    buffer_free(p->html_begin);
    buffer_free(p->admin_password);
    users_free(srv, p);
    free(p);
    return HANDLER_GO_ON;
}

int is_tcp_socket_open(server *srv, plugin_data *p, connection *con)
{
#ifdef USE_TCP_INFO
    struct tcp_info tinfo;
    unsigned int len = sizeof(tinfo);
    if (!getsockopt(con->fd, SOL_TCP, TCP_INFO, &tinfo, &len)) {
        if (!(tinfo.tcpi_state == TCP_CLOSE_WAIT ||
              tinfo.tcpi_state == TCP_CLOSE ||
              tinfo.tcpi_state == TCP_LAST_ACK ||
              tinfo.tcpi_state == TCP_CLOSING ||
              tinfo.tcpi_state == TCP_TIME_WAIT ||
              tinfo.tcpi_state == TCP_FIN_WAIT1 ||
              tinfo.tcpi_state == TCP_FIN_WAIT2 )) {
            return TRUE;
        }
    } else {
        log_info(srv, __FILE__, __LINE__, "sd", "getsockopt error ", errno);
    }
#else
    fd_set rset, eset;
    struct timeval tv;
    int retval;
    char sbuf[1];

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&rset);
    FD_ZERO(&eset);
    FD_SET(con->fd, &rset);
    FD_SET(con->fd, &eset);
    retval = select(con->fd + 1, &rset, 0, &eset, &tv);
    if (-1 == retval) {
        log_info(srv, __FILE__, __LINE__, "sd", "select error ", errno);
    } else {
        if (FD_ISSET(con->fd, &eset)) {
            return FALSE;
        }
        if (FD_ISSET(con->fd, &rset)) {
            retval = read(con->fd, sbuf, 1);
            if (retval > 0) {
                log_info(srv, __FILE__, __LINE__, "sd", "is_tcp_socket_open serious error", con->fd);
            }
            return FALSE;
        }
        return TRUE;
    }
#endif
    return FALSE;
}

static void make_sock_keep_alive(server *srv, connection *con)
{
    int opt;
    unsigned int len = sizeof(opt);
    opt = 1;

    if (setsockopt(con->fd, SOL_SOCKET, SO_KEEPALIVE, &opt, len)) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "setsockopt error");
    }
}

static void set_con_header(server *srv, plugin_data *p, connection *con)
{
    UNUSED(p);
    if (0 != con->file_started) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "set_con_header file_started error");
    }
    response_header_overwrite(srv, con, CONST_STR_LEN("Content-Type"), CONST_STR_LEN("text/html"));
    response_header_overwrite(srv, con, CONST_STR_LEN("Pragma"), CONST_STR_LEN("no-cache"));
    response_header_overwrite(srv, con, CONST_STR_LEN("Expires"), CONST_STR_LEN("Thu, 19 Nov 1981 08:52:00 GMT"));
    response_header_overwrite(srv, con, CONST_STR_LEN("Cache-Control"),
                              CONST_STR_LEN("no-store, no-cache, must-revalidate, post-check=0, pre-check=0"));
    con->http_status = 200;
    con->file_started = 1;
}

void con_set_response(server *srv, plugin_data *p, connection *con, buffer *resp, int st)
{
    buffer *b;
    UNUSED(p);
    if (1 != con->file_started) {
        set_con_header(srv, p, con);
    }
    if (0 != con->file_finished) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "set_con_resonse file_finished error");
    }
    b = chunkqueue_get_append_buffer(con->write_queue);
    if (st) {
        BUFFER_APPEND_STRING_CONST(b, SCRIPT_JS_BEGIN);
    }
    buffer_append_string_buffer(b, resp);
    if (st) {
        BUFFER_APPEND_STRING_CONST(b, SCRIPT_JS_END);
    }
    http_chunk_append_mem(srv, con, NULL, 0);
    con->file_finished = 1;
    joblist_append(srv, con);
}

void con_prepare_response(server *srv, plugin_data *p, connection *con, int st)
{
    buffer *b;
    UNUSED(p);
    if (1 != con->file_started) {
        set_con_header(srv, p, con);
    }
    if (0 != con->file_finished) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "con_prepare_response file_finished error");
    }
    if (st) {
        b = chunkqueue_get_append_buffer(con->write_queue);
        BUFFER_APPEND_STRING_CONST(b, SCRIPT_JS_BEGIN);
    }
}

void con_finalize_response(server *srv, plugin_data *p, connection *con, int st)
{
    buffer *b;
    UNUSED(p);
    if (st) {
        b = chunkqueue_get_append_buffer(con->write_queue);
        BUFFER_APPEND_STRING_CONST(b, SCRIPT_JS_END);
    }
    con->file_finished = 1;
    joblist_append(srv, con);
}

void con_redirect_to(server *srv, plugin_data *p, connection *con, int redir_to, int st)
{
    char s[256];

    con_prepare_response(srv, p, con, st);
    http_chunk_append_buffer(srv, con, p->js_redirect_func);
    sprintf(s, "(%d);", redir_to);
    http_chunk_append_mem(srv, con, s, strlen(s) + 1);
    http_chunk_append_mem(srv, con, NULL, 0);
    con_finalize_response(srv, p, con, st);
}

static int mod_fdajax_return_as_text(server *srv, connection *con, plugin_data *p, char *text)
{
    buffer *b = chunkqueue_get_append_buffer(con->write_queue);

    UNUSED(p);

    buffer_append_string(b, text);
    response_header_insert(srv, con, CONST_STR_LEN("Content-Type"), CONST_STR_LEN("text/plain"));
    con->http_status = 200;
    con->file_finished = 1;
    return 0;
}

static handler_t mod_fdajax_con_reset(server *srv, connection *con, void *p_d)
{
    plugin_data *p = p_d;
    win_info_p win;
    user_info_p user;
    size_t i;
    int found = FALSE;

    UNUSED(p);
    UNUSED(srv);

    if (NULL == con->plugin_ctx[p->id]) {
        return HANDLER_GO_ON;
    }
    win = con->plugin_ctx[p->id];
    con->plugin_ctx[p->id] = NULL;

    if (win->con != con) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "con_reset win con error");
        return HANDLER_GO_ON;
    }
    if(NULL == (user = win->owner)) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "con_reset owner is NULL error");
        return HANDLER_GO_ON;
    }
    for(i = 0; i < WINDOWS_MAX; i++) {
        if (user->windows[i] == win) {
            log_avg(srv, __FILE__, __LINE__, "bsdsd", con->dst_addr_buf, "con_reset dispose uid", user->user_id,
                    "win_id", win->win_id );
            win->con = NULL;
            found = TRUE;
        }
    }
    if (!found) {
        log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "con_reset not found error");
    }
    return HANDLER_GO_ON;
}

static handler_t mod_fdajax_con_close(server *srv, connection *con, void *p_d)
{
    plugin_data *p = p_d;
    win_info_p win;

    if (NULL != (win = con->plugin_ctx[p->id])) {
        log_error_write(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "con_close win_id", win->win_id);
        return HANDLER_GO_ON;
    }
    return HANDLER_GO_ON;
}

static int check_dead_cons(server *srv, plugin_data *p, user_info_p user)
{
    size_t i;
    int count = 0;
    struct timeval now;

    gettimeofday(&now, 0);

    for (i = 0; i < WINDOWS_MAX; i++) {
        if (NULL != user->windows[i] && NULL != user->windows[i]->con) {
            if (is_tcp_socket_open(srv, p, user->windows[i]->con)) {
                if (p->send_pings > 0) {
                    if (user->windows[i]->created_at.tv_sec < now.tv_sec - p->send_pings) {
                        window_append_string_buffer(user->windows[i], p->js_ping_code);
                        window_flush(srv, p, user->windows[i]);
                        user->windows[i]->con->file_finished = 1;
                    }
                }
            } else {
                /* remote side has closed connection */
                connection *dcon = user->windows[i]->con;
                log_avg(srv, __FILE__, __LINE__, "bs", dcon->dst_addr_buf, "check_dead_cons close");
                dcon->plugin_ctx[p->id] = NULL;
                connection_set_state(srv, dcon, CON_STATE_ERROR);
                joblist_append(srv, dcon);
                window_free(p, user->windows[i]);
                user->windows[i] = NULL;
                count++;
            }
        }
    }
    return count;
}

TRIGGER_FUNC(mod_fdajax_trigger)
{
    plugin_data *p = p_d;
    user_info_p user;
    int count = 0;

    if (p->next_check_dcons > 0) {
        /* trigger is executed once a second */
        p->next_check_dcons--;

        group_remove_old_mes(srv, p);

    } else {
        p->next_check_dcons = FDA_CHECK_CON_INTERVAL;

        for (user = p->users_by_sess; user != NULL; user = user->hh_sess.next) {
            count += check_dead_cons(srv, p, user);
        }
        if (count > 0) {
            log_info(srv, __FILE__, __LINE__, "sd", "trigger closed_windows " , count);
        }
    }
    return HANDLER_GO_ON;
}

static char *find_cookie_val(char *name, char *s, int *len)
{
    char *g, *nc, *st;

    if (NULL != (g = strstr(s, name))) {
        for (nc = g + strlen(name); *nc == ' ' || *nc == '\t'; nc++);
        if (*nc == '=') {
            st = ++nc;
            while (isalnum(*nc)) nc++;
            if (nc > st) {
                *len = nc - st;
                return st;
            }
        }
    }
    return NULL;
}

static void extract_cookies(server *srv, connection *con, plugin_data *p, user_request_p req)
{
    data_string *ds;
    UNUSED(srv);
    UNUSED(p);

    if (NULL != (ds = (data_string *)array_get_element(con->request.headers, "Cookie"))) {
        char *st;
        int len;
        if ((st = find_cookie_val(p->session_cookie->ptr, ds->value->ptr, &len))) {
            strncpy(req->sess_id_cookie, st, min(len, SESS_ID_LEN_MAX - 1));
            req->sess_id_cookie[min(len, SESS_ID_LEN_MAX - 1)] = 0;
        }
    }
}

static void find_www_nr(server *srv, connection *con, plugin_data *p, user_request_p req)
{
    if (con->request.http_host && con->request.http_host->ptr) {
        char *s = con->request.http_host->ptr;
        if (*s && *s == 's' && (strncmp(s, "secure", sizeof("secure") - 1) == 0)) {
            req->www_id = WINDOWS_MAX - 1;
            req->force_old_close = TRUE;
            return;
        }
        while (*s && (*s == 'w' || (*s >= '0' && *s <= '9'))) {
            if (isdigit(*s)) {
                req->www_id = *s - '0';
                if (req->www_id > WINDOWS_MAX) {
                    req->www_id = WINDOWS_MAX - 1;
                }
                break;
            }
            s++;
        }
    } else {
        if (con->dst_addr.ipv4.sin_addr.s_addr != htonl(INADDR_LOOPBACK)) {
            log_high(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "http_host not present");
        }
    }
}

static void free_request_resources(user_request_p req)
{
    if (req->mes) {
        buffer_free(req->mes);
        req->mes = NULL;
    }
    if (req->req_sess_id) {
        buffer_free(req->req_sess_id);
        req->req_sess_id = NULL;
    }
}

/* main commands handle function */

static int mod_fdajax_handle(server *srv, connection *con, plugin_data *p)
{
    enum auth_problem_t auth_problem;
    user_request_t req;
    user_info_p user, peer;
    grp_info_p grp;
    win_info_p win;
    mes_info_p mes;
    size_t i;
    int redirect, found, count, slot;
    buffer *b;
    char *ps;
    enum cmd_res_t answer;

    /* parse query */
    mod_fdajax_pinit(&req);
    mod_fdajax_pexec(&req, con->uri.query->ptr, con->uri.query->used - 1);
    if (mod_fdajax_pfinish(&req) < 1) {
        free_request_resources(&req);
        con->http_status = 500;
        log_high(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "URI parser error");
        return HANDLER_FINISHED;
    }
    extract_cookies(srv, con, p, &req);
    find_www_nr(srv, con, p, &req);

    if (req.cmd == cmd_none) {
        security_avg(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "security: cmd_not_set");
        free_request_resources(&req);
        con->http_status = 500;
        return HANDLER_FINISHED;
    }

    if (req.cmd == cmd_chatsig || req.cmd == cmd_wait || req.cmd == cmd_cancel || req.cmd == cmd_stream) {
        /* this is user space command */

        user = NULL;
        if (strlen(req.sess_id_cookie) == 0) {
            auth_problem = authp_null_cookie;
            security_avg(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "security: auth_user sess_id_cookie empty");
        } else {
            user = user_find_by_sess(p, req.sess_id_cookie);
            if (user) {
                user = user_auth(srv, con, p, user, &req, &auth_problem);
            } else {
                if (req.user_id != 0) {
                    auth_problem = authp_user_not_found;
                } else {
                    if (p->allow_guests) {
                        user = user_create_guest(con, &req);
                        user_attach(srv, p, user);
                    } else {
                        auth_problem = authp_no_guests;
                    }
                }
            }
        }

        if (NULL == user) {
            switch (auth_problem) {
            case authp_null_userid:
                con->http_status = 500;
                break;

            case authp_null_cookie:
                con_set_response(srv, p, con, p->js_nocookies_code, req.win_st);
                log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "auth: nocookies uid ", req.user_id);
                break;

            case authp_user_not_found:
                con_set_response(srv, p, con, p->js_notfound_code, req.win_st);
                log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "auth: not_found uid ", req.user_id);
                break;

            case authp_ip_addr:
                con_prepare_response(srv, p, con, req.win_st);
                b = chunkqueue_get_append_buffer(con->write_queue);
                buffer_append_string_buffer(b, p->js_relogin_func);
                buffer_append_string(b, "('ipaddr');");
                http_chunk_append_mem(srv, con, NULL, 0);
                con_finalize_response(srv, p, con, req.win_st);
                log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "auth: relogin_ipaddr uid ", req.user_id);
                break;

            case authp_sessid:
                con_prepare_response(srv, p, con, req.win_st);
                b = chunkqueue_get_append_buffer(con->write_queue);
                buffer_append_string_buffer(b, p->js_relogin_func);
                buffer_append_string(b, "('sessid');");
                http_chunk_append_mem(srv, con, NULL, 0);
                con_finalize_response(srv, p, con, req.win_st);
                log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "auth: relogin_sessid uid ", req.user_id);
                break;

            case authp_no_guests:
                con_set_response(srv, p, con, p->js_no_guests, req.win_st);
                log_high(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "auth: no_guests");
                break;
            }

        } else {
            switch (req.cmd) {
            case cmd_chatsig:
                if (1 != req.ev.count || NULL == req.mes || 0 == req.mes->used) {
                    con->http_status = 500;
                    break;
                }
                i = event_bit_to_index(req.ev.types);
                if (i < FDA_GRP_START) {
                    if (0 == user->user_id || 0 == req.peer_id) {
                        log_high(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:chatsig wrong parameters");
                        con->http_status = 500;
                        break;
                    }
                    if (!chat_access_peer(user, req.peer_id)) {
                        answer = cmdr_not_in_chat;
                    } else {
                        peer = user_find_by_id(p, req.peer_id);
                        if (!peer) {
                            answer = cmdr_user_not_logged;
                        } else {
                            if (!(mes = message_init_peer(srv, p, user, &req))) {
                                answer = cmdr_wrong_syntax;
                            } else {
                                message_remove_old(srv, p, &(peer->mes_list));
                                answer = message_push(srv, p, peer, mes);
                                window_flush_all(srv, p, peer);
                            }
                        }
                    }
                } else {
                    grp = group_find(p, req.ev.types);
                    if (!grp) {
                        answer = cmdr_grp_not_found;
                    } else {
                        if (!(mes = message_init_peer(srv, p, user, &req))) {
                            answer = cmdr_wrong_syntax;
                        } else {
                            message_grp_push(srv, p, grp, mes);
                            answer = cmdr_ok;
                        }
                    }
                }

                con_prepare_response(srv, p, con, req.win_st);
                http_chunk_append_mem(srv, con, g_answer[answer], strlen(g_answer[answer]) + 1);
                http_chunk_append_mem(srv, con, NULL, 0);
                con_finalize_response(srv, p, con, req.win_st);
                log_avg(srv, __FILE__, __LINE__, "bss", con->dst_addr_buf, "cmd:chatsig answer ", g_answer[answer]);
                break;

            case cmd_wait:
                if (req.ev.types == 0 || req.win_id == 0) {
                    con->http_status = 500;
                    break;
                }
                message_remove_old(srv, p, &(user->mes_list));
                window_remove_old(srv, p, con, user);

                win = window_find(con, user, &req);
                if ((NULL != win) && (NULL != win->con) && (win->con != con)) {
                    log_avg(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "cmd:wait same_win_id", win->win_id);
                    con->http_status = 500;
                    break;
                }
                if (win) {
                    win->ev = req.ev;

                    if (NULL == win->con) {
                        win->con = con;
                    } else {
                        assert(win->con == con);
                    }
                } else {
                    redirect = window_should_redirect(srv, p, con, user, &req);
                    if (redirect != -1) {
                        con_redirect_to(srv, p, con, redirect, req.win_st);
                        break;
                    }
                    if (-1 == (slot = window_find_slot(user))) {
                        log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "cmd:wait not empty slot uid", req.user_id);
                        con_set_response(srv, p, con, p->js_maxwin_code, req.win_st);
                        break;
                    }
                    win = window_init(p, con, user, &req, fda_win_chunked, slot);
                }
                con->mode = p->id;
                con->plugin_ctx[p->id] = win;

                answer = message_send_pending(srv, p, user->mes_list.first_mes, win);
                if (win->ev.types & FDA_EV_UNW) {
                    if (message_check_unsend(srv, p, user, win) > 0) {
                        answer = cmdr_mes_sent;
                    }
                    alert_push(srv, p, user);
                }
                window_check_groups(srv, p, win);

                count = win->send_count;
                window_flush_all(srv, p, user);

                if (win->send_count > count) {
                    log_avg(srv, __FILE__, __LINE__, "bsdsd", con->dst_addr_buf, "cmd:wait exit uid ", req.user_id,
                            " port ", ntohs(con->dst_addr.ipv4.sin_port));
                    break;
                }

                /* register win to handle when event arrives. set also keep-alive for socket
                   to make sure that disconnected socket will be detected and sweeped by trigger */
                make_sock_keep_alive(srv, con);
                log_avg(srv, __FILE__, __LINE__, "bsdsdsdss", con->dst_addr_buf, "cmd:wait wait uid", req.user_id,
                        "win_id", req.win_id, "www_id", req.www_id,
                        "sync_tv", req.tv.tv_sec > 0 ? tv2s(req.tv) : "not_set");
                free_request_resources(&req);
                return HANDLER_WAIT_FOR_EVENT;

            case cmd_stream:
                if (req.ev.types == 0 || req.win_id == 0) {
                    con->http_status = 500;
                    break;
                }
                message_remove_old(srv, p, &(user->mes_list));
                window_remove_old(srv, p, con, user);

                win = window_find(con, user, &req);
                if (NULL != win) {
                    if (NULL == win->con) {
                        win->ev = req.ev;
                        win->con = con;
                    } else {
                        log_avg(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "cmd:stream same_win_id", win->win_id);
                        con->http_status = 500;
                        break;
                    }
                } else {
                    redirect = window_should_redirect(srv, p, con, user, &req);
                    if (redirect != -1) {
                        con_redirect_to(srv, p, con, redirect, req.win_st);
                        break;
                    }
                    if (-1 == (slot = window_find_slot(user))) {
                        log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "cmd:stream not empty slot uid", req.user_id);
                        con_set_response(srv, p, con, p->js_maxwin_code, req.win_st);
                        break;
                    }
                    win = window_init(p, con, user, &req, fda_win_stream, slot);
                }

                con->mode = p->id;
                con->plugin_ctx[p->id] = win;
                make_sock_keep_alive(srv, con);
                /* send http header */
                con_prepare_response(srv, p, con, 0);
                b = chunkqueue_get_append_buffer(con->write_queue);
                buffer_append_string_buffer(b, p->html_begin);
                buffer_append_nl(b);
                http_chunk_append_mem(srv, con, NULL, 0);

                answer = message_send_pending(srv, p, user->mes_list.first_mes, win);
                if (win->ev.types & FDA_EV_UNW) {
                    /* check if there is unsend message, this win can receive it */
                    if (message_check_unsend(srv, p, user, win) > 0) {
                        answer = cmdr_mes_sent;
                    }
                    alert_push(srv, p, user);
                }
                window_check_groups(srv, p, win);
                window_flush_all(srv, p, user);

                log_avg(srv, __FILE__, __LINE__, "bsdsdsdss", con->dst_addr_buf, "cmd:stream wait uid", req.user_id,
                        "win_id", req.win_id, "www_id", req.www_id,
                        "sync_tv", req.tv.tv_sec > 0 ? tv2s(req.tv) : "not_set");
                free_request_resources(&req);
                return HANDLER_FINISHED;

            case cmd_cancel:
                if (0 == req.win_id && 0 == req.alert_id) {
                    con->http_status = 500;
                    break;
                }
                if (req.win_id > 0) {
                    found = FALSE;
                    if (NULL != (win = window_find(con, user, &req))) {
                        if (win->con) {
                            con_prepare_response(srv, p, win->con, 0);
                            http_chunk_append_mem(srv, win->con, NULL, 0);
                            con_finalize_response(srv, p, win->con, 0);
                            window_close(srv, p, user, win, NULL);
                            found = TRUE;
                        }
                    }
                } else {
                    found = alert_cancel(user, req.alert_id);
                }
                con_prepare_response(srv, p, con, req.win_st);

                if (req.mes && (req.mes->used > 0) && (strncmp(req.mes->ptr, "noresult", sizeof("noresult") - 1) == 0)) {
                    /* nothing to send */
                } else {
                    ps = found ? "CLOSED" : "NOT_FOUND";
                    http_chunk_append_mem(srv, con, ps, strlen(ps) + 1);
                }
                http_chunk_append_mem(srv, con, NULL, 0);
                con_finalize_response(srv, p, con, req.win_st);
                log_avg(srv, __FILE__, __LINE__, "bsdsdss", con->dst_addr_buf, "cmd:cancel uid", user->user_id, "win_id", req.win_id,
                        "result", found ? "closed" : "not_found");
                break;

            default:
                log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "user command error");
                con->http_status = 500;
                break;
            }
        }
    } else {
        /* this is admin space command */
        int is_admin = FALSE;
        int open_win_count;

        for (i = 0; i < p->admin_allowed_used; i++) {
            if (p->admin_allowed_ips[i].s_addr == con->dst_addr.ipv4.sin_addr.s_addr) {
                is_admin = TRUE;
                break;
            }
        }
        if (p->admin_password->used > 0) {
            if (0 != strcmp(p->admin_password->ptr, req.admin_passwd)) {
                is_admin = FALSE;
            }
        }
        if (!is_admin) {
            security_avg(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf,
                         "security: attempt to exec admin cmd");
            con->http_status = 500;
        } else {
            switch (req.cmd) {
            case cmd_check_user:
                if (req.user_id == 0) {
                    log_info(srv, __FILE__, __LINE__, "s", "cmd:check_user bad_params");
                    con->http_status = 500;
                    break;
                }

                open_win_count = 0;
                user = user_find_by_id(p, req.user_id);
                if (user) {
                    open_win_count = user_check(srv, p, con, user);
                    if (open_win_count > 0) {
                        answer = cmdr_user_active;
                    } else {
                        user_detach(srv, p, user);
                        user_free(srv, p, con, user);
                        answer = cmdr_logout_ok;
                    }
                } else {
                    answer = cmdr_user_not_found;
                }
                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsdsdss", con->dst_addr_buf, "cmd:check_user uid ",
                        req.user_id, " open_windows ", open_win_count, " result ", g_answer[answer]);
                break;

            case cmd_login:
                if (req.user_id == 0 || req.ipaddr.s_addr == INADDR_NONE ||
                    req.req_sess_id == NULL || req.req_sess_id->used > SESS_ID_LEN_MAX) {
                    log_info(srv, __FILE__, __LINE__, "s", "cmd:login bad_params");
                    con->http_status = 500;
                    break;
                }

                user = user_find_by_id(p, req.user_id);
                if (user) {
                    user_update_addr_and_sess(p, user, &req);
                    answer = cmdr_already_logged;
                    log_high(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf, "cmd:login update uid ", user->user_id);
                } else {
                    user = user_find_by_sess(p, req.req_sess_id->ptr);
                    if (user) {
                        if (0 == user->user_id) {
                            user_update_id_and_ipaddr(p, user, &req);
                            answer = cmdr_login_old_sess;
                        } else {
                            answer = cmdr_login_bad_id;
                        }
                    } else {
                        user = user_login(&req);
                        user_attach(srv, p, user);
                        answer = cmdr_login_ok;
                    }
                }

                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsdss", con->dst_addr_buf, "cmd:login uid ", req.user_id,
                        " result ", g_answer[answer]);
                break;

            case cmd_logout:
                if (req.user_id == 0) {
                    log_info(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:logout bad_params");
                    con->http_status = 500;
                    break;
                }

                user = user_find_by_id(p, req.user_id);
                if (user) {
                    user_detach(srv, p, user);
                    user_free(srv, p, con, user);
                    answer = cmdr_logout_ok;
                } else {
                    answer = cmdr_user_not_found;
                }

                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsdss", con->dst_addr_buf, "cmd:logout uid ",
                        req.user_id, " result ", g_answer[answer]);
                break;

            case cmd_addchat:
                if (req.user_id == 0 || req.peer_id == 0) {
                    log_info(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:addchat bad_params");
                    con->http_status = 500;
                    break;
                }
                user = user_find_by_id(p, req.user_id);
                peer = user_find_by_id(p, req.peer_id);
                if (!user || !peer) {
                    answer = cmdr_user_not_found;
                } else {
                    if (cmdr_chat_peer_add == (answer = chat_add_peer(user, peer->user_id))) {
                        if (cmdr_chat_peer_add != (answer = chat_add_peer(peer, user->user_id))) {
                            /* clean first user's chat list */
                            chat_rm_peer(user, peer->user_id);
                        }
                    }
                }
                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsdss", con->dst_addr_buf, "cmd:addchat uid ", req.user_id,
                        " result ", g_answer[answer]);
                break;

            case cmd_rmchat:
                if (req.user_id == 0 || req.peer_id == 0) {
                    log_info(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:rmchat bad_params");
                    con->http_status = 500;
                    break;
                }
                user = user_find_by_id(p, req.user_id);
                peer = user_find_by_id(p, req.peer_id);
                if (!user) {
                    answer = cmdr_user_not_found;
                } else {
                    answer = chat_rm_peer(user, req.peer_id);
                }
                if (peer) {
                    if (cmdr_chat_peer_rm_1 == chat_rm_peer(peer, req.user_id)) {
                        if (cmdr_chat_peer_rm_1 == answer) {
                            answer = cmdr_chat_peer_rm_2;
                        } else if (cmdr_user_not_found == answer) {
                            answer = cmdr_chat_peer_rm_1;
                        }
                    }
                }
                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsdss", con->dst_addr_buf, "cmd:rmchat uid ", req.user_id,
                        " result ", g_answer[answer]);
                break;


            case cmd_push:
                if (NULL == req.mes || 0 == req.mes->used || 1 != req.ev.count) {
                    log_info(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:push wrong_parameters");
                    con->http_status = 500;
                    break;
                }

                i = event_bit_to_index(req.ev.types);
                if (i < FDA_GRP_START) {
                    if (0 == req.peer_id) {
                        log_info(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:push wrong_parameters");
                        con->http_status = 500;
                        break;
                    }

                    peer = user_find_by_id(p, req.peer_id);
                    if (!peer) {
                        answer = cmdr_user_not_logged;
                    } else {
                        message_remove_old(srv, p, &(peer->mes_list));
                        mes = message_init(&req);
                        message_push(srv, p, peer, mes);
                        alert_push(srv, p, peer);
                        window_flush_all(srv, p, peer);
                        answer = cmdr_ok;
                    }
                } else {
                    grp = group_find(p, req.ev.types);
                    if (!grp) {
                        answer = cmdr_grp_not_found;
                    } else {
                        message_remove_old(srv, p, &(grp->mes_list));
                        mes = message_init(&req);
                        message_grp_push(srv, p, grp, mes);
                        answer = cmdr_ok;
                    }
                }
                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsssd", con->dst_addr_buf, "cmd:push result ", g_answer[answer],
                        " uid ", req.peer_id);
                break;

            case cmd_alert:
                if (req.peer_id == 0 || NULL == req.mes || 0 == req.mes->used) {
                    log_info(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "cmd:alert wrong_parameters");
                    con->http_status = 500;
                    break;
                }
                peer = user_find_by_id(p, req.peer_id);
                if (!peer) {
                    answer = cmdr_user_not_logged;
                } else {
                    message_remove_old(srv, p, &(peer->mes_list));
                    alert_add(srv, p, con, peer, &req);
                    alert_push(srv, p, peer);
                    window_flush_all(srv, p, peer);
                    answer = cmdr_ok;
                }
                mod_fdajax_return_as_text(srv, con, p, g_answer[answer]);
                log_avg(srv, __FILE__, __LINE__, "bsssd", con->dst_addr_buf, "cmd:alert result ", g_answer[answer],
                        " uid ", req.peer_id);
                break;

            case cmd_info:
                mod_fdajax_info(srv, p, con);
                con->http_status = 200;
                con->file_finished = 1;
                break;

            default:
                log_error_write(srv, __FILE__, __LINE__, "bs", con->dst_addr_buf, "unrecognized admin command");
                con->http_status = 500;
                break;
            }
        }
    }

    free_request_resources(&req);
    if (0 == con->http_status) {
        con->http_status = 200;
    }
    return HANDLER_FINISHED;
}


URIHANDLER_FUNC(mod_fdajax_uri_handler)
{
    plugin_data *p = p_d;
    int s_len;
    int ct_len;

    UNUSED(srv);

    if (con->uri.path->used == 0) return HANDLER_GO_ON;

    mod_fdajax_patch_connection(srv, con, p);
    s_len = con->uri.path->used - 1;
    ct_len = p->conf.ext->used - 1;

    if (ct_len > 0 && s_len >= ct_len &&
        0 == strncmp(con->uri.path->ptr + s_len - ct_len, p->conf.ext->ptr, ct_len)) {

        return mod_fdajax_handle(srv, con, p);
    }

    /* not found */
    return HANDLER_GO_ON;
}

SUBREQUEST_FUNC(mod_fdajax_subrequest)
{
    plugin_data *p = p_d;

    if (NULL == con->plugin_ctx[p->id]) {
        return HANDLER_GO_ON;
    }
    if (con->file_finished) {
        /* file_finished is set by push_message func */
        return HANDLER_FINISHED;
    }
    log_error_write(srv, __FILE__, __LINE__, "s", "subrequest not finished");
    return HANDLER_WAIT_FOR_EVENT;
}

/* this function is called at dlopen() time and inits the callbacks */

int mod_fdajax_plugin_init(plugin *p)
{
    p->version     = LIGHTTPD_VERSION_ID;
    p->name        = buffer_init_string("fdajax");

    p->connection_reset =           mod_fdajax_con_reset;
    p->handle_connection_close =    mod_fdajax_con_close;
    p->handle_trigger =             mod_fdajax_trigger;
    p->init =                       mod_fdajax_init;
    p->handle_uri_clean  =          mod_fdajax_uri_handler;
    p->handle_subrequest =          mod_fdajax_subrequest;
    p->set_defaults  =              mod_fdajax_set_defaults;
    p->cleanup =                    mod_fdajax_free;
    p->data =                       NULL;

    return 0;
}
