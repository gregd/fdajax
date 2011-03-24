#ifndef MOD_FDAJAX_DEF_H
#define MOD_FDAJAX_DEF_H

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>

#include "base.h"
#include "log.h"
#include "buffer.h"
#include "joblist.h"
#include "http_chunk.h"
#include "connections.h"
#include "response.h"
#include "splaytree.h"
#include "plugin.h"

#include "uthash.h"

#if defined(__linux__)
#define USE_TCP_INFO 1
#endif

#define TRUE    1
#define FALSE   0
#define min(a,b) ((a) < (b) ? (a) : (b))
#define timeval_less(t1, t2) ((t1.tv_sec < t2.tv_sec) || (t1.tv_sec == t2.tv_sec && t1.tv_usec < t2.tv_usec))
#define timeval_sub(t1, t2) do { t1.tv_sec -= t2.tv_sec; \
                                 if (t1.tv_usec < t2.tv_usec) \
                                 { t1.tv_sec -= 1; t1.tv_usec += 1000000 - t2.tv_usec; } \
                                 else { t1.tv_usec -= t2.tv_usec; } } while (0)

#define LOG_LEVEL_NONE      0
#define LOG_LEVEL_NORMAL    1
#define LOG_LEVEL_AVG       2
#define LOG_LEVEL_HIGH      3

#define log_info if (p->log_level >= LOG_LEVEL_NORMAL) log_error_write
#define log_avg  if (p->log_level >= LOG_LEVEL_AVG) log_error_write
#define log_high if (p->log_level >= LOG_LEVEL_HIGH) log_error_write
#define security_info if (p->log_security >= LOG_LEVEL_NORMAL) log_error_write
#define security_avg  if (p->log_security >= LOG_LEVEL_AVG) log_error_write
#define security_high if (p->log_security >= LOG_LEVEL_HIGH) log_error_write

#define FDA_CHECK_CON_INTERVAL 30

#define FDA_TYPES_MAX   32

#define FDA_EV_START    1
#define FDA_EV_END      15
#define FDA_EV_MAX      16
#define FDA_EV_UNW      0x00000001          /* recevie unwanted and alerts */
#define FDA_EV_GEN      0x00000002
#define FDA_EV_CHAT     0x00000004
#define FDA_EV_TOQ      0x00000008
#define FDA_EV_TWP      0x00000010
#define FDA_EV_SUO      0x00000020
#define FDA_EV_SUS      0x00000040
#define FDA_EV_SHO      0x00000080
#define FDA_EV_SHS      0x00000100
#define FDA_EV_SHC      0x00000200
#define FDA_EV_MES      0x00000400
#define FDA_EV_ORD      0x00000800
#define FDA_EV_CCD      0x00001000
#define FDA_EV_ITM      0x00002000
#define FDA_EV_LNE      0x00004000
#define FDA_EV_USR      0x00008000

#define FDA_MAX_GROUPS  16
#define FDA_GRP_START   16
#define FDA_GRP_END     31

#define FDA_GRP_MAIN    0x00010000
#define FDA_GRP_CHAT    0x00020000
#define FDA_GRP_QUES    0x00040000
#define FDA_GRP_ANSW    0x00080000
#define FDA_GRP_OFRS    0x00100000
#define FDA_GRP_PRIC    0x00200000
#define FDA_GRP_OPIN    0x00400000
#define FDA_GRP_USER    0x00800000
#define FDA_GRP_ORDS    0x01000000
#define FDA_GRP_GEIC    0x02000000
#define FDA_GRP_FEED    0x04000000
#define FDA_GRP_MESE    0x08000000
#define FDA_GRP_NETK    0x10000000
#define FDA_GRP_TASK    0x20000000
#define FDA_GRP_FRID    0x40000000
#define FDA_GRP_INFO    0x80000000

