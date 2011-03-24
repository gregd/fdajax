#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mod_fdajax_defs.h"

#define INIT_EVENT(mask, index) req->ev.count++; req->ev.types |= mask; cur_ev_nr = index; req->ev.ids_len[index] = 0
#define CUR_ID_TAB_LEN req->ev.ids_len[cur_ev_nr]

%%{
  machine fdamod_parser;

  uint = digit{1,10} >{ cur_int = 0; } @{ cur_int = cur_int * 10 + (fc - '0'); } ;

  user_id =  'user_id='  uint %{ req->user_id = cur_int; } ;
  peer_id =  'peer_id='  uint %{ req->peer_id = cur_int; } ;
  win_id =   'win_id='   uint %{ req->win_id = cur_int; } ;
  win_st =   'win_st='   uint %{ req->win_st = cur_int; } ;
  sec =      'sec='      uint %{ req->tv.tv_sec = cur_int; } ;
  usec =     'usec='     uint %{ req->tv.tv_usec = cur_int; } ;
  alert_id = 'alert_id=' uint %{ req->alert_id = cur_int; } ;
  amode =    'amode='    uint %{ req->amode = cur_int; } ;
  force =    'force='    uint %{ req->force_old_close = cur_int; } ;

  cmd = 'cmd=' ( 'wait'     %{ req->cmd = cmd_wait; } |
                 'push'     %{ req->cmd = cmd_push; } |
                 'alert'    %{ req->cmd = cmd_alert; } |
                 'stream'   %{ req->cmd = cmd_stream; } |
                 'cancel'   %{ req->cmd = cmd_cancel; } |
                 'check'    %{ req->cmd = cmd_check_user; } |
                 'login'    %{ req->cmd = cmd_login; } |
                 'logout'   %{ req->cmd = cmd_logout; } |
                 'info'     %{ req->cmd = cmd_info; } |
                 'add_chat' %{ req->cmd = cmd_addchat; } |
                 'rm_chat'  %{ req->cmd = cmd_rmchat; } |
                 'chat_sig' %{ req->cmd = cmd_chatsig; } ) ;

  action add_id {
      if (CUR_ID_TAB_LEN < FDA_IDS_MAX) {
          req->ev.ids[cur_ev_nr][CUR_ID_TAB_LEN++] = cur_int;
      } else {
          CUR_ID_TAB_LEN = 0;
      }
  }

  ev_model = ('unw'  %{ INIT_EVENT(FDA_EV_UNW, FDA_EV_UNW_INDEX); } |
              'gen'  %{ INIT_EVENT(FDA_EV_GEN, FDA_EV_GEN_INDEX); } |
              'chat' %{ INIT_EVENT(FDA_EV_CHAT, FDA_EV_CHAT_INDEX); } |
              'toq'  %{ INIT_EVENT(FDA_EV_TOQ, FDA_EV_TOQ_INDEX); } |
              'twp'  %{ INIT_EVENT(FDA_EV_TWP, FDA_EV_TWP_INDEX); } |
              'suo'  %{ INIT_EVENT(FDA_EV_SUO, FDA_EV_SUO_INDEX); } |
              'sus'  %{ INIT_EVENT(FDA_EV_SUS, FDA_EV_SUS_INDEX); } |
              'sho'  %{ INIT_EVENT(FDA_EV_SHO, FDA_EV_SHO_INDEX); } |
              'shs'  %{ INIT_EVENT(FDA_EV_SHS, FDA_EV_SHS_INDEX); } |
              'shc'  %{ INIT_EVENT(FDA_EV_SHC, FDA_EV_SHC_INDEX); } |
              'mes'  %{ INIT_EVENT(FDA_EV_MES, FDA_EV_MES_INDEX); } |
              'ord'  %{ INIT_EVENT(FDA_EV_ORD, FDA_EV_ORD_INDEX); } |
              'ccd'  %{ INIT_EVENT(FDA_EV_CCD, FDA_EV_CCD_INDEX); } |
              'itm'  %{ INIT_EVENT(FDA_EV_ITM, FDA_EV_ITM_INDEX); } |
              'lne'  %{ INIT_EVENT(FDA_EV_LNE, FDA_EV_LNE_INDEX); } |
              'usr'  %{ INIT_EVENT(FDA_EV_USR, FDA_EV_USR_INDEX); } )
                     ( ('%2C' | '%2c' | ',') uint %add_id ) * ;

  ev_group = ('main'  %{ INIT_EVENT(FDA_GRP_MAIN, FDA_GRP_MAIN_INDEX); } |
              'gchat' %{ INIT_EVENT(FDA_GRP_CHAT, FDA_GRP_CHAT_INDEX); } |
              'ques'  %{ INIT_EVENT(FDA_GRP_QUES, FDA_GRP_QUES_INDEX); } |
              'answ'  %{ INIT_EVENT(FDA_GRP_ANSW, FDA_GRP_ANSW_INDEX); } |
              'ofrs'  %{ INIT_EVENT(FDA_GRP_OFRS, FDA_GRP_OFRS_INDEX); } |
              'pric'  %{ INIT_EVENT(FDA_GRP_PRIC, FDA_GRP_PRIC_INDEX); } |
              'opin'  %{ INIT_EVENT(FDA_GRP_OPIN, FDA_GRP_OPIN_INDEX); } |
              'users' %{ INIT_EVENT(FDA_GRP_USER, FDA_GRP_USER_INDEX); } |
              'ords'  %{ INIT_EVENT(FDA_GRP_ORDS, FDA_GRP_ORDS_INDEX); } |
              'geic'  %{ INIT_EVENT(FDA_GRP_GEIC, FDA_GRP_GEIC_INDEX); } |
              'feed'  %{ INIT_EVENT(FDA_GRP_FEED, FDA_GRP_FEED_INDEX); } |
              'mese'  %{ INIT_EVENT(FDA_GRP_MESE, FDA_GRP_MESE_INDEX); } |
              'netk'  %{ INIT_EVENT(FDA_GRP_NETK, FDA_GRP_NETK_INDEX); } |
              'task'  %{ INIT_EVENT(FDA_GRP_TASK, FDA_GRP_TASK_INDEX); } |
              'frid'  %{ INIT_EVENT(FDA_GRP_FRID, FDA_GRP_FRID_INDEX); } |
              'info'  %{ INIT_EVENT(FDA_GRP_INFO, FDA_GRP_INFO_INDEX); } ) ;

  ev_type = ev_model | ev_group;
  ev_types = ('types=' ev_type (('%7C' | '%7c' | '|') ev_type) * ) ;

  # IP address in host byte order
  ipaddr = 'ip_addr=' uint %{ if (0xff < cur_int) fbreak; ip_addr = ip_addr | (cur_int << 24); } '.'
                      uint %{ if (0xff < cur_int) fbreak; ip_addr = ip_addr | (cur_int << 16); } '.'
                      uint %{ if (0xff < cur_int) fbreak; ip_addr = ip_addr | (cur_int << 8); }'.'
                      uint %{ if (0xff < cur_int) fbreak; ip_addr = ip_addr | (cur_int << 0);
                             req->ipaddr.s_addr = ip_addr; ip_addr = 0; } ;

  # Decode url encoded string
  action init_mes {
      if (req->mes) {
          fbreak;
      }
      req->mes = buffer_init();
      /* TODO is mem allocated ? */
      buffer_prepare_append(req->mes, len);
      buf = req->mes->ptr;
      ppos = &(req->mes->used);
  }
  action init_hex {
      hex = phex << 4;
  }
  action finish_hex {
      hex = hex | phex;
      buf[(*ppos)++] = hex;
  }
  action append_char {
      buf[(*ppos)++] = fc;
  }
  action append_sp {
      buf[(*ppos)++] = ' ';
  }
  action finish_mes {
      buf[(*ppos)++] = 0;
  }

  hex = [a-f] @{ phex = fc - 'a' + 10; } |
        [A-F] @{ phex = fc - 'A' + 10; } |
        [0-9] @{ phex = fc - '0'; } ;

  mes = 'mes=' ( ('%' hex %init_hex hex %finish_hex ) |
                 ('+' @append_sp ) |
                 ([^&%+\0] @append_char) ) + >init_mes %finish_mes ;

  action set_mark {
      mark = fpc;
  }
  action copy_sessid {
      if (req->req_sess_id) {
          fbreak;
      }
      req->req_sess_id = buffer_init();
      buffer_copy_string_len(req->req_sess_id, mark, fpc - mark);
  }
  sessid = 'sess_id=' [a-zA-Z0-9]+ >set_mark %copy_sessid ;

  action copy_admin_passwd {
      if (req->admin_passwd[0]) {
          fbreak;
      }
      j = min(fpc - mark, PASSWORD_MAX - 1);
      strncpy(req->admin_passwd, mark, j);
      req->admin_passwd[j] = 0;
  }
  admin_passwd = 'admin_passwd=' [a-zA-Z0-9]+ >set_mark %copy_admin_passwd ;

  dummy = '_=' ;

  arg = cmd | user_id | peer_id | win_id | win_st | ev_types | mes | sessid | ipaddr | sec | usec | alert_id | force | amode |
        admin_passwd | dummy ;
  main := arg ('&' arg)* 0 ;

}%%

