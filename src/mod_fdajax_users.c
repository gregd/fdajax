#include "mod_fdajax_defs.h"

user_info_p user_login(user_request_p req)
{
    user_info_p user = calloc(1, sizeof(user_info_t));

    if (!user) {
        return NULL;
    }
    user->user_id = req->user_id;
    user->ipaddr.s_addr = htonl(req->ipaddr.s_addr);
    strncpy(user->sess_id, req->req_sess_id->ptr, min(SESS_ID_LEN_MAX - 1, req->req_sess_id->used));
    user->sess_id[min(SESS_ID_LEN_MAX - 1, req->req_sess_id->used)] = 0;
    gettimeofday(&(user->created_at), 0);
    user->send_count = 0;
    user->send_peer_count = 0;
    user->last_alert = 0;
    bzero(user->alerts, sizeof(user->alerts));
    message_list_init(&(user->mes_list));
    return user;
}

user_info_p user_create_guest(connection *con, user_request_p req)
{
    user_info_p user = calloc(1, sizeof(user_info_t));

    if (!user) {
        return NULL;
    }
    user->user_id = 0;
    user->ipaddr.s_addr = con->dst_addr.ipv4.sin_addr.s_addr;
    strcpy(user->sess_id, req->sess_id_cookie);
    gettimeofday(&(user->created_at), 0);
    user->send_count = 0;
    user->send_peer_count = 0;
    user->last_alert = 0;
    bzero(user->alerts, sizeof(user->alerts));
    message_list_init(&(user->mes_list));
    return user;
}


void user_update_addr_and_sess(plugin_data *p, user_info_p user, user_request_p req)
{
    user->ipaddr.s_addr = htonl(req->ipaddr.s_addr);
    if (strcmp(user->sess_id, req->req_sess_id->ptr) != 0) {
        HASH_DELETE(hh_sess, p->users_by_sess, user);
        strncpy(user->sess_id, req->req_sess_id->ptr, min(SESS_ID_LEN_MAX - 1, req->req_sess_id->used));
        user->sess_id[min(SESS_ID_LEN_MAX - 1, req->req_sess_id->used)] = 0;
        HASH_ADD(hh_sess, p->users_by_sess, sess_id, strlen(user->sess_id), user);
    }
}

void user_update_id_and_ipaddr(plugin_data *p, user_info_p user, user_request_p req)
{
    UNUSED(p);
    user->user_id = req->user_id;
    user->ipaddr.s_addr = htonl(req->ipaddr.s_addr);
    if (user->user_id > 0) {
        HASH_ADD(hh_id, p->users_by_id, user_id, sizeof(int), user);
    }
}

void user_free(server *srv, plugin_data *p, connection *con, user_info_p user)
{
    message_remove_all(&(user->mes_list));
    window_close_all(srv, p, con, user);
    free(user);
}

void users_free(server *srv, plugin_data *p)
{
    user_info_p user;

    UNUSED(srv);
    log_info(srv, __FILE__, __LINE__, "s", "free_users");

    while (NULL != (user = p->users_by_sess)) {
        user_detach(srv, p, user);
        user_free(srv, p, NULL, user);
    }
}

user_info_p user_find_by_sess(plugin_data *p, char *s)
{
    user_info_p user;
    if (NULL == s) {
        return NULL;
    }
    HASH_FIND(hh_sess, p->users_by_sess, s, (int)strlen(s), user);
    return user;
}

user_info_p user_find_by_id(plugin_data *p, int user_id)
{
    user_info_p user;
    if (0 == user_id) {
        return NULL;
    }
    HASH_FIND(hh_id, p->users_by_id, &user_id, sizeof(int), user);
    return user;
}

void user_attach(server *srv, plugin_data *p, user_info_p new_user)
{
    UNUSED(srv);
    if (NULL == new_user) {
        return;
    }
    if (new_user->user_id > 0) {
        HASH_ADD(hh_id, p->users_by_id, user_id, sizeof(int), new_user);
    }
    HASH_ADD(hh_sess, p->users_by_sess, sess_id, strlen(new_user->sess_id), new_user);
}

void user_detach(server *srv, plugin_data *p, user_info_p old_user)
{
    UNUSED(srv);
    if (old_user->user_id > 0) {
        HASH_DELETE(hh_id, p->users_by_id, old_user);
    }
    HASH_DELETE(hh_sess, p->users_by_sess, old_user);
}

user_info_p user_auth(server *srv, connection *con, plugin_data *p, user_info_p user, user_request_p req, auth_problem_p preason)
{
    if (user->user_id > 0) {
        if (req->user_id == 0 || req->user_id != user->user_id) {
            *preason = authp_null_userid;
            security_avg(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf,
                         "security: auth_user wrong uid", user->user_id, "req_uid", req->user_id);
            return NULL;
        }
    } else {
        if (req->user_id != 0) {
            *preason = authp_null_userid;
            security_avg(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf,
                         "security: auth_user guest cannot have uid ", req->user_id);
            return NULL;
        }
    }
    if (p->check_user_ip) {
        if (con->dst_addr.ipv4.sin_addr.s_addr != user->ipaddr.s_addr) {
            *preason = authp_ip_addr;
            security_avg(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf,
                         "security: auth_user ip check failed uid ", user->user_id);
            return NULL;
        }
    }
    if (strcmp(req->sess_id_cookie, user->sess_id) != 0) {
        *preason = authp_sessid;
        security_avg(srv, __FILE__, __LINE__, "bsd", con->dst_addr_buf,
                     "security: auth_user sess_id different uid", user->user_id);
        return NULL;
    }
    return user;
}

int user_check(server *srv, plugin_data *p, connection *con, user_info_p user)
{
    int open_win_count;
    message_remove_old(srv, p, &(user->mes_list));
    open_win_count = window_remove_old(srv, p, con, user);
    return open_win_count;
}