#define FDA_EV_UNW_INDEX    0
#define FDA_EV_GEN_INDEX    1
#define FDA_EV_CHAT_INDEX   2
#define FDA_EV_TOQ_INDEX    3
#define FDA_EV_TWP_INDEX    4
#define FDA_EV_SUO_INDEX    5
#define FDA_EV_SUS_INDEX    6
#define FDA_EV_SHO_INDEX    7
#define FDA_EV_SHS_INDEX    8
#define FDA_EV_SHC_INDEX    9
#define FDA_EV_MES_INDEX   10
#define FDA_EV_ORD_INDEX   11
#define FDA_EV_CCD_INDEX   12
#define FDA_EV_ITM_INDEX   13
#define FDA_EV_LNE_INDEX   14
#define FDA_EV_USR_INDEX   15
#define FDA_GRP_MAIN_INDEX 16
#define FDA_GRP_CHAT_INDEX 17
#define FDA_GRP_QUES_INDEX 18
#define FDA_GRP_ANSW_INDEX 19
#define FDA_GRP_OFRS_INDEX 20
#define FDA_GRP_PRIC_INDEX 21
#define FDA_GRP_OPIN_INDEX 22
#define FDA_GRP_USER_INDEX 23
#define FDA_GRP_ORDS_INDEX 24
#define FDA_GRP_GEIC_INDEX 25
#define FDA_GRP_FEED_INDEX 26
#define FDA_GRP_MESE_INDEX 27
#define FDA_GRP_NETK_INDEX 28
#define FDA_GRP_TASK_INDEX 29
#define FDA_GRP_FRID_INDEX 30
#define FDA_GRP_INFO_INDEX 31

#define FDA_IDS_MAX     16

#define SCRIPT_JS_BEGIN "<script type=\"text/javascript\">\n"
#define SCRIPT_JS_END   "</script>\n"
#define FDA_HTML_BEGIN      "<html><head><title>FdAjax</title></head><body>\n"

/* convert index to mask */
extern unsigned int g_ev_mask_by_index[FDA_TYPES_MAX];
extern char *g_ev_name_by_index[FDA_TYPES_MAX];

/* FDALive module commands */
enum gdc_cmd_t { cmd_none = 0,
                 cmd_wait,
                 cmd_stream,
                 cmd_push,
                 cmd_alert,
                 cmd_cancel,
                 cmd_chatsig,
                 cmd_check_user,
                 cmd_login,
                 cmd_logout,
                 cmd_info,
                 cmd_addchat,
                 cmd_rmchat
};

/* commands results */
enum cmd_res_t { cmdr_ok                = 0,
                 cmdr_mem_res_error     = 1,
                 cmdr_not_in_chat       = 2,
                 cmdr_mes_sent          = 3,
                 cmdr_user_not_logged   = 4,
                 cmdr_already_logged    = 5,
                 cmdr_login_ok          = 6,
                 cmdr_logout_ok         = 7,
                 cmdr_user_not_found    = 8,
                 cmdr_chat_peer_add     = 9,
                 cmdr_chat_peer_rm_1    = 10,
                 cmdr_chat_peer_rm_2    = 11,
                 cmdr_cuser_not_found   = 12,
                 cmdr_cuser_too_many    = 13,
                 cmdr_wrong_syntax      = 14,
                 cmdr_user_active       = 15,
                 cmdr_login_bad_id      = 16,
                 cmdr_login_old_sess    = 17,
                 cmdr_grp_not_found     = 18
};

enum auth_problem_t { authp_null_userid    = 0,
                      authp_user_not_found = 1,
                      authp_ip_addr        = 2,
                      authp_null_cookie    = 3,
                      authp_sessid         = 4,
                      authp_no_guests      = 5
};
typedef enum auth_problem_t* auth_problem_p;

/* Info about one user's browser window */
struct user_info_s;

