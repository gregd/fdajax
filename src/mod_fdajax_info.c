#include "mod_fdajax_defs.h"

char *tv2s(struct timeval atv);

int print_user(buffer *b, user_info_p user)
{
    win_info_p win;
    int first;
    size_t i, j, k;

    BUFFER_APPEND_STRING_CONST(b, "<tr><td>");
    buffer_append_long(b, user->user_id);
    BUFFER_APPEND_STRING_CONST(b, "</td><td>");
    BUFFER_APPEND_STRING_CONST(b, "IP address: ");
    buffer_append_string(b, inet_ntoa(user->ipaddr));
    BUFFER_APPEND_STRING_CONST(b, "&nbsp;&nbsp;Created at: ");
    buffer_append_string(b, tv2s(user->created_at));
    BUFFER_APPEND_STRING_CONST(b, "<br/>Peers: ");
    first = TRUE;
    for(i = 0; i < PEERS_MAX; i++) {
        if (user->peers[i] != 0) {
            first = FALSE;
            buffer_append_long(b, user->peers[i]);
            BUFFER_APPEND_STRING_CONST(b, " ");
        }
    }
    if (first) {
        BUFFER_APPEND_STRING_CONST(b, "Empty");
    }
    BUFFER_APPEND_STRING_CONST(b, "&nbsp;&nbsp;To peer: ");
    buffer_append_long(b, user->send_peer_count);
    BUFFER_APPEND_STRING_CONST(b, "&nbsp;&nbsp;Total recv: ");
    buffer_append_long(b, user->send_count);
    BUFFER_APPEND_STRING_CONST(b,
                               "<table class=\"win\"><tr><th>Win ID</th><th>Mode</th><th>Port</th><th>Events</th>"
                               "<th>Count</th><th>Alert</th></tr>\n");
    for(i = 0; i < WINDOWS_MAX; i++) {
        win = user->windows[i];
        if (NULL == win) {
            continue;
        }
        BUFFER_APPEND_STRING_CONST(b, "<tr><td>");
        buffer_append_long(b, win->win_id);
        BUFFER_APPEND_STRING_CONST(b, "</td><td>");
        switch (win->win_type) {
        case fda_win_chunked:
            BUFFER_APPEND_STRING_CONST(b, "chunked");
            break;
        case fda_win_stream:
            BUFFER_APPEND_STRING_CONST(b, "stream");
        }
        BUFFER_APPEND_STRING_CONST(b, "</td><td>");
        if (win->con) {
            buffer_append_long(b, ntohs(win->con->dst_addr.ipv4.sin_port));
        } else {
            BUFFER_APPEND_STRING_CONST(b, "&nbsp;");
        }
        BUFFER_APPEND_STRING_CONST(b, "</td><td>");
        first = TRUE;
        for (k = 0; k < FDA_TYPES_MAX; k++) {
            if (win->ev.types & g_ev_mask_by_index[k]) {
                if (first) {
                    first = FALSE;
                } else {
                    BUFFER_APPEND_STRING_CONST(b, " | ");
                }
                buffer_append_string(b, g_ev_name_by_index[k]);
                BUFFER_APPEND_STRING_CONST(b, " ");
                for (j = 0; j < win->ev.ids_len[k]; j++) {
                    buffer_append_long(b, win->ev.ids[k][j]);
                    BUFFER_APPEND_STRING_CONST(b, " ");
                }
            }
        }
        BUFFER_APPEND_STRING_CONST(b, "</td><td>");
        buffer_append_long(b, win->send_count);
        BUFFER_APPEND_STRING_CONST(b, "</td><td>");
        buffer_append_long(b, win->last_alert);
        BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    }
    BUFFER_APPEND_STRING_CONST(b, "</table></td></tr>");
    return 0;
}