%% write data;

int mod_fdajax_pinit(user_request_p req)
{
    int cs = 0;
    %% write init;
    req->cs = cs;
    req->cmd =              0;
    req->ev.types =         0;
    req->ev.count =         0;
    req->tv.tv_sec =        0;
    req->tv.tv_usec =       0;
    req->win_id =           0;
    req->win_st =           0;
    req->www_id =           0;
    req->alert_id =         0;
    req->amode =            0;
    req->force_old_close =  0;
    req->user_id =          0;
    req->peer_id =          0;
    req->ipaddr.s_addr =    INADDR_NONE;
    req->mes =              NULL;
    req->req_sess_id =      NULL;
    req->sess_id_cookie[0] = 0;
    req->admin_passwd[0]   = 0;
    return 1;
}

int mod_fdajax_pexec(user_request_p req, char *start, size_t len)
{
    char *p, *pe, *mark = 0, *buf = 0;
    unsigned char phex = 0, hex = 0;
    unsigned int cur_int = 0;
    unsigned int ip_addr = 0;
    size_t j, *ppos = 0;
    int cur_ev_nr = 0;
    int cs = req->cs;

    assert(*(start + len) == 0);
    p = start;
    pe = start + len + 1;
    %% write exec;
    req->cs = cs;

    return 1;
}

int mod_fdajax_pfinish(user_request_p req)
{
  int cs = req->cs;
  %% write eof;
  req->cs = cs;

  if (req->cs == fdamod_parser_error) {
      return -1;
  } else if (req->cs >= fdamod_parser_first_final) {
      return 1;
  }
  return 0;
}