struct events_info_s {
    unsigned int    types;
    int             ids[FDA_EV_MAX][FDA_IDS_MAX];
    unsigned char   ids_len[FDA_EV_MAX];
    unsigned char   count;
};
typedef struct events_info_s  events_info_t;
typedef struct events_info_s* evetns_info_p;

enum fda_win_type { fda_win_chunked = 0,
                    fda_win_stream = 1 };
struct win_info_s {
    int                 win_id;
    int                 win_st;
    int                 www_id;
    int                 send_count;
    unsigned int        last_alert;
    enum fda_win_type   win_type;
    struct user_info_s *owner;
    connection         *con;
    buffer             *to_send;
    events_info_t       ev;
    struct timeval      created_at;
    struct timeval      last_send;
    struct timeval      last_mes_at[FDA_TYPES_MAX];
};
typedef struct win_info_s   win_info_t;
typedef struct win_info_s*  win_info_p;

/* A message to a user */
struct mes_info_s {
    buffer             *mes;
    events_info_t       ev;
    int                 send_count;
    int                 to_remove;
    int                 amode;
    struct timeval      created_at;
    struct mes_info_s  *next, *prev;
};
typedef struct mes_info_s   mes_info_t;
typedef struct mes_info_s*  mes_info_p;

struct mes_list_s {
    mes_info_p      first_mes;
    mes_info_p      last_mes;
};
typedef struct mes_list_s   mes_list_t;
typedef struct mes_list_s*  mes_list_p;

/* An alert to a user */
struct alert_info_s {
    unsigned int        id;
    buffer             *mes;
    struct timeval      created_at;
};
typedef struct alert_info_s  alert_info_t;
typedef struct alert_info_s* alert_info_p;

#define PEERS_MAX   20
#define WINDOWS_MAX 5
#define ALERTS_MAX  10
#define SESS_ID_LEN_MAX  128
#define PASSWORD_MAX 128

/* Info about logged user */
struct user_info_s {
    int             user_id;
    struct in_addr  ipaddr;
    char            sess_id[SESS_ID_LEN_MAX];
    struct timeval  created_at;
    int             send_count;
    int             send_peer_count;
    unsigned int    last_alert;

    mes_list_t      mes_list;
    int             peers[PEERS_MAX];
    alert_info_t    alerts[ALERTS_MAX];
    win_info_p      windows[WINDOWS_MAX];

    UT_hash_handle hh_sess, hh_id;
};
typedef struct user_info_s  user_info_t;
typedef struct user_info_s* user_info_p;

/* Groups info */
struct win_node_s {
    win_info_p win;
    struct win_node_s *next;
    struct win_node_s *prev;
};
typedef struct win_node_s  win_node_t;
typedef struct win_node_s* win_node_p;

struct grp_info_s {
    int             grp_id;
    mes_list_t      mes_list;

    win_node_p      first_node;
    win_node_p      last_node;
};
typedef struct grp_info_s  grp_info_t;
typedef struct grp_info_s* grp_info_p;

/* Parsed user's request */
struct user_request_s {
    int             cs;
    enum gdc_cmd_t  cmd;
    events_info_t   ev;
    struct timeval  tv;
    int             user_id;
    int             peer_id;
    int             win_id;
    int             win_st;
    int             www_id;
    unsigned int    alert_id;
    unsigned int    amode;
    int             force_old_close;
    buffer         *mes;
    struct in_addr  ipaddr;
    buffer         *req_sess_id;
    char            sess_id_cookie[SESS_ID_LEN_MAX];
    char            admin_passwd[PASSWORD_MAX];
};
typedef struct user_request_s user_request_t;
typedef struct user_request_s* user_request_p;