int mod_fdajax_info(server *srv, plugin_data *p, connection *con)
{
    user_info_p user;
    size_t i;
    buffer *b;
    b = chunkqueue_get_append_buffer(con->write_queue);

    BUFFER_COPY_STRING_CONST(b,
                             "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n"
                             "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"\n"
                             "  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n"
                             "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" lang=\"en\">\n"
                             "<head>\n"
                             "<title>FdAjax Module Status</title>\n");
    BUFFER_APPEND_STRING_CONST(b,
                               "<style type=\"text/css\">\n"
                               "div.main { float: left; margin: 20px; width: 650px; }\n"
                               "div.side { float: left; width: 300px; margin-top: 20px;}\n"
                               "h2 { text-align: center; }\n"
                               "h4 { text-align: center; }\n"
                               "table { width: 645px; border-collapse: collapse; }\n"
                               "table.win { margin: 3px; width: 100%; border-collapse: collapse; }\n"
                               "td { padding: 3px; margin: 0px; border: 1px solid #dfddcf; vertical-align: top; }\n"
                               "</style>\n");
    BUFFER_APPEND_STRING_CONST(b,
                               "</head>\n"
                               "<body>\n");

    BUFFER_APPEND_STRING_CONST(b, "<div class=\"main\">");
    BUFFER_APPEND_STRING_CONST(b, "<h2>Full-duplex Ajax Module Version 0.9</h2>");
    BUFFER_APPEND_STRING_CONST(b, "<h2>Configuration</h2>");
    BUFFER_APPEND_STRING_CONST(b, "<table><tr><th>Parameter</th><th>Value<th></tr>\n");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>mes_live_max (ms)</td><td>");
    buffer_append_long(b, p->mes_live_max / 1000);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>win_timeout (ms)</td><td>");
    buffer_append_long(b, p->win_timeout / 1000);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>session_cookie</td><td>");
    buffer_append_string_buffer(b, p->session_cookie);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>allow_guests</td><td>");
    buffer_append_string(b, p->allow_guests ? "enable" : "disable");
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>send_redirects</td><td>");
    buffer_append_string(b, p->send_redirects ? "enable" : "disable");
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>merge_messages</td><td>");
    buffer_append_string(b, p->merge_messages ? "enable" : "disable");
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>log_level</td><td>");
    buffer_append_long(b, p->log_level);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>log_security</td><td>");
    buffer_append_long(b, p->log_security);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_peer_func</td><td>");
    buffer_append_string_buffer(b, p->js_peer_func);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_grp_peer_func</td><td>");
    buffer_append_string_buffer(b, p->js_grp_peer_func);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_logout_code</td><td>");
    buffer_append_string_buffer(b, p->js_logout_code);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_maxwin_code</td><td>");
    buffer_append_string_buffer(b, p->js_maxwin_code);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_nocookies</td><td>");
    buffer_append_string_buffer(b, p->js_nocookies_code);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_notfound</td><td>");
    buffer_append_string_buffer(b, p->js_notfound_code);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_relogin</td><td>");
    buffer_append_string_buffer(b, p->js_relogin_func);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_redirect</td><td>");
    buffer_append_string_buffer(b, p->js_redirect_func);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_alert_id_func</td><td>");
    buffer_append_string_buffer(b, p->js_alert_id_func);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_no_guests</td><td>");
    buffer_append_string_buffer(b, p->js_no_guests);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>js_ping_code</td><td>");
    buffer_append_string_buffer(b, p->js_ping_code);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>send_pings</td><td>");
    buffer_append_long(b, p->send_pings);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>unw_prefix</td><td>");
    buffer_append_string_buffer(b, p->unw_prefix);
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>allow_peer_call</td><td>");
    for (i = 0; i < FDA_TYPES_MAX; i++) {
        if (p->allow_peer_call_mask & g_ev_mask_by_index[i]) {
            buffer_append_string(b, g_ev_name_by_index[i]);
            BUFFER_APPEND_STRING_CONST(b, " ");
        }
    }
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>check_user_ip</td><td>");
    buffer_append_string(b, p->check_user_ip ? "enable" : "disable");
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>admin_password</td><td>");
    buffer_append_string(b, p->admin_password->used > 0 ? "set" : "not set");
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "<tr><td>admin_ips</td><td>");
    for (i = 0; i < p->admin_allowed_used; i++) {
        buffer_append_string(b, inet_ntoa(p->admin_allowed_ips[i]));
        BUFFER_APPEND_STRING_CONST(b, " ");
    }
    BUFFER_APPEND_STRING_CONST(b, "</td></tr>");
    BUFFER_APPEND_STRING_CONST(b, "</table>");
    BUFFER_APPEND_STRING_CONST(b, "<h2>Logged Users</h2>");
    BUFFER_APPEND_STRING_CONST(b, "<table><tr><th>User ID</th><th>Data<th></tr>\n");

    for (user = p->users_by_sess; user != NULL; user = user->hh_sess.next) {
        print_user(b, user);
    }

    BUFFER_APPEND_STRING_CONST(b, "</table>");
    BUFFER_APPEND_STRING_CONST(b,
                               "<h4>Copyright &copy; 2007 <a href=\"http://www.refwell.com\">GDC / Refwell</a>"
                               " | <a href=\"http://www.refwell.com/blog\">Blog</a></h4>");
    BUFFER_APPEND_STRING_CONST(b, "</div>");
    BUFFER_APPEND_STRING_CONST(b,
                               "<div class=\"side\"><script type=\"text/javascript\" "
                               "src=\"http://widget.refwell.com/q2?account=gregd&amp;site=fdajax_info\"></script>");
    BUFFER_APPEND_STRING_CONST(b, "</div></body></html>\n");

    response_header_overwrite(srv, con, CONST_STR_LEN("Content-Type"), CONST_STR_LEN("text/html"));
    return 0;
}