typedef struct {
    buffer         *ext;
    buffer         *js_peer_func;
    buffer         *js_grp_peer_func;
    buffer         *js_logout_code;
    buffer         *js_maxwin_code;
    buffer         *js_nocookies_code;
    buffer         *js_notfound_code;
    buffer         *js_relogin_func;
    buffer         *js_redirect_func;
    buffer         *js_alert_id_func;
    buffer         *js_ping_code;
    buffer         *js_no_guests;
    buffer         *unw_prefix;
    buffer         *session_cookie;
    buffer         *html_begin;
    buffer         *admin_password;
    array          *admin_ips;
    array          *allow_peer_call;
    unsigned short  mes_live_max;
    unsigned short  win_timeout;
    unsigned short  log_level;
    unsigned short  log_security;
    unsigned short  merge_messages;
    unsigned short  send_redirects;
    unsigned short  check_user_ip;
    unsigned short  send_pings;
    unsigned short  allow_guests;
} plugin_config;

#define ALLOWED_MAX 100

typedef struct {
    PLUGIN_DATA;

    buffer *match_buf;
    plugin_config **config_storage;
    plugin_config conf;

    buffer         *js_peer_func;
    buffer         *js_grp_peer_func;
    buffer         *js_logout_code;
    buffer         *js_maxwin_code;
    buffer         *js_nocookies_code;
    buffer         *js_notfound_code;
    buffer         *js_relogin_func;
    buffer         *js_redirect_func;
    buffer         *js_alert_id_func;
    buffer         *js_ping_code;
    buffer         *js_no_guests;
    buffer         *unw_prefix;
    buffer         *session_cookie;
    buffer         *html_begin;
    buffer         *admin_password;
    int             log_security;
    int             log_level;
    int             mes_live_max;
    int             win_timeout;
    int             next_check_dcons;
    int             merge_messages;
    int             send_redirects;
    int             check_user_ip;
    int             send_pings;
    int             allow_guests;

    unsigned int    allow_peer_call_mask;
    struct in_addr  admin_allowed_ips[ALLOWED_MAX];
    size_t          admin_allowed_used;

    user_info_p     users_by_sess;
    user_info_p     users_by_id;

    grp_info_t      groups[FDA_MAX_GROUPS];
} plugin_data;

int mod_fdajax_pinit(user_request_p req);
int mod_fdajax_pexec(user_request_p req, char *start, size_t len);
int mod_fdajax_pfinish(user_request_p req);

int mod_fdajax_cinit(int *pcs);
int mod_fdajax_cexec(int *pcs, char *start, size_t len);
int mod_fdajax_cfinish(int *pcs);

int mod_fdajax_info(server *srv, plugin_data *p, connection *con);

void con_set_response(server *srv, plugin_data *p, connection *con, buffer *resp, int st);
void con_prepare_response(server *srv, plugin_data *p, connection *con, int st);
void con_finalize_response(server *srv, plugin_data *p, connection *con, int st);

void buffer_append_nl(buffer *buf);
char *tv2s(struct timeval atv);
int is_tcp_socket_open(server *srv, plugin_data *p, connection *con);

user_info_p    user_login(user_request_p req);
user_info_p    user_create_guest(connection *con, user_request_p req);
void           user_update_addr_and_sess(plugin_data *p, user_info_p user, user_request_p req);
void           user_update_id_and_ipaddr(plugin_data *p, user_info_p user, user_request_p req);
void           user_free(server *srv, plugin_data *p, connection *con, user_info_p user);
user_info_p    user_find_by_sess(plugin_data *p, char *s);
user_info_p    user_find_by_id(plugin_data *p, int user_id);
void           user_attach(server *srv, plugin_data *p, user_info_p new_user);
void           user_detach(server *srv, plugin_data *p, user_info_p user);
void           users_free(server *srv, plugin_data *p);
user_info_p    user_auth(server *srv, connection *con, plugin_data *p, user_info_p user, user_request_p req, auth_problem_p preason);
int            user_check(server *srv, plugin_data *p, connection *con, user_info_p user);

void           alert_free_slot(user_info_p user, size_t i);
unsigned int   alert_max_id(user_info_p user);
int            alert_cancel(user_info_p user, unsigned int id);
size_t         alert_find_slot(user_info_p user);
int            alert_add(server *srv, plugin_data *p, connection *con, user_info_p user, user_request_p req);
int            alert_add_from_mes(server *srv, plugin_data *p, user_info_p user, mes_info_p mes);
int            alert_append(server *srv, plugin_data *p, user_info_p user, buffer *buf, unsigned int last_id);
enum gdc_cmd_t alert_push(server *srv, plugin_data *p, user_info_p user);

enum gdc_cmd_t chat_add_peer(user_info_p user, int peer_id);
enum gdc_cmd_t chat_rm_peer(user_info_p user, int peer_id);
int            chat_access_peer(user_info_p user, int peer_id);

mes_info_p     message_init(user_request_p req);
mes_info_p     message_init_peer(server *srv, plugin_data *p, user_info_p user, user_request_p req);
void           message_free(mes_info_p mes);
void           message_list_init(mes_list_p list);
void           message_attach(mes_list_p list, mes_info_p mes);
void           message_detach(mes_list_p list, mes_info_p mes);
void           message_remove_all(mes_list_p list);
void           message_remove_old(server *srv, plugin_data *p, mes_list_p list);
int            message_append_to_win(server *srv, plugin_data *p, win_info_p win, mes_info_p mes, int ev_index, int nl);
int            message_append_as_unwanted(server *srv, plugin_data *p, win_info_p win, mes_info_p mes);
enum cmd_res_t message_send_pending(server *srv, plugin_data *p, mes_info_p mes, win_info_p win);
int            message_handle_unsend(server *srv, plugin_data *p, user_info_p user, mes_info_p mes, win_info_p recv_win);
int            message_check_unsend(server *srv, plugin_data *p, user_info_p user, win_info_p recv_win);
enum gdc_cmd_t message_push(server *srv, plugin_data *p, user_info_p user, mes_info_p mes);
int            message_grp_push(server *srv, plugin_data *p, grp_info_p grp, mes_info_p mes);

win_info_p     window_find(connection *con, user_info_p user, user_request_p req);
int            window_should_redirect(server *srv, plugin_data *p, connection *con, user_info_p user, user_request_p req);
win_info_p     window_init(plugin_data *p, connection *con, user_info_p user, user_request_p req, enum fda_win_type win_type, int slot);
void           window_free(plugin_data *p, win_info_p win);
int            window_find_slot(user_info_p user);
void           window_close_all(server *srv, plugin_data *p, connection *con, user_info_p user);
void           window_close(server *srv, plugin_data *p, user_info_p user, win_info_p win, buffer *close_message);
int            window_remove_old(server *srv, plugin_data *p, connection *con, user_info_p user);
void           window_update_last_send(win_info_p win, struct timeval tv);
int            window_is_old(win_info_p win, struct timeval now, unsigned long win_timeout);
buffer *       window_get_buffer(win_info_p win);
void           window_append_string(win_info_p win, char *s);
void           window_append_string_buffer(win_info_p win, buffer *sb);
win_info_p     window_first_with_unw(server *srv, plugin_data *p, user_info_p user);
int            window_can_receive(win_info_p win, mes_info_p mes, int check_time);
int            window_check_groups(server *srv, plugin_data *p, win_info_p win);
int            window_flush_all(server *srv, plugin_data *p, user_info_p user);
int            window_flush(server *srv, plugin_data *p, win_info_p win);

int            event_bit_to_index(unsigned int ev);
int            event_check_ids(win_info_p win, mes_info_p mes, int ev_nr);
int            event_find_index_by_name(char *s);

void           group_init(grp_info_p grp, int i);
grp_info_p     group_find(plugin_data *p, unsigned int ev);
void           group_add_window(grp_info_p grp, win_info_p win);
void           group_rm_window(grp_info_p grp, win_info_p win);
void           group_remove_old_mes(server *srv, plugin_data *p);

#endif
