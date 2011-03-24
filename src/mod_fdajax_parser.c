#line 1 "mod_fdajax_parser.rl"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mod_fdajax_defs.h"

#define INIT_EVENT(mask, index) req->ev.count++; req->ev.types |= mask; cur_ev_nr = index; req->ev.ids_len[index] = 0
#define CUR_ID_TAB_LEN req->ev.ids_len[cur_ev_nr]

#line 155 "mod_fdajax_parser.rl"



#line 16 "mod_fdajax_parser.c"
static const int fdamod_parser_start = 1;
static const int fdamod_parser_first_final = 399;
static const int fdamod_parser_error = 0;

static const int fdamod_parser_en_main = 1;

#line 158 "mod_fdajax_parser.rl"

int mod_fdajax_pinit(user_request_p req)
{
    int cs = 0;
    
#line 29 "mod_fdajax_parser.c"
	{
	cs = fdamod_parser_start;
	}
#line 163 "mod_fdajax_parser.rl"
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
    
#line 70 "mod_fdajax_parser.c"
	{
	if ( p == pe )
		goto _out;
	switch ( cs )
	{
tr31:
#line 139 "mod_fdajax_parser.rl"
	{
      if (req->admin_passwd[0]) {
          goto _out1;
      }
      j = min(p - mark, PASSWORD_MAX - 1);
      strncpy(req->admin_passwd, mark, j);
      req->admin_passwd[j] = 0;
  }
	goto st1;
tr42:
#line 21 "mod_fdajax_parser.rl"
	{ req->alert_id = cur_int; }
	goto st1;
tr58:
#line 22 "mod_fdajax_parser.rl"
	{ req->amode = cur_int; }
	goto st1;
tr88:
#line 34 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_addchat; }
	goto st1;
tr93:
#line 27 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_alert; }
	goto st1;
tr101:
#line 29 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_cancel; }
	goto st1;
tr110:
#line 36 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_chatsig; }
	goto st1;
tr114:
#line 30 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_check_user; }
	goto st1;
tr119:
#line 33 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_info; }
	goto st1;
tr126:
#line 31 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_login; }
	goto st1;
tr130:
#line 32 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_logout; }
	goto st1;
tr135:
#line 26 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_push; }
	goto st1;
tr143:
#line 35 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_rmchat; }
	goto st1;
tr150:
#line 28 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_stream; }
	goto st1;
tr155:
#line 25 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_wait; }
	goto st1;
tr163:
#line 23 "mod_fdajax_parser.rl"
	{ req->force_old_close = cur_int; }
	goto st1;
tr191:
#line 88 "mod_fdajax_parser.rl"
	{ if (0xff < cur_int) goto _out1; ip_addr = ip_addr | (cur_int << 0);
                             req->ipaddr.s_addr = ip_addr; ip_addr = 0; }
	goto st1;
tr234:
#line 115 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = 0;
  }
	goto st1;
tr245:
#line 105 "mod_fdajax_parser.rl"
	{
      hex = hex | phex;
      buf[(*ppos)++] = hex;
  }
#line 115 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = 0;
  }
	goto st1;
tr256:
#line 16 "mod_fdajax_parser.rl"
	{ req->peer_id = cur_int; }
	goto st1;
tr272:
#line 19 "mod_fdajax_parser.rl"
	{ req->tv.tv_sec = cur_int; }
	goto st1;
tr289:
#line 130 "mod_fdajax_parser.rl"
	{
      if (req->req_sess_id) {
          goto _out1;
      }
      req->req_sess_id = buffer_init();
      buffer_copy_string_len(req->req_sess_id, mark, p - mark);
  }
	goto st1;
tr315:
#line 67 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ANSW, FDA_GRP_ANSW_INDEX); }
	goto st1;
tr323:
#line 58 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CCD, FDA_EV_CCD_INDEX); }
	goto st1;
tr331:
#line 38 "mod_fdajax_parser.rl"
	{
      if (CUR_ID_TAB_LEN < FDA_IDS_MAX) {
          req->ev.ids[cur_ev_nr][CUR_ID_TAB_LEN++] = cur_int;
      } else {
          CUR_ID_TAB_LEN = 0;
      }
  }
	goto st1;
tr347:
#line 48 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CHAT, FDA_EV_CHAT_INDEX); }
	goto st1;
tr356:
#line 74 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FEED, FDA_GRP_FEED_INDEX); }
	goto st1;
tr362:
#line 78 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FRID, FDA_GRP_FRID_INDEX); }
	goto st1;
tr371:
#line 65 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_CHAT, FDA_GRP_CHAT_INDEX); }
	goto st1;
tr378:
#line 73 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_GEIC, FDA_GRP_GEIC_INDEX); }
	goto st1;
tr382:
#line 47 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_GEN, FDA_EV_GEN_INDEX); }
	goto st1;
tr391:
#line 79 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_INFO, FDA_GRP_INFO_INDEX); }
	goto st1;
tr396:
#line 59 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ITM, FDA_EV_ITM_INDEX); }
	goto st1;
tr403:
#line 60 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_LNE, FDA_EV_LNE_INDEX); }
	goto st1;
tr412:
#line 64 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MAIN, FDA_GRP_MAIN_INDEX); }
	goto st1;
tr417:
#line 56 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_MES, FDA_EV_MES_INDEX); }
	goto st1;
tr423:
#line 75 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MESE, FDA_GRP_MESE_INDEX); }
	goto st1;
tr430:
#line 76 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_NETK, FDA_GRP_NETK_INDEX); }
	goto st1;
tr439:
#line 68 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OFRS, FDA_GRP_OFRS_INDEX); }
	goto st1;
tr445:
#line 70 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OPIN, FDA_GRP_OPIN_INDEX); }
	goto st1;
tr450:
#line 57 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ORD, FDA_EV_ORD_INDEX); }
	goto st1;
tr456:
#line 72 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ORDS, FDA_GRP_ORDS_INDEX); }
	goto st1;
tr463:
#line 69 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_PRIC, FDA_GRP_PRIC_INDEX); }
	goto st1;
tr470:
#line 66 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_QUES, FDA_GRP_QUES_INDEX); }
	goto st1;
tr479:
#line 55 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHC, FDA_EV_SHC_INDEX); }
	goto st1;
tr484:
#line 53 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHO, FDA_EV_SHO_INDEX); }
	goto st1;
tr489:
#line 54 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHS, FDA_EV_SHS_INDEX); }
	goto st1;
tr496:
#line 51 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUO, FDA_EV_SUO_INDEX); }
	goto st1;
tr501:
#line 52 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUS, FDA_EV_SUS_INDEX); }
	goto st1;
tr511:
#line 77 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_TASK, FDA_GRP_TASK_INDEX); }
	goto st1;
tr516:
#line 49 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TOQ, FDA_EV_TOQ_INDEX); }
	goto st1;
tr522:
#line 50 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TWP, FDA_EV_TWP_INDEX); }
	goto st1;
tr530:
#line 46 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_UNW, FDA_EV_UNW_INDEX); }
	goto st1;
tr539:
#line 71 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_USER, FDA_GRP_USER_INDEX); }
	goto st1;
tr543:
#line 61 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_USR, FDA_EV_USR_INDEX); }
	goto st1;
tr553:
#line 20 "mod_fdajax_parser.rl"
	{ req->tv.tv_usec = cur_int; }
	goto st1;
tr569:
#line 15 "mod_fdajax_parser.rl"
	{ req->user_id = cur_int; }
	goto st1;
tr588:
#line 17 "mod_fdajax_parser.rl"
	{ req->win_id = cur_int; }
	goto st1;
tr602:
#line 18 "mod_fdajax_parser.rl"
	{ req->win_st = cur_int; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _out1;
case 1:
#line 345 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 95: goto st2;
		case 97: goto st4;
		case 99: goto st51;
		case 102: goto st116;
		case 105: goto st132;
		case 109: goto st183;
		case 112: goto st191;
		case 115: goto st209;
		case 116: goto st230;
		case 117: goto st339;
		case 119: goto st369;
	}
	goto st0;
st0:
	goto _out0;
st2:
	if ( ++p == pe )
		goto _out2;
case 2:
	if ( (*p) == 61 )
		goto st3;
	goto st0;
st3:
	if ( ++p == pe )
		goto _out3;
case 3:
	switch( (*p) ) {
		case 0: goto st399;
		case 38: goto st1;
	}
	goto st0;
tr30:
#line 139 "mod_fdajax_parser.rl"
	{
      if (req->admin_passwd[0]) {
          goto _out399;
      }
      j = min(p - mark, PASSWORD_MAX - 1);
      strncpy(req->admin_passwd, mark, j);
      req->admin_passwd[j] = 0;
  }
	goto st399;
tr41:
#line 21 "mod_fdajax_parser.rl"
	{ req->alert_id = cur_int; }
	goto st399;
tr57:
#line 22 "mod_fdajax_parser.rl"
	{ req->amode = cur_int; }
	goto st399;
tr87:
#line 34 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_addchat; }
	goto st399;
tr92:
#line 27 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_alert; }
	goto st399;
tr100:
#line 29 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_cancel; }
	goto st399;
tr109:
#line 36 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_chatsig; }
	goto st399;
tr113:
#line 30 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_check_user; }
	goto st399;
tr118:
#line 33 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_info; }
	goto st399;
tr125:
#line 31 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_login; }
	goto st399;
tr129:
#line 32 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_logout; }
	goto st399;
tr134:
#line 26 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_push; }
	goto st399;
tr142:
#line 35 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_rmchat; }
	goto st399;
tr149:
#line 28 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_stream; }
	goto st399;
tr154:
#line 25 "mod_fdajax_parser.rl"
	{ req->cmd = cmd_wait; }
	goto st399;
tr162:
#line 23 "mod_fdajax_parser.rl"
	{ req->force_old_close = cur_int; }
	goto st399;
tr190:
#line 88 "mod_fdajax_parser.rl"
	{ if (0xff < cur_int) goto _out399; ip_addr = ip_addr | (cur_int << 0);
                             req->ipaddr.s_addr = ip_addr; ip_addr = 0; }
	goto st399;
tr232:
#line 115 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = 0;
  }
	goto st399;
tr243:
#line 105 "mod_fdajax_parser.rl"
	{
      hex = hex | phex;
      buf[(*ppos)++] = hex;
  }
#line 115 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = 0;
  }
	goto st399;
tr255:
#line 16 "mod_fdajax_parser.rl"
	{ req->peer_id = cur_int; }
	goto st399;
tr271:
#line 19 "mod_fdajax_parser.rl"
	{ req->tv.tv_sec = cur_int; }
	goto st399;
tr288:
#line 130 "mod_fdajax_parser.rl"
	{
      if (req->req_sess_id) {
          goto _out399;
      }
      req->req_sess_id = buffer_init();
      buffer_copy_string_len(req->req_sess_id, mark, p - mark);
  }
	goto st399;
tr313:
#line 67 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ANSW, FDA_GRP_ANSW_INDEX); }
	goto st399;
tr321:
#line 58 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CCD, FDA_EV_CCD_INDEX); }
	goto st399;
tr329:
#line 38 "mod_fdajax_parser.rl"
	{
      if (CUR_ID_TAB_LEN < FDA_IDS_MAX) {
          req->ev.ids[cur_ev_nr][CUR_ID_TAB_LEN++] = cur_int;
      } else {
          CUR_ID_TAB_LEN = 0;
      }
  }
	goto st399;
tr345:
#line 48 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CHAT, FDA_EV_CHAT_INDEX); }
	goto st399;
tr354:
#line 74 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FEED, FDA_GRP_FEED_INDEX); }
	goto st399;
tr360:
#line 78 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FRID, FDA_GRP_FRID_INDEX); }
	goto st399;
tr369:
#line 65 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_CHAT, FDA_GRP_CHAT_INDEX); }
	goto st399;
tr376:
#line 73 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_GEIC, FDA_GRP_GEIC_INDEX); }
	goto st399;
tr380:
#line 47 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_GEN, FDA_EV_GEN_INDEX); }
	goto st399;
tr389:
#line 79 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_INFO, FDA_GRP_INFO_INDEX); }
	goto st399;
tr394:
#line 59 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ITM, FDA_EV_ITM_INDEX); }
	goto st399;
tr401:
#line 60 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_LNE, FDA_EV_LNE_INDEX); }
	goto st399;
tr410:
#line 64 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MAIN, FDA_GRP_MAIN_INDEX); }
	goto st399;
tr415:
#line 56 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_MES, FDA_EV_MES_INDEX); }
	goto st399;
tr421:
#line 75 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MESE, FDA_GRP_MESE_INDEX); }
	goto st399;
tr428:
#line 76 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_NETK, FDA_GRP_NETK_INDEX); }
	goto st399;
tr437:
#line 68 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OFRS, FDA_GRP_OFRS_INDEX); }
	goto st399;
tr443:
#line 70 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OPIN, FDA_GRP_OPIN_INDEX); }
	goto st399;
tr448:
#line 57 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ORD, FDA_EV_ORD_INDEX); }
	goto st399;
tr454:
#line 72 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ORDS, FDA_GRP_ORDS_INDEX); }
	goto st399;
tr461:
#line 69 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_PRIC, FDA_GRP_PRIC_INDEX); }
	goto st399;
tr468:
#line 66 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_QUES, FDA_GRP_QUES_INDEX); }
	goto st399;
tr477:
#line 55 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHC, FDA_EV_SHC_INDEX); }
	goto st399;
tr482:
#line 53 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHO, FDA_EV_SHO_INDEX); }
	goto st399;
tr487:
#line 54 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHS, FDA_EV_SHS_INDEX); }
	goto st399;
tr494:
#line 51 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUO, FDA_EV_SUO_INDEX); }
	goto st399;
tr499:
#line 52 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUS, FDA_EV_SUS_INDEX); }
	goto st399;
tr509:
#line 77 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_TASK, FDA_GRP_TASK_INDEX); }
	goto st399;
tr514:
#line 49 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TOQ, FDA_EV_TOQ_INDEX); }
	goto st399;
tr520:
#line 50 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TWP, FDA_EV_TWP_INDEX); }
	goto st399;
tr528:
#line 46 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_UNW, FDA_EV_UNW_INDEX); }
	goto st399;
tr537:
#line 71 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_USER, FDA_GRP_USER_INDEX); }
	goto st399;
tr541:
#line 61 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_USR, FDA_EV_USR_INDEX); }
	goto st399;
tr552:
#line 20 "mod_fdajax_parser.rl"
	{ req->tv.tv_usec = cur_int; }
	goto st399;
tr568:
#line 15 "mod_fdajax_parser.rl"
	{ req->user_id = cur_int; }
	goto st399;
tr587:
#line 17 "mod_fdajax_parser.rl"
	{ req->win_id = cur_int; }
	goto st399;
tr601:
#line 18 "mod_fdajax_parser.rl"
	{ req->win_st = cur_int; }
	goto st399;
st399:
	if ( ++p == pe )
		goto _out399;
case 399:
#line 647 "mod_fdajax_parser.c"
	goto st0;
st4:
	if ( ++p == pe )
		goto _out4;
case 4:
	switch( (*p) ) {
		case 100: goto st5;
		case 108: goto st18;
		case 109: goto st36;
	}
	goto st0;
st5:
	if ( ++p == pe )
		goto _out5;
case 5:
	if ( (*p) == 109 )
		goto st6;
	goto st0;
st6:
	if ( ++p == pe )
		goto _out6;
case 6:
	if ( (*p) == 105 )
		goto st7;
	goto st0;
st7:
	if ( ++p == pe )
		goto _out7;
case 7:
	if ( (*p) == 110 )
		goto st8;
	goto st0;
st8:
	if ( ++p == pe )
		goto _out8;
case 8:
	if ( (*p) == 95 )
		goto st9;
	goto st0;
st9:
	if ( ++p == pe )
		goto _out9;
case 9:
	if ( (*p) == 112 )
		goto st10;
	goto st0;
st10:
	if ( ++p == pe )
		goto _out10;
case 10:
	if ( (*p) == 97 )
		goto st11;
	goto st0;
st11:
	if ( ++p == pe )
		goto _out11;
case 11:
	if ( (*p) == 115 )
		goto st12;
	goto st0;
st12:
	if ( ++p == pe )
		goto _out12;
case 12:
	if ( (*p) == 115 )
		goto st13;
	goto st0;
st13:
	if ( ++p == pe )
		goto _out13;
case 13:
	if ( (*p) == 119 )
		goto st14;
	goto st0;
st14:
	if ( ++p == pe )
		goto _out14;
case 14:
	if ( (*p) == 100 )
		goto st15;
	goto st0;
st15:
	if ( ++p == pe )
		goto _out15;
case 15:
	if ( (*p) == 61 )
		goto st16;
	goto st0;
st16:
	if ( ++p == pe )
		goto _out16;
case 16:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr29;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr29;
	} else
		goto tr29;
	goto st0;
tr29:
#line 127 "mod_fdajax_parser.rl"
	{
      mark = p;
  }
	goto st17;
st17:
	if ( ++p == pe )
		goto _out17;
case 17:
#line 759 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr30;
		case 38: goto tr31;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st17;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st17;
	} else
		goto st17;
	goto st0;
st18:
	if ( ++p == pe )
		goto _out18;
case 18:
	if ( (*p) == 101 )
		goto st19;
	goto st0;
st19:
	if ( ++p == pe )
		goto _out19;
case 19:
	if ( (*p) == 114 )
		goto st20;
	goto st0;
st20:
	if ( ++p == pe )
		goto _out20;
case 20:
	if ( (*p) == 116 )
		goto st21;
	goto st0;
st21:
	if ( ++p == pe )
		goto _out21;
case 21:
	if ( (*p) == 95 )
		goto st22;
	goto st0;
st22:
	if ( ++p == pe )
		goto _out22;
case 22:
	if ( (*p) == 105 )
		goto st23;
	goto st0;
st23:
	if ( ++p == pe )
		goto _out23;
case 23:
	if ( (*p) == 100 )
		goto st24;
	goto st0;
st24:
	if ( ++p == pe )
		goto _out24;
case 24:
	if ( (*p) == 61 )
		goto st25;
	goto st0;
st25:
	if ( ++p == pe )
		goto _out25;
case 25:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr40;
	goto st0;
tr40:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st26;
st26:
	if ( ++p == pe )
		goto _out26;
case 26:
#line 839 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr43;
	goto st0;
tr43:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st27;
st27:
	if ( ++p == pe )
		goto _out27;
case 27:
#line 855 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr44;
	goto st0;
tr44:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st28;
st28:
	if ( ++p == pe )
		goto _out28;
case 28:
#line 871 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr45;
	goto st0;
tr45:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st29;
st29:
	if ( ++p == pe )
		goto _out29;
case 29:
#line 887 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr46;
	goto st0;
tr46:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st30;
st30:
	if ( ++p == pe )
		goto _out30;
case 30:
#line 903 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr47;
	goto st0;
tr47:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st31;
st31:
	if ( ++p == pe )
		goto _out31;
case 31:
#line 919 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr48;
	goto st0;
tr48:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st32;
st32:
	if ( ++p == pe )
		goto _out32;
case 32:
#line 935 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr49;
	goto st0;
tr49:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st33;
st33:
	if ( ++p == pe )
		goto _out33;
case 33:
#line 951 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr50;
	goto st0;
tr50:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st34;
st34:
	if ( ++p == pe )
		goto _out34;
case 34:
#line 967 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr51;
	goto st0;
tr51:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st35;
st35:
	if ( ++p == pe )
		goto _out35;
case 35:
#line 983 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr41;
		case 38: goto tr42;
	}
	goto st0;
st36:
	if ( ++p == pe )
		goto _out36;
case 36:
	if ( (*p) == 111 )
		goto st37;
	goto st0;
st37:
	if ( ++p == pe )
		goto _out37;
case 37:
	if ( (*p) == 100 )
		goto st38;
	goto st0;
st38:
	if ( ++p == pe )
		goto _out38;
case 38:
	if ( (*p) == 101 )
		goto st39;
	goto st0;
st39:
	if ( ++p == pe )
		goto _out39;
case 39:
	if ( (*p) == 61 )
		goto st40;
	goto st0;
st40:
	if ( ++p == pe )
		goto _out40;
case 40:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr56;
	goto st0;
tr56:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st41;
st41:
	if ( ++p == pe )
		goto _out41;
case 41:
#line 1034 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr59;
	goto st0;
tr59:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st42;
st42:
	if ( ++p == pe )
		goto _out42;
case 42:
#line 1050 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr60;
	goto st0;
tr60:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st43;
st43:
	if ( ++p == pe )
		goto _out43;
case 43:
#line 1066 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr61;
	goto st0;
tr61:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st44;
st44:
	if ( ++p == pe )
		goto _out44;
case 44:
#line 1082 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr62;
	goto st0;
tr62:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st45;
st45:
	if ( ++p == pe )
		goto _out45;
case 45:
#line 1098 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr63;
	goto st0;
tr63:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st46;
st46:
	if ( ++p == pe )
		goto _out46;
case 46:
#line 1114 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr64;
	goto st0;
tr64:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st47;
st47:
	if ( ++p == pe )
		goto _out47;
case 47:
#line 1130 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr65;
	goto st0;
tr65:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st48;
st48:
	if ( ++p == pe )
		goto _out48;
case 48:
#line 1146 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr66;
	goto st0;
tr66:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st49;
st49:
	if ( ++p == pe )
		goto _out49;
case 49:
#line 1162 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr67;
	goto st0;
tr67:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st50;
st50:
	if ( ++p == pe )
		goto _out50;
case 50:
#line 1178 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr57;
		case 38: goto tr58;
	}
	goto st0;
st51:
	if ( ++p == pe )
		goto _out51;
case 51:
	if ( (*p) == 109 )
		goto st52;
	goto st0;
st52:
	if ( ++p == pe )
		goto _out52;
case 52:
	if ( (*p) == 100 )
		goto st53;
	goto st0;
st53:
	if ( ++p == pe )
		goto _out53;
case 53:
	if ( (*p) == 61 )
		goto st54;
	goto st0;
st54:
	if ( ++p == pe )
		goto _out54;
case 54:
	switch( (*p) ) {
		case 97: goto st55;
		case 99: goto st67;
		case 105: goto st83;
		case 108: goto st87;
		case 112: goto st95;
		case 114: goto st99;
		case 115: goto st106;
		case 119: goto st112;
	}
	goto st0;
st55:
	if ( ++p == pe )
		goto _out55;
case 55:
	switch( (*p) ) {
		case 100: goto st56;
		case 108: goto st63;
	}
	goto st0;
st56:
	if ( ++p == pe )
		goto _out56;
case 56:
	if ( (*p) == 100 )
		goto st57;
	goto st0;
st57:
	if ( ++p == pe )
		goto _out57;
case 57:
	if ( (*p) == 95 )
		goto st58;
	goto st0;
st58:
	if ( ++p == pe )
		goto _out58;
case 58:
	if ( (*p) == 99 )
		goto st59;
	goto st0;
st59:
	if ( ++p == pe )
		goto _out59;
case 59:
	if ( (*p) == 104 )
		goto st60;
	goto st0;
st60:
	if ( ++p == pe )
		goto _out60;
case 60:
	if ( (*p) == 97 )
		goto st61;
	goto st0;
st61:
	if ( ++p == pe )
		goto _out61;
case 61:
	if ( (*p) == 116 )
		goto st62;
	goto st0;
st62:
	if ( ++p == pe )
		goto _out62;
case 62:
	switch( (*p) ) {
		case 0: goto tr87;
		case 38: goto tr88;
	}
	goto st0;
st63:
	if ( ++p == pe )
		goto _out63;
case 63:
	if ( (*p) == 101 )
		goto st64;
	goto st0;
st64:
	if ( ++p == pe )
		goto _out64;
case 64:
	if ( (*p) == 114 )
		goto st65;
	goto st0;
st65:
	if ( ++p == pe )
		goto _out65;
case 65:
	if ( (*p) == 116 )
		goto st66;
	goto st0;
st66:
	if ( ++p == pe )
		goto _out66;
case 66:
	switch( (*p) ) {
		case 0: goto tr92;
		case 38: goto tr93;
	}
	goto st0;
st67:
	if ( ++p == pe )
		goto _out67;
case 67:
	switch( (*p) ) {
		case 97: goto st68;
		case 104: goto st73;
	}
	goto st0;
st68:
	if ( ++p == pe )
		goto _out68;
case 68:
	if ( (*p) == 110 )
		goto st69;
	goto st0;
st69:
	if ( ++p == pe )
		goto _out69;
case 69:
	if ( (*p) == 99 )
		goto st70;
	goto st0;
st70:
	if ( ++p == pe )
		goto _out70;
case 70:
	if ( (*p) == 101 )
		goto st71;
	goto st0;
st71:
	if ( ++p == pe )
		goto _out71;
case 71:
	if ( (*p) == 108 )
		goto st72;
	goto st0;
st72:
	if ( ++p == pe )
		goto _out72;
case 72:
	switch( (*p) ) {
		case 0: goto tr100;
		case 38: goto tr101;
	}
	goto st0;
st73:
	if ( ++p == pe )
		goto _out73;
case 73:
	switch( (*p) ) {
		case 97: goto st74;
		case 101: goto st80;
	}
	goto st0;
st74:
	if ( ++p == pe )
		goto _out74;
case 74:
	if ( (*p) == 116 )
		goto st75;
	goto st0;
st75:
	if ( ++p == pe )
		goto _out75;
case 75:
	if ( (*p) == 95 )
		goto st76;
	goto st0;
st76:
	if ( ++p == pe )
		goto _out76;
case 76:
	if ( (*p) == 115 )
		goto st77;
	goto st0;
st77:
	if ( ++p == pe )
		goto _out77;
case 77:
	if ( (*p) == 105 )
		goto st78;
	goto st0;
st78:
	if ( ++p == pe )
		goto _out78;
case 78:
	if ( (*p) == 103 )
		goto st79;
	goto st0;
st79:
	if ( ++p == pe )
		goto _out79;
case 79:
	switch( (*p) ) {
		case 0: goto tr109;
		case 38: goto tr110;
	}
	goto st0;
st80:
	if ( ++p == pe )
		goto _out80;
case 80:
	if ( (*p) == 99 )
		goto st81;
	goto st0;
st81:
	if ( ++p == pe )
		goto _out81;
case 81:
	if ( (*p) == 107 )
		goto st82;
	goto st0;
st82:
	if ( ++p == pe )
		goto _out82;
case 82:
	switch( (*p) ) {
		case 0: goto tr113;
		case 38: goto tr114;
	}
	goto st0;
st83:
	if ( ++p == pe )
		goto _out83;
case 83:
	if ( (*p) == 110 )
		goto st84;
	goto st0;
st84:
	if ( ++p == pe )
		goto _out84;
case 84:
	if ( (*p) == 102 )
		goto st85;
	goto st0;
st85:
	if ( ++p == pe )
		goto _out85;
case 85:
	if ( (*p) == 111 )
		goto st86;
	goto st0;
st86:
	if ( ++p == pe )
		goto _out86;
case 86:
	switch( (*p) ) {
		case 0: goto tr118;
		case 38: goto tr119;
	}
	goto st0;
st87:
	if ( ++p == pe )
		goto _out87;
case 87:
	if ( (*p) == 111 )
		goto st88;
	goto st0;
st88:
	if ( ++p == pe )
		goto _out88;
case 88:
	if ( (*p) == 103 )
		goto st89;
	goto st0;
st89:
	if ( ++p == pe )
		goto _out89;
case 89:
	switch( (*p) ) {
		case 105: goto st90;
		case 111: goto st92;
	}
	goto st0;
st90:
	if ( ++p == pe )
		goto _out90;
case 90:
	if ( (*p) == 110 )
		goto st91;
	goto st0;
st91:
	if ( ++p == pe )
		goto _out91;
case 91:
	switch( (*p) ) {
		case 0: goto tr125;
		case 38: goto tr126;
	}
	goto st0;
st92:
	if ( ++p == pe )
		goto _out92;
case 92:
	if ( (*p) == 117 )
		goto st93;
	goto st0;
st93:
	if ( ++p == pe )
		goto _out93;
case 93:
	if ( (*p) == 116 )
		goto st94;
	goto st0;
st94:
	if ( ++p == pe )
		goto _out94;
case 94:
	switch( (*p) ) {
		case 0: goto tr129;
		case 38: goto tr130;
	}
	goto st0;
st95:
	if ( ++p == pe )
		goto _out95;
case 95:
	if ( (*p) == 117 )
		goto st96;
	goto st0;
st96:
	if ( ++p == pe )
		goto _out96;
case 96:
	if ( (*p) == 115 )
		goto st97;
	goto st0;
st97:
	if ( ++p == pe )
		goto _out97;
case 97:
	if ( (*p) == 104 )
		goto st98;
	goto st0;
st98:
	if ( ++p == pe )
		goto _out98;
case 98:
	switch( (*p) ) {
		case 0: goto tr134;
		case 38: goto tr135;
	}
	goto st0;
st99:
	if ( ++p == pe )
		goto _out99;
case 99:
	if ( (*p) == 109 )
		goto st100;
	goto st0;
st100:
	if ( ++p == pe )
		goto _out100;
case 100:
	if ( (*p) == 95 )
		goto st101;
	goto st0;
st101:
	if ( ++p == pe )
		goto _out101;
case 101:
	if ( (*p) == 99 )
		goto st102;
	goto st0;
st102:
	if ( ++p == pe )
		goto _out102;
case 102:
	if ( (*p) == 104 )
		goto st103;
	goto st0;
st103:
	if ( ++p == pe )
		goto _out103;
case 103:
	if ( (*p) == 97 )
		goto st104;
	goto st0;
st104:
	if ( ++p == pe )
		goto _out104;
case 104:
	if ( (*p) == 116 )
		goto st105;
	goto st0;
st105:
	if ( ++p == pe )
		goto _out105;
case 105:
	switch( (*p) ) {
		case 0: goto tr142;
		case 38: goto tr143;
	}
	goto st0;
st106:
	if ( ++p == pe )
		goto _out106;
case 106:
	if ( (*p) == 116 )
		goto st107;
	goto st0;
st107:
	if ( ++p == pe )
		goto _out107;
case 107:
	if ( (*p) == 114 )
		goto st108;
	goto st0;
st108:
	if ( ++p == pe )
		goto _out108;
case 108:
	if ( (*p) == 101 )
		goto st109;
	goto st0;
st109:
	if ( ++p == pe )
		goto _out109;
case 109:
	if ( (*p) == 97 )
		goto st110;
	goto st0;
st110:
	if ( ++p == pe )
		goto _out110;
case 110:
	if ( (*p) == 109 )
		goto st111;
	goto st0;
st111:
	if ( ++p == pe )
		goto _out111;
case 111:
	switch( (*p) ) {
		case 0: goto tr149;
		case 38: goto tr150;
	}
	goto st0;
st112:
	if ( ++p == pe )
		goto _out112;
case 112:
	if ( (*p) == 97 )
		goto st113;
	goto st0;
st113:
	if ( ++p == pe )
		goto _out113;
case 113:
	if ( (*p) == 105 )
		goto st114;
	goto st0;
st114:
	if ( ++p == pe )
		goto _out114;
case 114:
	if ( (*p) == 116 )
		goto st115;
	goto st0;
st115:
	if ( ++p == pe )
		goto _out115;
case 115:
	switch( (*p) ) {
		case 0: goto tr154;
		case 38: goto tr155;
	}
	goto st0;
st116:
	if ( ++p == pe )
		goto _out116;
case 116:
	if ( (*p) == 111 )
		goto st117;
	goto st0;
st117:
	if ( ++p == pe )
		goto _out117;
case 117:
	if ( (*p) == 114 )
		goto st118;
	goto st0;
st118:
	if ( ++p == pe )
		goto _out118;
case 118:
	if ( (*p) == 99 )
		goto st119;
	goto st0;
st119:
	if ( ++p == pe )
		goto _out119;
case 119:
	if ( (*p) == 101 )
		goto st120;
	goto st0;
st120:
	if ( ++p == pe )
		goto _out120;
case 120:
	if ( (*p) == 61 )
		goto st121;
	goto st0;
st121:
	if ( ++p == pe )
		goto _out121;
case 121:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr161;
	goto st0;
tr161:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st122;
st122:
	if ( ++p == pe )
		goto _out122;
case 122:
#line 1731 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr164;
	goto st0;
tr164:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st123;
st123:
	if ( ++p == pe )
		goto _out123;
case 123:
#line 1747 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr165;
	goto st0;
tr165:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st124;
st124:
	if ( ++p == pe )
		goto _out124;
case 124:
#line 1763 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr166;
	goto st0;
tr166:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st125;
st125:
	if ( ++p == pe )
		goto _out125;
case 125:
#line 1779 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr167;
	goto st0;
tr167:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st126;
st126:
	if ( ++p == pe )
		goto _out126;
case 126:
#line 1795 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr168;
	goto st0;
tr168:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st127;
st127:
	if ( ++p == pe )
		goto _out127;
case 127:
#line 1811 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr169;
	goto st0;
tr169:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st128;
st128:
	if ( ++p == pe )
		goto _out128;
case 128:
#line 1827 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr170;
	goto st0;
tr170:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st129;
st129:
	if ( ++p == pe )
		goto _out129;
case 129:
#line 1843 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr171;
	goto st0;
tr171:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st130;
st130:
	if ( ++p == pe )
		goto _out130;
case 130:
#line 1859 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr172;
	goto st0;
tr172:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st131;
st131:
	if ( ++p == pe )
		goto _out131;
case 131:
#line 1875 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr162;
		case 38: goto tr163;
	}
	goto st0;
st132:
	if ( ++p == pe )
		goto _out132;
case 132:
	if ( (*p) == 112 )
		goto st133;
	goto st0;
st133:
	if ( ++p == pe )
		goto _out133;
case 133:
	if ( (*p) == 95 )
		goto st134;
	goto st0;
st134:
	if ( ++p == pe )
		goto _out134;
case 134:
	if ( (*p) == 97 )
		goto st135;
	goto st0;
st135:
	if ( ++p == pe )
		goto _out135;
case 135:
	if ( (*p) == 100 )
		goto st136;
	goto st0;
st136:
	if ( ++p == pe )
		goto _out136;
case 136:
	if ( (*p) == 100 )
		goto st137;
	goto st0;
st137:
	if ( ++p == pe )
		goto _out137;
case 137:
	if ( (*p) == 114 )
		goto st138;
	goto st0;
st138:
	if ( ++p == pe )
		goto _out138;
case 138:
	if ( (*p) == 61 )
		goto st139;
	goto st0;
st139:
	if ( ++p == pe )
		goto _out139;
case 139:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr180;
	goto st0;
tr180:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st140;
st140:
	if ( ++p == pe )
		goto _out140;
case 140:
#line 1947 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr182;
	goto st0;
tr181:
#line 85 "mod_fdajax_parser.rl"
	{ if (0xff < cur_int) goto _out141; ip_addr = ip_addr | (cur_int << 24); }
	goto st141;
st141:
	if ( ++p == pe )
		goto _out141;
case 141:
#line 1961 "mod_fdajax_parser.c"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr183;
	goto st0;
tr183:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st142;
st142:
	if ( ++p == pe )
		goto _out142;
case 142:
#line 1975 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr185;
	goto st0;
tr184:
#line 86 "mod_fdajax_parser.rl"
	{ if (0xff < cur_int) goto _out143; ip_addr = ip_addr | (cur_int << 16); }
	goto st143;
st143:
	if ( ++p == pe )
		goto _out143;
case 143:
#line 1989 "mod_fdajax_parser.c"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr186;
	goto st0;
tr186:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st144;
st144:
	if ( ++p == pe )
		goto _out144;
case 144:
#line 2003 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr188;
	goto st0;
tr187:
#line 87 "mod_fdajax_parser.rl"
	{ if (0xff < cur_int) goto _out145; ip_addr = ip_addr | (cur_int << 8); }
	goto st145;
st145:
	if ( ++p == pe )
		goto _out145;
case 145:
#line 2017 "mod_fdajax_parser.c"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr189;
	goto st0;
tr189:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st146;
st146:
	if ( ++p == pe )
		goto _out146;
case 146:
#line 2031 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr192;
	goto st0;
tr192:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st147;
st147:
	if ( ++p == pe )
		goto _out147;
case 147:
#line 2047 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr193;
	goto st0;
tr193:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st148;
st148:
	if ( ++p == pe )
		goto _out148;
case 148:
#line 2063 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr194;
	goto st0;
tr194:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st149;
st149:
	if ( ++p == pe )
		goto _out149;
case 149:
#line 2079 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr195;
	goto st0;
tr195:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st150;
st150:
	if ( ++p == pe )
		goto _out150;
case 150:
#line 2095 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr196;
	goto st0;
tr196:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st151;
st151:
	if ( ++p == pe )
		goto _out151;
case 151:
#line 2111 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr197;
	goto st0;
tr197:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st152;
st152:
	if ( ++p == pe )
		goto _out152;
case 152:
#line 2127 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr198;
	goto st0;
tr198:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st153;
st153:
	if ( ++p == pe )
		goto _out153;
case 153:
#line 2143 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr199;
	goto st0;
tr199:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st154;
st154:
	if ( ++p == pe )
		goto _out154;
case 154:
#line 2159 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr200;
	goto st0;
tr200:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st155;
st155:
	if ( ++p == pe )
		goto _out155;
case 155:
#line 2175 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr190;
		case 38: goto tr191;
	}
	goto st0;
tr188:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st156;
st156:
	if ( ++p == pe )
		goto _out156;
case 156:
#line 2189 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr201;
	goto st0;
tr201:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st157;
st157:
	if ( ++p == pe )
		goto _out157;
case 157:
#line 2203 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr202;
	goto st0;
tr202:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st158;
st158:
	if ( ++p == pe )
		goto _out158;
case 158:
#line 2217 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr203;
	goto st0;
tr203:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st159;
st159:
	if ( ++p == pe )
		goto _out159;
case 159:
#line 2231 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr204;
	goto st0;
tr204:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st160;
st160:
	if ( ++p == pe )
		goto _out160;
case 160:
#line 2245 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr205;
	goto st0;
tr205:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st161;
st161:
	if ( ++p == pe )
		goto _out161;
case 161:
#line 2259 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr206;
	goto st0;
tr206:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st162;
st162:
	if ( ++p == pe )
		goto _out162;
case 162:
#line 2273 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr207;
	goto st0;
tr207:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st163;
st163:
	if ( ++p == pe )
		goto _out163;
case 163:
#line 2287 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr208;
	goto st0;
tr208:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st164;
st164:
	if ( ++p == pe )
		goto _out164;
case 164:
#line 2301 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr187;
	goto st0;
tr185:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st165;
st165:
	if ( ++p == pe )
		goto _out165;
case 165:
#line 2313 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr209;
	goto st0;
tr209:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st166;
st166:
	if ( ++p == pe )
		goto _out166;
case 166:
#line 2327 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr210;
	goto st0;
tr210:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st167;
st167:
	if ( ++p == pe )
		goto _out167;
case 167:
#line 2341 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr211;
	goto st0;
tr211:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st168;
st168:
	if ( ++p == pe )
		goto _out168;
case 168:
#line 2355 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr212;
	goto st0;
tr212:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st169;
st169:
	if ( ++p == pe )
		goto _out169;
case 169:
#line 2369 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr213;
	goto st0;
tr213:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st170;
st170:
	if ( ++p == pe )
		goto _out170;
case 170:
#line 2383 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr214;
	goto st0;
tr214:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st171;
st171:
	if ( ++p == pe )
		goto _out171;
case 171:
#line 2397 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr215;
	goto st0;
tr215:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st172;
st172:
	if ( ++p == pe )
		goto _out172;
case 172:
#line 2411 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr216;
	goto st0;
tr216:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st173;
st173:
	if ( ++p == pe )
		goto _out173;
case 173:
#line 2425 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr184;
	goto st0;
tr182:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st174;
st174:
	if ( ++p == pe )
		goto _out174;
case 174:
#line 2437 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr217;
	goto st0;
tr217:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st175;
st175:
	if ( ++p == pe )
		goto _out175;
case 175:
#line 2451 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr218;
	goto st0;
tr218:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st176;
st176:
	if ( ++p == pe )
		goto _out176;
case 176:
#line 2465 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr219;
	goto st0;
tr219:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st177;
st177:
	if ( ++p == pe )
		goto _out177;
case 177:
#line 2479 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr220;
	goto st0;
tr220:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st178;
st178:
	if ( ++p == pe )
		goto _out178;
case 178:
#line 2493 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr221;
	goto st0;
tr221:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st179;
st179:
	if ( ++p == pe )
		goto _out179;
case 179:
#line 2507 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr222;
	goto st0;
tr222:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st180;
st180:
	if ( ++p == pe )
		goto _out180;
case 180:
#line 2521 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr223;
	goto st0;
tr223:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st181;
st181:
	if ( ++p == pe )
		goto _out181;
case 181:
#line 2535 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr224;
	goto st0;
tr224:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st182;
st182:
	if ( ++p == pe )
		goto _out182;
case 182:
#line 2549 "mod_fdajax_parser.c"
	if ( (*p) == 46 )
		goto tr181;
	goto st0;
st183:
	if ( ++p == pe )
		goto _out183;
case 183:
	if ( (*p) == 101 )
		goto st184;
	goto st0;
st184:
	if ( ++p == pe )
		goto _out184;
case 184:
	if ( (*p) == 115 )
		goto st185;
	goto st0;
st185:
	if ( ++p == pe )
		goto _out185;
case 185:
	if ( (*p) == 61 )
		goto st186;
	goto st0;
st186:
	if ( ++p == pe )
		goto _out186;
case 186:
	switch( (*p) ) {
		case 0: goto st0;
		case 37: goto tr229;
		case 38: goto st0;
		case 43: goto tr230;
	}
	goto tr228;
tr228:
#line 92 "mod_fdajax_parser.rl"
	{
      if (req->mes) {
          goto _out187;
      }
      req->mes = buffer_init();
      /* TODO is mem allocated ? */
      buffer_prepare_append(req->mes, len);
      buf = req->mes->ptr;
      ppos = &(req->mes->used);
  }
#line 109 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = (*p);
  }
	goto st187;
tr230:
#line 92 "mod_fdajax_parser.rl"
	{
      if (req->mes) {
          goto _out187;
      }
      req->mes = buffer_init();
      /* TODO is mem allocated ? */
      buffer_prepare_append(req->mes, len);
      buf = req->mes->ptr;
      ppos = &(req->mes->used);
  }
#line 112 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = ' ';
  }
	goto st187;
tr231:
#line 109 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = (*p);
  }
	goto st187;
tr235:
#line 112 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = ' ';
  }
	goto st187;
tr242:
#line 105 "mod_fdajax_parser.rl"
	{
      hex = hex | phex;
      buf[(*ppos)++] = hex;
  }
#line 109 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = (*p);
  }
	goto st187;
tr246:
#line 105 "mod_fdajax_parser.rl"
	{
      hex = hex | phex;
      buf[(*ppos)++] = hex;
  }
#line 112 "mod_fdajax_parser.rl"
	{
      buf[(*ppos)++] = ' ';
  }
	goto st187;
st187:
	if ( ++p == pe )
		goto _out187;
case 187:
#line 2657 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr232;
		case 37: goto st188;
		case 38: goto tr234;
		case 43: goto tr235;
	}
	goto tr231;
tr229:
#line 92 "mod_fdajax_parser.rl"
	{
      if (req->mes) {
          goto _out188;
      }
      req->mes = buffer_init();
      /* TODO is mem allocated ? */
      buffer_prepare_append(req->mes, len);
      buf = req->mes->ptr;
      ppos = &(req->mes->used);
  }
	goto st188;
tr244:
#line 105 "mod_fdajax_parser.rl"
	{
      hex = hex | phex;
      buf[(*ppos)++] = hex;
  }
	goto st188;
st188:
	if ( ++p == pe )
		goto _out188;
case 188:
#line 2689 "mod_fdajax_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr236;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr238;
	} else
		goto tr237;
	goto st0;
tr236:
#line 121 "mod_fdajax_parser.rl"
	{ phex = (*p) - '0'; }
	goto st189;
tr237:
#line 120 "mod_fdajax_parser.rl"
	{ phex = (*p) - 'A' + 10; }
	goto st189;
tr238:
#line 119 "mod_fdajax_parser.rl"
	{ phex = (*p) - 'a' + 10; }
	goto st189;
st189:
	if ( ++p == pe )
		goto _out189;
case 189:
#line 2715 "mod_fdajax_parser.c"
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr239;
	} else if ( (*p) > 70 ) {
		if ( 97 <= (*p) && (*p) <= 102 )
			goto tr241;
	} else
		goto tr240;
	goto st0;
tr239:
#line 102 "mod_fdajax_parser.rl"
	{
      hex = phex << 4;
  }
#line 121 "mod_fdajax_parser.rl"
	{ phex = (*p) - '0'; }
	goto st190;
tr240:
#line 102 "mod_fdajax_parser.rl"
	{
      hex = phex << 4;
  }
#line 120 "mod_fdajax_parser.rl"
	{ phex = (*p) - 'A' + 10; }
	goto st190;
tr241:
#line 102 "mod_fdajax_parser.rl"
	{
      hex = phex << 4;
  }
#line 119 "mod_fdajax_parser.rl"
	{ phex = (*p) - 'a' + 10; }
	goto st190;
st190:
	if ( ++p == pe )
		goto _out190;
case 190:
#line 2753 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr243;
		case 37: goto tr244;
		case 38: goto tr245;
		case 43: goto tr246;
	}
	goto tr242;
st191:
	if ( ++p == pe )
		goto _out191;
case 191:
	if ( (*p) == 101 )
		goto st192;
	goto st0;
st192:
	if ( ++p == pe )
		goto _out192;
case 192:
	if ( (*p) == 101 )
		goto st193;
	goto st0;
st193:
	if ( ++p == pe )
		goto _out193;
case 193:
	if ( (*p) == 114 )
		goto st194;
	goto st0;
st194:
	if ( ++p == pe )
		goto _out194;
case 194:
	if ( (*p) == 95 )
		goto st195;
	goto st0;
st195:
	if ( ++p == pe )
		goto _out195;
case 195:
	if ( (*p) == 105 )
		goto st196;
	goto st0;
st196:
	if ( ++p == pe )
		goto _out196;
case 196:
	if ( (*p) == 100 )
		goto st197;
	goto st0;
st197:
	if ( ++p == pe )
		goto _out197;
case 197:
	if ( (*p) == 61 )
		goto st198;
	goto st0;
st198:
	if ( ++p == pe )
		goto _out198;
case 198:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr254;
	goto st0;
tr254:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st199;
st199:
	if ( ++p == pe )
		goto _out199;
case 199:
#line 2827 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr257;
	goto st0;
tr257:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st200;
st200:
	if ( ++p == pe )
		goto _out200;
case 200:
#line 2843 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr258;
	goto st0;
tr258:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st201;
st201:
	if ( ++p == pe )
		goto _out201;
case 201:
#line 2859 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr259;
	goto st0;
tr259:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st202;
st202:
	if ( ++p == pe )
		goto _out202;
case 202:
#line 2875 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr260;
	goto st0;
tr260:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st203;
st203:
	if ( ++p == pe )
		goto _out203;
case 203:
#line 2891 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr261;
	goto st0;
tr261:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st204;
st204:
	if ( ++p == pe )
		goto _out204;
case 204:
#line 2907 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr262;
	goto st0;
tr262:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st205;
st205:
	if ( ++p == pe )
		goto _out205;
case 205:
#line 2923 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr263;
	goto st0;
tr263:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st206;
st206:
	if ( ++p == pe )
		goto _out206;
case 206:
#line 2939 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr264;
	goto st0;
tr264:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st207;
st207:
	if ( ++p == pe )
		goto _out207;
case 207:
#line 2955 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr265;
	goto st0;
tr265:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st208;
st208:
	if ( ++p == pe )
		goto _out208;
case 208:
#line 2971 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr255;
		case 38: goto tr256;
	}
	goto st0;
st209:
	if ( ++p == pe )
		goto _out209;
case 209:
	if ( (*p) == 101 )
		goto st210;
	goto st0;
st210:
	if ( ++p == pe )
		goto _out210;
case 210:
	switch( (*p) ) {
		case 99: goto st211;
		case 115: goto st223;
	}
	goto st0;
st211:
	if ( ++p == pe )
		goto _out211;
case 211:
	if ( (*p) == 61 )
		goto st212;
	goto st0;
st212:
	if ( ++p == pe )
		goto _out212;
case 212:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr270;
	goto st0;
tr270:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st213;
st213:
	if ( ++p == pe )
		goto _out213;
case 213:
#line 3017 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr273;
	goto st0;
tr273:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st214;
st214:
	if ( ++p == pe )
		goto _out214;
case 214:
#line 3033 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr274;
	goto st0;
tr274:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st215;
st215:
	if ( ++p == pe )
		goto _out215;
case 215:
#line 3049 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr275;
	goto st0;
tr275:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st216;
st216:
	if ( ++p == pe )
		goto _out216;
case 216:
#line 3065 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr276;
	goto st0;
tr276:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st217;
st217:
	if ( ++p == pe )
		goto _out217;
case 217:
#line 3081 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr277;
	goto st0;
tr277:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st218;
st218:
	if ( ++p == pe )
		goto _out218;
case 218:
#line 3097 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr278;
	goto st0;
tr278:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st219;
st219:
	if ( ++p == pe )
		goto _out219;
case 219:
#line 3113 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr279;
	goto st0;
tr279:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st220;
st220:
	if ( ++p == pe )
		goto _out220;
case 220:
#line 3129 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr280;
	goto st0;
tr280:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st221;
st221:
	if ( ++p == pe )
		goto _out221;
case 221:
#line 3145 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr281;
	goto st0;
tr281:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st222;
st222:
	if ( ++p == pe )
		goto _out222;
case 222:
#line 3161 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr271;
		case 38: goto tr272;
	}
	goto st0;
st223:
	if ( ++p == pe )
		goto _out223;
case 223:
	if ( (*p) == 115 )
		goto st224;
	goto st0;
st224:
	if ( ++p == pe )
		goto _out224;
case 224:
	if ( (*p) == 95 )
		goto st225;
	goto st0;
st225:
	if ( ++p == pe )
		goto _out225;
case 225:
	if ( (*p) == 105 )
		goto st226;
	goto st0;
st226:
	if ( ++p == pe )
		goto _out226;
case 226:
	if ( (*p) == 100 )
		goto st227;
	goto st0;
st227:
	if ( ++p == pe )
		goto _out227;
case 227:
	if ( (*p) == 61 )
		goto st228;
	goto st0;
st228:
	if ( ++p == pe )
		goto _out228;
case 228:
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto tr287;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto tr287;
	} else
		goto tr287;
	goto st0;
tr287:
#line 127 "mod_fdajax_parser.rl"
	{
      mark = p;
  }
	goto st229;
st229:
	if ( ++p == pe )
		goto _out229;
case 229:
#line 3225 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr288;
		case 38: goto tr289;
	}
	if ( (*p) < 65 ) {
		if ( 48 <= (*p) && (*p) <= 57 )
			goto st229;
	} else if ( (*p) > 90 ) {
		if ( 97 <= (*p) && (*p) <= 122 )
			goto st229;
	} else
		goto st229;
	goto st0;
st230:
	if ( ++p == pe )
		goto _out230;
case 230:
	if ( (*p) == 121 )
		goto st231;
	goto st0;
st231:
	if ( ++p == pe )
		goto _out231;
case 231:
	if ( (*p) == 112 )
		goto st232;
	goto st0;
st232:
	if ( ++p == pe )
		goto _out232;
case 232:
	if ( (*p) == 101 )
		goto st233;
	goto st0;
st233:
	if ( ++p == pe )
		goto _out233;
case 233:
	if ( (*p) == 115 )
		goto st234;
	goto st0;
st234:
	if ( ++p == pe )
		goto _out234;
case 234:
	if ( (*p) == 61 )
		goto st235;
	goto st0;
tr316:
#line 67 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ANSW, FDA_GRP_ANSW_INDEX); }
	goto st235;
tr325:
#line 58 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CCD, FDA_EV_CCD_INDEX); }
	goto st235;
tr334:
#line 38 "mod_fdajax_parser.rl"
	{
      if (CUR_ID_TAB_LEN < FDA_IDS_MAX) {
          req->ev.ids[cur_ev_nr][CUR_ID_TAB_LEN++] = cur_int;
      } else {
          CUR_ID_TAB_LEN = 0;
      }
  }
	goto st235;
tr349:
#line 48 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CHAT, FDA_EV_CHAT_INDEX); }
	goto st235;
tr357:
#line 74 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FEED, FDA_GRP_FEED_INDEX); }
	goto st235;
tr363:
#line 78 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FRID, FDA_GRP_FRID_INDEX); }
	goto st235;
tr372:
#line 65 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_CHAT, FDA_GRP_CHAT_INDEX); }
	goto st235;
tr379:
#line 73 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_GEIC, FDA_GRP_GEIC_INDEX); }
	goto st235;
tr384:
#line 47 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_GEN, FDA_EV_GEN_INDEX); }
	goto st235;
tr392:
#line 79 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_INFO, FDA_GRP_INFO_INDEX); }
	goto st235;
tr398:
#line 59 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ITM, FDA_EV_ITM_INDEX); }
	goto st235;
tr405:
#line 60 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_LNE, FDA_EV_LNE_INDEX); }
	goto st235;
tr413:
#line 64 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MAIN, FDA_GRP_MAIN_INDEX); }
	goto st235;
tr420:
#line 56 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_MES, FDA_EV_MES_INDEX); }
	goto st235;
tr424:
#line 75 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MESE, FDA_GRP_MESE_INDEX); }
	goto st235;
tr431:
#line 76 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_NETK, FDA_GRP_NETK_INDEX); }
	goto st235;
tr440:
#line 68 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OFRS, FDA_GRP_OFRS_INDEX); }
	goto st235;
tr446:
#line 70 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OPIN, FDA_GRP_OPIN_INDEX); }
	goto st235;
tr453:
#line 57 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ORD, FDA_EV_ORD_INDEX); }
	goto st235;
tr457:
#line 72 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ORDS, FDA_GRP_ORDS_INDEX); }
	goto st235;
tr464:
#line 69 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_PRIC, FDA_GRP_PRIC_INDEX); }
	goto st235;
tr471:
#line 66 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_QUES, FDA_GRP_QUES_INDEX); }
	goto st235;
tr481:
#line 55 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHC, FDA_EV_SHC_INDEX); }
	goto st235;
tr486:
#line 53 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHO, FDA_EV_SHO_INDEX); }
	goto st235;
tr491:
#line 54 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHS, FDA_EV_SHS_INDEX); }
	goto st235;
tr498:
#line 51 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUO, FDA_EV_SUO_INDEX); }
	goto st235;
tr503:
#line 52 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUS, FDA_EV_SUS_INDEX); }
	goto st235;
tr512:
#line 77 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_TASK, FDA_GRP_TASK_INDEX); }
	goto st235;
tr518:
#line 49 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TOQ, FDA_EV_TOQ_INDEX); }
	goto st235;
tr524:
#line 50 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TWP, FDA_EV_TWP_INDEX); }
	goto st235;
tr532:
#line 46 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_UNW, FDA_EV_UNW_INDEX); }
	goto st235;
tr540:
#line 71 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_USER, FDA_GRP_USER_INDEX); }
	goto st235;
tr545:
#line 61 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_USR, FDA_EV_USR_INDEX); }
	goto st235;
st235:
	if ( ++p == pe )
		goto _out235;
case 235:
#line 3416 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 97: goto st236;
		case 99: goto st242;
		case 102: goto st261;
		case 103: goto st268;
		case 105: goto st277;
		case 108: goto st283;
		case 109: goto st286;
		case 110: goto st293;
		case 111: goto st297;
		case 112: goto st307;
		case 113: goto st311;
		case 115: goto st315;
		case 116: goto st323;
		case 117: goto st331;
	}
	goto st0;
st236:
	if ( ++p == pe )
		goto _out236;
case 236:
	if ( (*p) == 110 )
		goto st237;
	goto st0;
st237:
	if ( ++p == pe )
		goto _out237;
case 237:
	if ( (*p) == 115 )
		goto st238;
	goto st0;
st238:
	if ( ++p == pe )
		goto _out238;
case 238:
	if ( (*p) == 119 )
		goto st239;
	goto st0;
st239:
	if ( ++p == pe )
		goto _out239;
case 239:
	switch( (*p) ) {
		case 0: goto tr313;
		case 37: goto tr314;
		case 38: goto tr315;
		case 124: goto tr316;
	}
	goto st0;
tr314:
#line 67 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ANSW, FDA_GRP_ANSW_INDEX); }
	goto st240;
tr355:
#line 74 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FEED, FDA_GRP_FEED_INDEX); }
	goto st240;
tr361:
#line 78 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_FRID, FDA_GRP_FRID_INDEX); }
	goto st240;
tr370:
#line 65 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_CHAT, FDA_GRP_CHAT_INDEX); }
	goto st240;
tr377:
#line 73 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_GEIC, FDA_GRP_GEIC_INDEX); }
	goto st240;
tr390:
#line 79 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_INFO, FDA_GRP_INFO_INDEX); }
	goto st240;
tr411:
#line 64 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MAIN, FDA_GRP_MAIN_INDEX); }
	goto st240;
tr422:
#line 75 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_MESE, FDA_GRP_MESE_INDEX); }
	goto st240;
tr429:
#line 76 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_NETK, FDA_GRP_NETK_INDEX); }
	goto st240;
tr438:
#line 68 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OFRS, FDA_GRP_OFRS_INDEX); }
	goto st240;
tr444:
#line 70 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_OPIN, FDA_GRP_OPIN_INDEX); }
	goto st240;
tr455:
#line 72 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_ORDS, FDA_GRP_ORDS_INDEX); }
	goto st240;
tr462:
#line 69 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_PRIC, FDA_GRP_PRIC_INDEX); }
	goto st240;
tr469:
#line 66 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_QUES, FDA_GRP_QUES_INDEX); }
	goto st240;
tr510:
#line 77 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_TASK, FDA_GRP_TASK_INDEX); }
	goto st240;
tr538:
#line 71 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_GRP_USER, FDA_GRP_USER_INDEX); }
	goto st240;
st240:
	if ( ++p == pe )
		goto _out240;
case 240:
#line 3534 "mod_fdajax_parser.c"
	if ( (*p) == 55 )
		goto st241;
	goto st0;
st241:
	if ( ++p == pe )
		goto _out241;
case 241:
	switch( (*p) ) {
		case 67: goto st235;
		case 99: goto st235;
	}
	goto st0;
st242:
	if ( ++p == pe )
		goto _out242;
case 242:
	switch( (*p) ) {
		case 99: goto st243;
		case 104: goto st258;
	}
	goto st0;
st243:
	if ( ++p == pe )
		goto _out243;
case 243:
	if ( (*p) == 100 )
		goto st244;
	goto st0;
st244:
	if ( ++p == pe )
		goto _out244;
case 244:
	switch( (*p) ) {
		case 0: goto tr321;
		case 37: goto tr322;
		case 38: goto tr323;
		case 44: goto tr324;
		case 124: goto tr325;
	}
	goto st0;
tr322:
#line 58 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CCD, FDA_EV_CCD_INDEX); }
	goto st245;
tr330:
#line 38 "mod_fdajax_parser.rl"
	{
      if (CUR_ID_TAB_LEN < FDA_IDS_MAX) {
          req->ev.ids[cur_ev_nr][CUR_ID_TAB_LEN++] = cur_int;
      } else {
          CUR_ID_TAB_LEN = 0;
      }
  }
	goto st245;
tr346:
#line 48 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CHAT, FDA_EV_CHAT_INDEX); }
	goto st245;
tr381:
#line 47 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_GEN, FDA_EV_GEN_INDEX); }
	goto st245;
tr395:
#line 59 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ITM, FDA_EV_ITM_INDEX); }
	goto st245;
tr402:
#line 60 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_LNE, FDA_EV_LNE_INDEX); }
	goto st245;
tr416:
#line 56 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_MES, FDA_EV_MES_INDEX); }
	goto st245;
tr449:
#line 57 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ORD, FDA_EV_ORD_INDEX); }
	goto st245;
tr478:
#line 55 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHC, FDA_EV_SHC_INDEX); }
	goto st245;
tr483:
#line 53 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHO, FDA_EV_SHO_INDEX); }
	goto st245;
tr488:
#line 54 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHS, FDA_EV_SHS_INDEX); }
	goto st245;
tr495:
#line 51 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUO, FDA_EV_SUO_INDEX); }
	goto st245;
tr500:
#line 52 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUS, FDA_EV_SUS_INDEX); }
	goto st245;
tr515:
#line 49 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TOQ, FDA_EV_TOQ_INDEX); }
	goto st245;
tr521:
#line 50 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TWP, FDA_EV_TWP_INDEX); }
	goto st245;
tr529:
#line 46 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_UNW, FDA_EV_UNW_INDEX); }
	goto st245;
tr542:
#line 61 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_USR, FDA_EV_USR_INDEX); }
	goto st245;
st245:
	if ( ++p == pe )
		goto _out245;
case 245:
#line 3653 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 50: goto st246;
		case 55: goto st241;
	}
	goto st0;
st246:
	if ( ++p == pe )
		goto _out246;
case 246:
	switch( (*p) ) {
		case 67: goto st247;
		case 99: goto st247;
	}
	goto st0;
tr324:
#line 58 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CCD, FDA_EV_CCD_INDEX); }
	goto st247;
tr332:
#line 38 "mod_fdajax_parser.rl"
	{
      if (CUR_ID_TAB_LEN < FDA_IDS_MAX) {
          req->ev.ids[cur_ev_nr][CUR_ID_TAB_LEN++] = cur_int;
      } else {
          CUR_ID_TAB_LEN = 0;
      }
  }
	goto st247;
tr348:
#line 48 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_CHAT, FDA_EV_CHAT_INDEX); }
	goto st247;
tr383:
#line 47 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_GEN, FDA_EV_GEN_INDEX); }
	goto st247;
tr397:
#line 59 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ITM, FDA_EV_ITM_INDEX); }
	goto st247;
tr404:
#line 60 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_LNE, FDA_EV_LNE_INDEX); }
	goto st247;
tr418:
#line 56 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_MES, FDA_EV_MES_INDEX); }
	goto st247;
tr451:
#line 57 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_ORD, FDA_EV_ORD_INDEX); }
	goto st247;
tr480:
#line 55 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHC, FDA_EV_SHC_INDEX); }
	goto st247;
tr485:
#line 53 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHO, FDA_EV_SHO_INDEX); }
	goto st247;
tr490:
#line 54 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SHS, FDA_EV_SHS_INDEX); }
	goto st247;
tr497:
#line 51 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUO, FDA_EV_SUO_INDEX); }
	goto st247;
tr502:
#line 52 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_SUS, FDA_EV_SUS_INDEX); }
	goto st247;
tr517:
#line 49 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TOQ, FDA_EV_TOQ_INDEX); }
	goto st247;
tr523:
#line 50 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_TWP, FDA_EV_TWP_INDEX); }
	goto st247;
tr531:
#line 46 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_UNW, FDA_EV_UNW_INDEX); }
	goto st247;
tr544:
#line 61 "mod_fdajax_parser.rl"
	{ INIT_EVENT(FDA_EV_USR, FDA_EV_USR_INDEX); }
	goto st247;
st247:
	if ( ++p == pe )
		goto _out247;
case 247:
#line 3746 "mod_fdajax_parser.c"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr328;
	goto st0;
tr328:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st248;
st248:
	if ( ++p == pe )
		goto _out248;
case 248:
#line 3760 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr333;
	goto st0;
tr333:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st249;
st249:
	if ( ++p == pe )
		goto _out249;
case 249:
#line 3779 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr335;
	goto st0;
tr335:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st250;
st250:
	if ( ++p == pe )
		goto _out250;
case 250:
#line 3798 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr336;
	goto st0;
tr336:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st251;
st251:
	if ( ++p == pe )
		goto _out251;
case 251:
#line 3817 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr337;
	goto st0;
tr337:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st252;
st252:
	if ( ++p == pe )
		goto _out252;
case 252:
#line 3836 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr338;
	goto st0;
tr338:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st253;
st253:
	if ( ++p == pe )
		goto _out253;
case 253:
#line 3855 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr339;
	goto st0;
tr339:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st254;
st254:
	if ( ++p == pe )
		goto _out254;
case 254:
#line 3874 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr340;
	goto st0;
tr340:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st255;
st255:
	if ( ++p == pe )
		goto _out255;
case 255:
#line 3893 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr341;
	goto st0;
tr341:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st256;
st256:
	if ( ++p == pe )
		goto _out256;
case 256:
#line 3912 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr342;
	goto st0;
tr342:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st257;
st257:
	if ( ++p == pe )
		goto _out257;
case 257:
#line 3931 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr329;
		case 37: goto tr330;
		case 38: goto tr331;
		case 44: goto tr332;
		case 124: goto tr334;
	}
	goto st0;
st258:
	if ( ++p == pe )
		goto _out258;
case 258:
	if ( (*p) == 97 )
		goto st259;
	goto st0;
st259:
	if ( ++p == pe )
		goto _out259;
case 259:
	if ( (*p) == 116 )
		goto st260;
	goto st0;
st260:
	if ( ++p == pe )
		goto _out260;
case 260:
	switch( (*p) ) {
		case 0: goto tr345;
		case 37: goto tr346;
		case 38: goto tr347;
		case 44: goto tr348;
		case 124: goto tr349;
	}
	goto st0;
st261:
	if ( ++p == pe )
		goto _out261;
case 261:
	switch( (*p) ) {
		case 101: goto st262;
		case 114: goto st265;
	}
	goto st0;
st262:
	if ( ++p == pe )
		goto _out262;
case 262:
	if ( (*p) == 101 )
		goto st263;
	goto st0;
st263:
	if ( ++p == pe )
		goto _out263;
case 263:
	if ( (*p) == 100 )
		goto st264;
	goto st0;
st264:
	if ( ++p == pe )
		goto _out264;
case 264:
	switch( (*p) ) {
		case 0: goto tr354;
		case 37: goto tr355;
		case 38: goto tr356;
		case 124: goto tr357;
	}
	goto st0;
st265:
	if ( ++p == pe )
		goto _out265;
case 265:
	if ( (*p) == 105 )
		goto st266;
	goto st0;
st266:
	if ( ++p == pe )
		goto _out266;
case 266:
	if ( (*p) == 100 )
		goto st267;
	goto st0;
st267:
	if ( ++p == pe )
		goto _out267;
case 267:
	switch( (*p) ) {
		case 0: goto tr360;
		case 37: goto tr361;
		case 38: goto tr362;
		case 124: goto tr363;
	}
	goto st0;
st268:
	if ( ++p == pe )
		goto _out268;
case 268:
	switch( (*p) ) {
		case 99: goto st269;
		case 101: goto st273;
	}
	goto st0;
st269:
	if ( ++p == pe )
		goto _out269;
case 269:
	if ( (*p) == 104 )
		goto st270;
	goto st0;
st270:
	if ( ++p == pe )
		goto _out270;
case 270:
	if ( (*p) == 97 )
		goto st271;
	goto st0;
st271:
	if ( ++p == pe )
		goto _out271;
case 271:
	if ( (*p) == 116 )
		goto st272;
	goto st0;
st272:
	if ( ++p == pe )
		goto _out272;
case 272:
	switch( (*p) ) {
		case 0: goto tr369;
		case 37: goto tr370;
		case 38: goto tr371;
		case 124: goto tr372;
	}
	goto st0;
st273:
	if ( ++p == pe )
		goto _out273;
case 273:
	switch( (*p) ) {
		case 105: goto st274;
		case 110: goto st276;
	}
	goto st0;
st274:
	if ( ++p == pe )
		goto _out274;
case 274:
	if ( (*p) == 99 )
		goto st275;
	goto st0;
st275:
	if ( ++p == pe )
		goto _out275;
case 275:
	switch( (*p) ) {
		case 0: goto tr376;
		case 37: goto tr377;
		case 38: goto tr378;
		case 124: goto tr379;
	}
	goto st0;
st276:
	if ( ++p == pe )
		goto _out276;
case 276:
	switch( (*p) ) {
		case 0: goto tr380;
		case 37: goto tr381;
		case 38: goto tr382;
		case 44: goto tr383;
		case 124: goto tr384;
	}
	goto st0;
st277:
	if ( ++p == pe )
		goto _out277;
case 277:
	switch( (*p) ) {
		case 110: goto st278;
		case 116: goto st281;
	}
	goto st0;
st278:
	if ( ++p == pe )
		goto _out278;
case 278:
	if ( (*p) == 102 )
		goto st279;
	goto st0;
st279:
	if ( ++p == pe )
		goto _out279;
case 279:
	if ( (*p) == 111 )
		goto st280;
	goto st0;
st280:
	if ( ++p == pe )
		goto _out280;
case 280:
	switch( (*p) ) {
		case 0: goto tr389;
		case 37: goto tr390;
		case 38: goto tr391;
		case 124: goto tr392;
	}
	goto st0;
st281:
	if ( ++p == pe )
		goto _out281;
case 281:
	if ( (*p) == 109 )
		goto st282;
	goto st0;
st282:
	if ( ++p == pe )
		goto _out282;
case 282:
	switch( (*p) ) {
		case 0: goto tr394;
		case 37: goto tr395;
		case 38: goto tr396;
		case 44: goto tr397;
		case 124: goto tr398;
	}
	goto st0;
st283:
	if ( ++p == pe )
		goto _out283;
case 283:
	if ( (*p) == 110 )
		goto st284;
	goto st0;
st284:
	if ( ++p == pe )
		goto _out284;
case 284:
	if ( (*p) == 101 )
		goto st285;
	goto st0;
st285:
	if ( ++p == pe )
		goto _out285;
case 285:
	switch( (*p) ) {
		case 0: goto tr401;
		case 37: goto tr402;
		case 38: goto tr403;
		case 44: goto tr404;
		case 124: goto tr405;
	}
	goto st0;
st286:
	if ( ++p == pe )
		goto _out286;
case 286:
	switch( (*p) ) {
		case 97: goto st287;
		case 101: goto st290;
	}
	goto st0;
st287:
	if ( ++p == pe )
		goto _out287;
case 287:
	if ( (*p) == 105 )
		goto st288;
	goto st0;
st288:
	if ( ++p == pe )
		goto _out288;
case 288:
	if ( (*p) == 110 )
		goto st289;
	goto st0;
st289:
	if ( ++p == pe )
		goto _out289;
case 289:
	switch( (*p) ) {
		case 0: goto tr410;
		case 37: goto tr411;
		case 38: goto tr412;
		case 124: goto tr413;
	}
	goto st0;
st290:
	if ( ++p == pe )
		goto _out290;
case 290:
	if ( (*p) == 115 )
		goto st291;
	goto st0;
st291:
	if ( ++p == pe )
		goto _out291;
case 291:
	switch( (*p) ) {
		case 0: goto tr415;
		case 37: goto tr416;
		case 38: goto tr417;
		case 44: goto tr418;
		case 101: goto st292;
		case 124: goto tr420;
	}
	goto st0;
st292:
	if ( ++p == pe )
		goto _out292;
case 292:
	switch( (*p) ) {
		case 0: goto tr421;
		case 37: goto tr422;
		case 38: goto tr423;
		case 124: goto tr424;
	}
	goto st0;
st293:
	if ( ++p == pe )
		goto _out293;
case 293:
	if ( (*p) == 101 )
		goto st294;
	goto st0;
st294:
	if ( ++p == pe )
		goto _out294;
case 294:
	if ( (*p) == 116 )
		goto st295;
	goto st0;
st295:
	if ( ++p == pe )
		goto _out295;
case 295:
	if ( (*p) == 107 )
		goto st296;
	goto st0;
st296:
	if ( ++p == pe )
		goto _out296;
case 296:
	switch( (*p) ) {
		case 0: goto tr428;
		case 37: goto tr429;
		case 38: goto tr430;
		case 124: goto tr431;
	}
	goto st0;
st297:
	if ( ++p == pe )
		goto _out297;
case 297:
	switch( (*p) ) {
		case 102: goto st298;
		case 112: goto st301;
		case 114: goto st304;
	}
	goto st0;
st298:
	if ( ++p == pe )
		goto _out298;
case 298:
	if ( (*p) == 114 )
		goto st299;
	goto st0;
st299:
	if ( ++p == pe )
		goto _out299;
case 299:
	if ( (*p) == 115 )
		goto st300;
	goto st0;
st300:
	if ( ++p == pe )
		goto _out300;
case 300:
	switch( (*p) ) {
		case 0: goto tr437;
		case 37: goto tr438;
		case 38: goto tr439;
		case 124: goto tr440;
	}
	goto st0;
st301:
	if ( ++p == pe )
		goto _out301;
case 301:
	if ( (*p) == 105 )
		goto st302;
	goto st0;
st302:
	if ( ++p == pe )
		goto _out302;
case 302:
	if ( (*p) == 110 )
		goto st303;
	goto st0;
st303:
	if ( ++p == pe )
		goto _out303;
case 303:
	switch( (*p) ) {
		case 0: goto tr443;
		case 37: goto tr444;
		case 38: goto tr445;
		case 124: goto tr446;
	}
	goto st0;
st304:
	if ( ++p == pe )
		goto _out304;
case 304:
	if ( (*p) == 100 )
		goto st305;
	goto st0;
st305:
	if ( ++p == pe )
		goto _out305;
case 305:
	switch( (*p) ) {
		case 0: goto tr448;
		case 37: goto tr449;
		case 38: goto tr450;
		case 44: goto tr451;
		case 115: goto st306;
		case 124: goto tr453;
	}
	goto st0;
st306:
	if ( ++p == pe )
		goto _out306;
case 306:
	switch( (*p) ) {
		case 0: goto tr454;
		case 37: goto tr455;
		case 38: goto tr456;
		case 124: goto tr457;
	}
	goto st0;
st307:
	if ( ++p == pe )
		goto _out307;
case 307:
	if ( (*p) == 114 )
		goto st308;
	goto st0;
st308:
	if ( ++p == pe )
		goto _out308;
case 308:
	if ( (*p) == 105 )
		goto st309;
	goto st0;
st309:
	if ( ++p == pe )
		goto _out309;
case 309:
	if ( (*p) == 99 )
		goto st310;
	goto st0;
st310:
	if ( ++p == pe )
		goto _out310;
case 310:
	switch( (*p) ) {
		case 0: goto tr461;
		case 37: goto tr462;
		case 38: goto tr463;
		case 124: goto tr464;
	}
	goto st0;
st311:
	if ( ++p == pe )
		goto _out311;
case 311:
	if ( (*p) == 117 )
		goto st312;
	goto st0;
st312:
	if ( ++p == pe )
		goto _out312;
case 312:
	if ( (*p) == 101 )
		goto st313;
	goto st0;
st313:
	if ( ++p == pe )
		goto _out313;
case 313:
	if ( (*p) == 115 )
		goto st314;
	goto st0;
st314:
	if ( ++p == pe )
		goto _out314;
case 314:
	switch( (*p) ) {
		case 0: goto tr468;
		case 37: goto tr469;
		case 38: goto tr470;
		case 124: goto tr471;
	}
	goto st0;
st315:
	if ( ++p == pe )
		goto _out315;
case 315:
	switch( (*p) ) {
		case 104: goto st316;
		case 117: goto st320;
	}
	goto st0;
st316:
	if ( ++p == pe )
		goto _out316;
case 316:
	switch( (*p) ) {
		case 99: goto st317;
		case 111: goto st318;
		case 115: goto st319;
	}
	goto st0;
st317:
	if ( ++p == pe )
		goto _out317;
case 317:
	switch( (*p) ) {
		case 0: goto tr477;
		case 37: goto tr478;
		case 38: goto tr479;
		case 44: goto tr480;
		case 124: goto tr481;
	}
	goto st0;
st318:
	if ( ++p == pe )
		goto _out318;
case 318:
	switch( (*p) ) {
		case 0: goto tr482;
		case 37: goto tr483;
		case 38: goto tr484;
		case 44: goto tr485;
		case 124: goto tr486;
	}
	goto st0;
st319:
	if ( ++p == pe )
		goto _out319;
case 319:
	switch( (*p) ) {
		case 0: goto tr487;
		case 37: goto tr488;
		case 38: goto tr489;
		case 44: goto tr490;
		case 124: goto tr491;
	}
	goto st0;
st320:
	if ( ++p == pe )
		goto _out320;
case 320:
	switch( (*p) ) {
		case 111: goto st321;
		case 115: goto st322;
	}
	goto st0;
st321:
	if ( ++p == pe )
		goto _out321;
case 321:
	switch( (*p) ) {
		case 0: goto tr494;
		case 37: goto tr495;
		case 38: goto tr496;
		case 44: goto tr497;
		case 124: goto tr498;
	}
	goto st0;
st322:
	if ( ++p == pe )
		goto _out322;
case 322:
	switch( (*p) ) {
		case 0: goto tr499;
		case 37: goto tr500;
		case 38: goto tr501;
		case 44: goto tr502;
		case 124: goto tr503;
	}
	goto st0;
st323:
	if ( ++p == pe )
		goto _out323;
case 323:
	switch( (*p) ) {
		case 97: goto st324;
		case 111: goto st327;
		case 119: goto st329;
	}
	goto st0;
st324:
	if ( ++p == pe )
		goto _out324;
case 324:
	if ( (*p) == 115 )
		goto st325;
	goto st0;
st325:
	if ( ++p == pe )
		goto _out325;
case 325:
	if ( (*p) == 107 )
		goto st326;
	goto st0;
st326:
	if ( ++p == pe )
		goto _out326;
case 326:
	switch( (*p) ) {
		case 0: goto tr509;
		case 37: goto tr510;
		case 38: goto tr511;
		case 124: goto tr512;
	}
	goto st0;
st327:
	if ( ++p == pe )
		goto _out327;
case 327:
	if ( (*p) == 113 )
		goto st328;
	goto st0;
st328:
	if ( ++p == pe )
		goto _out328;
case 328:
	switch( (*p) ) {
		case 0: goto tr514;
		case 37: goto tr515;
		case 38: goto tr516;
		case 44: goto tr517;
		case 124: goto tr518;
	}
	goto st0;
st329:
	if ( ++p == pe )
		goto _out329;
case 329:
	if ( (*p) == 112 )
		goto st330;
	goto st0;
st330:
	if ( ++p == pe )
		goto _out330;
case 330:
	switch( (*p) ) {
		case 0: goto tr520;
		case 37: goto tr521;
		case 38: goto tr522;
		case 44: goto tr523;
		case 124: goto tr524;
	}
	goto st0;
st331:
	if ( ++p == pe )
		goto _out331;
case 331:
	switch( (*p) ) {
		case 110: goto st332;
		case 115: goto st334;
	}
	goto st0;
st332:
	if ( ++p == pe )
		goto _out332;
case 332:
	if ( (*p) == 119 )
		goto st333;
	goto st0;
st333:
	if ( ++p == pe )
		goto _out333;
case 333:
	switch( (*p) ) {
		case 0: goto tr528;
		case 37: goto tr529;
		case 38: goto tr530;
		case 44: goto tr531;
		case 124: goto tr532;
	}
	goto st0;
st334:
	if ( ++p == pe )
		goto _out334;
case 334:
	switch( (*p) ) {
		case 101: goto st335;
		case 114: goto st338;
	}
	goto st0;
st335:
	if ( ++p == pe )
		goto _out335;
case 335:
	if ( (*p) == 114 )
		goto st336;
	goto st0;
st336:
	if ( ++p == pe )
		goto _out336;
case 336:
	if ( (*p) == 115 )
		goto st337;
	goto st0;
st337:
	if ( ++p == pe )
		goto _out337;
case 337:
	switch( (*p) ) {
		case 0: goto tr537;
		case 37: goto tr538;
		case 38: goto tr539;
		case 124: goto tr540;
	}
	goto st0;
st338:
	if ( ++p == pe )
		goto _out338;
case 338:
	switch( (*p) ) {
		case 0: goto tr541;
		case 37: goto tr542;
		case 38: goto tr543;
		case 44: goto tr544;
		case 124: goto tr545;
	}
	goto st0;
st339:
	if ( ++p == pe )
		goto _out339;
case 339:
	if ( (*p) == 115 )
		goto st340;
	goto st0;
st340:
	if ( ++p == pe )
		goto _out340;
case 340:
	if ( (*p) == 101 )
		goto st341;
	goto st0;
st341:
	if ( ++p == pe )
		goto _out341;
case 341:
	switch( (*p) ) {
		case 99: goto st342;
		case 114: goto st354;
	}
	goto st0;
st342:
	if ( ++p == pe )
		goto _out342;
case 342:
	if ( (*p) == 61 )
		goto st343;
	goto st0;
st343:
	if ( ++p == pe )
		goto _out343;
case 343:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr551;
	goto st0;
tr551:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st344;
st344:
	if ( ++p == pe )
		goto _out344;
case 344:
#line 4718 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr554;
	goto st0;
tr554:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st345;
st345:
	if ( ++p == pe )
		goto _out345;
case 345:
#line 4734 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr555;
	goto st0;
tr555:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st346;
st346:
	if ( ++p == pe )
		goto _out346;
case 346:
#line 4750 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr556;
	goto st0;
tr556:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st347;
st347:
	if ( ++p == pe )
		goto _out347;
case 347:
#line 4766 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr557;
	goto st0;
tr557:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st348;
st348:
	if ( ++p == pe )
		goto _out348;
case 348:
#line 4782 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr558;
	goto st0;
tr558:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st349;
st349:
	if ( ++p == pe )
		goto _out349;
case 349:
#line 4798 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr559;
	goto st0;
tr559:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st350;
st350:
	if ( ++p == pe )
		goto _out350;
case 350:
#line 4814 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr560;
	goto st0;
tr560:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st351;
st351:
	if ( ++p == pe )
		goto _out351;
case 351:
#line 4830 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr561;
	goto st0;
tr561:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st352;
st352:
	if ( ++p == pe )
		goto _out352;
case 352:
#line 4846 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr562;
	goto st0;
tr562:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st353;
st353:
	if ( ++p == pe )
		goto _out353;
case 353:
#line 4862 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr552;
		case 38: goto tr553;
	}
	goto st0;
st354:
	if ( ++p == pe )
		goto _out354;
case 354:
	if ( (*p) == 95 )
		goto st355;
	goto st0;
st355:
	if ( ++p == pe )
		goto _out355;
case 355:
	if ( (*p) == 105 )
		goto st356;
	goto st0;
st356:
	if ( ++p == pe )
		goto _out356;
case 356:
	if ( (*p) == 100 )
		goto st357;
	goto st0;
st357:
	if ( ++p == pe )
		goto _out357;
case 357:
	if ( (*p) == 61 )
		goto st358;
	goto st0;
st358:
	if ( ++p == pe )
		goto _out358;
case 358:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr567;
	goto st0;
tr567:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st359;
st359:
	if ( ++p == pe )
		goto _out359;
case 359:
#line 4913 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr570;
	goto st0;
tr570:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st360;
st360:
	if ( ++p == pe )
		goto _out360;
case 360:
#line 4929 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr571;
	goto st0;
tr571:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st361;
st361:
	if ( ++p == pe )
		goto _out361;
case 361:
#line 4945 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr572;
	goto st0;
tr572:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st362;
st362:
	if ( ++p == pe )
		goto _out362;
case 362:
#line 4961 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr573;
	goto st0;
tr573:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st363;
st363:
	if ( ++p == pe )
		goto _out363;
case 363:
#line 4977 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr574;
	goto st0;
tr574:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st364;
st364:
	if ( ++p == pe )
		goto _out364;
case 364:
#line 4993 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr575;
	goto st0;
tr575:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st365;
st365:
	if ( ++p == pe )
		goto _out365;
case 365:
#line 5009 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr576;
	goto st0;
tr576:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st366;
st366:
	if ( ++p == pe )
		goto _out366;
case 366:
#line 5025 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr577;
	goto st0;
tr577:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st367;
st367:
	if ( ++p == pe )
		goto _out367;
case 367:
#line 5041 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr578;
	goto st0;
tr578:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st368;
st368:
	if ( ++p == pe )
		goto _out368;
case 368:
#line 5057 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr568;
		case 38: goto tr569;
	}
	goto st0;
st369:
	if ( ++p == pe )
		goto _out369;
case 369:
	if ( (*p) == 105 )
		goto st370;
	goto st0;
st370:
	if ( ++p == pe )
		goto _out370;
case 370:
	if ( (*p) == 110 )
		goto st371;
	goto st0;
st371:
	if ( ++p == pe )
		goto _out371;
case 371:
	if ( (*p) == 95 )
		goto st372;
	goto st0;
st372:
	if ( ++p == pe )
		goto _out372;
case 372:
	switch( (*p) ) {
		case 105: goto st373;
		case 115: goto st386;
	}
	goto st0;
st373:
	if ( ++p == pe )
		goto _out373;
case 373:
	if ( (*p) == 100 )
		goto st374;
	goto st0;
st374:
	if ( ++p == pe )
		goto _out374;
case 374:
	if ( (*p) == 61 )
		goto st375;
	goto st0;
st375:
	if ( ++p == pe )
		goto _out375;
case 375:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr586;
	goto st0;
tr586:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st376;
st376:
	if ( ++p == pe )
		goto _out376;
case 376:
#line 5124 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr589;
	goto st0;
tr589:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st377;
st377:
	if ( ++p == pe )
		goto _out377;
case 377:
#line 5140 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr590;
	goto st0;
tr590:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st378;
st378:
	if ( ++p == pe )
		goto _out378;
case 378:
#line 5156 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr591;
	goto st0;
tr591:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st379;
st379:
	if ( ++p == pe )
		goto _out379;
case 379:
#line 5172 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr592;
	goto st0;
tr592:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st380;
st380:
	if ( ++p == pe )
		goto _out380;
case 380:
#line 5188 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr593;
	goto st0;
tr593:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st381;
st381:
	if ( ++p == pe )
		goto _out381;
case 381:
#line 5204 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr594;
	goto st0;
tr594:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st382;
st382:
	if ( ++p == pe )
		goto _out382;
case 382:
#line 5220 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr595;
	goto st0;
tr595:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st383;
st383:
	if ( ++p == pe )
		goto _out383;
case 383:
#line 5236 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr596;
	goto st0;
tr596:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st384;
st384:
	if ( ++p == pe )
		goto _out384;
case 384:
#line 5252 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr597;
	goto st0;
tr597:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st385;
st385:
	if ( ++p == pe )
		goto _out385;
case 385:
#line 5268 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr587;
		case 38: goto tr588;
	}
	goto st0;
st386:
	if ( ++p == pe )
		goto _out386;
case 386:
	if ( (*p) == 116 )
		goto st387;
	goto st0;
st387:
	if ( ++p == pe )
		goto _out387;
case 387:
	if ( (*p) == 61 )
		goto st388;
	goto st0;
st388:
	if ( ++p == pe )
		goto _out388;
case 388:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr600;
	goto st0;
tr600:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = 0; }
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st389;
st389:
	if ( ++p == pe )
		goto _out389;
case 389:
#line 5305 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr603;
	goto st0;
tr603:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st390;
st390:
	if ( ++p == pe )
		goto _out390;
case 390:
#line 5321 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr604;
	goto st0;
tr604:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st391;
st391:
	if ( ++p == pe )
		goto _out391;
case 391:
#line 5337 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr605;
	goto st0;
tr605:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st392;
st392:
	if ( ++p == pe )
		goto _out392;
case 392:
#line 5353 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr606;
	goto st0;
tr606:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st393;
st393:
	if ( ++p == pe )
		goto _out393;
case 393:
#line 5369 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr607;
	goto st0;
tr607:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st394;
st394:
	if ( ++p == pe )
		goto _out394;
case 394:
#line 5385 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr608;
	goto st0;
tr608:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st395;
st395:
	if ( ++p == pe )
		goto _out395;
case 395:
#line 5401 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr609;
	goto st0;
tr609:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st396;
st396:
	if ( ++p == pe )
		goto _out396;
case 396:
#line 5417 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr610;
	goto st0;
tr610:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st397;
st397:
	if ( ++p == pe )
		goto _out397;
case 397:
#line 5433 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr611;
	goto st0;
tr611:
#line 13 "mod_fdajax_parser.rl"
	{ cur_int = cur_int * 10 + ((*p) - '0'); }
	goto st398;
st398:
	if ( ++p == pe )
		goto _out398;
case 398:
#line 5449 "mod_fdajax_parser.c"
	switch( (*p) ) {
		case 0: goto tr601;
		case 38: goto tr602;
	}
	goto st0;
	}
	_out1: cs = 1; goto _out; 
	_out0: cs = 0; goto _out; 
	_out2: cs = 2; goto _out; 
	_out3: cs = 3; goto _out; 
	_out399: cs = 399; goto _out; 
	_out4: cs = 4; goto _out; 
	_out5: cs = 5; goto _out; 
	_out6: cs = 6; goto _out; 
	_out7: cs = 7; goto _out; 
	_out8: cs = 8; goto _out; 
	_out9: cs = 9; goto _out; 
	_out10: cs = 10; goto _out; 
	_out11: cs = 11; goto _out; 
	_out12: cs = 12; goto _out; 
	_out13: cs = 13; goto _out; 
	_out14: cs = 14; goto _out; 
	_out15: cs = 15; goto _out; 
	_out16: cs = 16; goto _out; 
	_out17: cs = 17; goto _out; 
	_out18: cs = 18; goto _out; 
	_out19: cs = 19; goto _out; 
	_out20: cs = 20; goto _out; 
	_out21: cs = 21; goto _out; 
	_out22: cs = 22; goto _out; 
	_out23: cs = 23; goto _out; 
	_out24: cs = 24; goto _out; 
	_out25: cs = 25; goto _out; 
	_out26: cs = 26; goto _out; 
	_out27: cs = 27; goto _out; 
	_out28: cs = 28; goto _out; 
	_out29: cs = 29; goto _out; 
	_out30: cs = 30; goto _out; 
	_out31: cs = 31; goto _out; 
	_out32: cs = 32; goto _out; 
	_out33: cs = 33; goto _out; 
	_out34: cs = 34; goto _out; 
	_out35: cs = 35; goto _out; 
	_out36: cs = 36; goto _out; 
	_out37: cs = 37; goto _out; 
	_out38: cs = 38; goto _out; 
	_out39: cs = 39; goto _out; 
	_out40: cs = 40; goto _out; 
	_out41: cs = 41; goto _out; 
	_out42: cs = 42; goto _out; 
	_out43: cs = 43; goto _out; 
	_out44: cs = 44; goto _out; 
	_out45: cs = 45; goto _out; 
	_out46: cs = 46; goto _out; 
	_out47: cs = 47; goto _out; 
	_out48: cs = 48; goto _out; 
	_out49: cs = 49; goto _out; 
	_out50: cs = 50; goto _out; 
	_out51: cs = 51; goto _out; 
	_out52: cs = 52; goto _out; 
	_out53: cs = 53; goto _out; 
	_out54: cs = 54; goto _out; 
	_out55: cs = 55; goto _out; 
	_out56: cs = 56; goto _out; 
	_out57: cs = 57; goto _out; 
	_out58: cs = 58; goto _out; 
	_out59: cs = 59; goto _out; 
	_out60: cs = 60; goto _out; 
	_out61: cs = 61; goto _out; 
	_out62: cs = 62; goto _out; 
	_out63: cs = 63; goto _out; 
	_out64: cs = 64; goto _out; 
	_out65: cs = 65; goto _out; 
	_out66: cs = 66; goto _out; 
	_out67: cs = 67; goto _out; 
	_out68: cs = 68; goto _out; 
	_out69: cs = 69; goto _out; 
	_out70: cs = 70; goto _out; 
	_out71: cs = 71; goto _out; 
	_out72: cs = 72; goto _out; 
	_out73: cs = 73; goto _out; 
	_out74: cs = 74; goto _out; 
	_out75: cs = 75; goto _out; 
	_out76: cs = 76; goto _out; 
	_out77: cs = 77; goto _out; 
	_out78: cs = 78; goto _out; 
	_out79: cs = 79; goto _out; 
	_out80: cs = 80; goto _out; 
	_out81: cs = 81; goto _out; 
	_out82: cs = 82; goto _out; 
	_out83: cs = 83; goto _out; 
	_out84: cs = 84; goto _out; 
	_out85: cs = 85; goto _out; 
	_out86: cs = 86; goto _out; 
	_out87: cs = 87; goto _out; 
	_out88: cs = 88; goto _out; 
	_out89: cs = 89; goto _out; 
	_out90: cs = 90; goto _out; 
	_out91: cs = 91; goto _out; 
	_out92: cs = 92; goto _out; 
	_out93: cs = 93; goto _out; 
	_out94: cs = 94; goto _out; 
	_out95: cs = 95; goto _out; 
	_out96: cs = 96; goto _out; 
	_out97: cs = 97; goto _out; 
	_out98: cs = 98; goto _out; 
	_out99: cs = 99; goto _out; 
	_out100: cs = 100; goto _out; 
	_out101: cs = 101; goto _out; 
	_out102: cs = 102; goto _out; 
	_out103: cs = 103; goto _out; 
	_out104: cs = 104; goto _out; 
	_out105: cs = 105; goto _out; 
	_out106: cs = 106; goto _out; 
	_out107: cs = 107; goto _out; 
	_out108: cs = 108; goto _out; 
	_out109: cs = 109; goto _out; 
	_out110: cs = 110; goto _out; 
	_out111: cs = 111; goto _out; 
	_out112: cs = 112; goto _out; 
	_out113: cs = 113; goto _out; 
	_out114: cs = 114; goto _out; 
	_out115: cs = 115; goto _out; 
	_out116: cs = 116; goto _out; 
	_out117: cs = 117; goto _out; 
	_out118: cs = 118; goto _out; 
	_out119: cs = 119; goto _out; 
	_out120: cs = 120; goto _out; 
	_out121: cs = 121; goto _out; 
	_out122: cs = 122; goto _out; 
	_out123: cs = 123; goto _out; 
	_out124: cs = 124; goto _out; 
	_out125: cs = 125; goto _out; 
	_out126: cs = 126; goto _out; 
	_out127: cs = 127; goto _out; 
	_out128: cs = 128; goto _out; 
	_out129: cs = 129; goto _out; 
	_out130: cs = 130; goto _out; 
	_out131: cs = 131; goto _out; 
	_out132: cs = 132; goto _out; 
	_out133: cs = 133; goto _out; 
	_out134: cs = 134; goto _out; 
	_out135: cs = 135; goto _out; 
	_out136: cs = 136; goto _out; 
	_out137: cs = 137; goto _out; 
	_out138: cs = 138; goto _out; 
	_out139: cs = 139; goto _out; 
	_out140: cs = 140; goto _out; 
	_out141: cs = 141; goto _out; 
	_out142: cs = 142; goto _out; 
	_out143: cs = 143; goto _out; 
	_out144: cs = 144; goto _out; 
	_out145: cs = 145; goto _out; 
	_out146: cs = 146; goto _out; 
	_out147: cs = 147; goto _out; 
	_out148: cs = 148; goto _out; 
	_out149: cs = 149; goto _out; 
	_out150: cs = 150; goto _out; 
	_out151: cs = 151; goto _out; 
	_out152: cs = 152; goto _out; 
	_out153: cs = 153; goto _out; 
	_out154: cs = 154; goto _out; 
	_out155: cs = 155; goto _out; 
	_out156: cs = 156; goto _out; 
	_out157: cs = 157; goto _out; 
	_out158: cs = 158; goto _out; 
	_out159: cs = 159; goto _out; 
	_out160: cs = 160; goto _out; 
	_out161: cs = 161; goto _out; 
	_out162: cs = 162; goto _out; 
	_out163: cs = 163; goto _out; 
	_out164: cs = 164; goto _out; 
	_out165: cs = 165; goto _out; 
	_out166: cs = 166; goto _out; 
	_out167: cs = 167; goto _out; 
	_out168: cs = 168; goto _out; 
	_out169: cs = 169; goto _out; 
	_out170: cs = 170; goto _out; 
	_out171: cs = 171; goto _out; 
	_out172: cs = 172; goto _out; 
	_out173: cs = 173; goto _out; 
	_out174: cs = 174; goto _out; 
	_out175: cs = 175; goto _out; 
	_out176: cs = 176; goto _out; 
	_out177: cs = 177; goto _out; 
	_out178: cs = 178; goto _out; 
	_out179: cs = 179; goto _out; 
	_out180: cs = 180; goto _out; 
	_out181: cs = 181; goto _out; 
	_out182: cs = 182; goto _out; 
	_out183: cs = 183; goto _out; 
	_out184: cs = 184; goto _out; 
	_out185: cs = 185; goto _out; 
	_out186: cs = 186; goto _out; 
	_out187: cs = 187; goto _out; 
	_out188: cs = 188; goto _out; 
	_out189: cs = 189; goto _out; 
	_out190: cs = 190; goto _out; 
	_out191: cs = 191; goto _out; 
	_out192: cs = 192; goto _out; 
	_out193: cs = 193; goto _out; 
	_out194: cs = 194; goto _out; 
	_out195: cs = 195; goto _out; 
	_out196: cs = 196; goto _out; 
	_out197: cs = 197; goto _out; 
	_out198: cs = 198; goto _out; 
	_out199: cs = 199; goto _out; 
	_out200: cs = 200; goto _out; 
	_out201: cs = 201; goto _out; 
	_out202: cs = 202; goto _out; 
	_out203: cs = 203; goto _out; 
	_out204: cs = 204; goto _out; 
	_out205: cs = 205; goto _out; 
	_out206: cs = 206; goto _out; 
	_out207: cs = 207; goto _out; 
	_out208: cs = 208; goto _out; 
	_out209: cs = 209; goto _out; 
	_out210: cs = 210; goto _out; 
	_out211: cs = 211; goto _out; 
	_out212: cs = 212; goto _out; 
	_out213: cs = 213; goto _out; 
	_out214: cs = 214; goto _out; 
	_out215: cs = 215; goto _out; 
	_out216: cs = 216; goto _out; 
	_out217: cs = 217; goto _out; 
	_out218: cs = 218; goto _out; 
	_out219: cs = 219; goto _out; 
	_out220: cs = 220; goto _out; 
	_out221: cs = 221; goto _out; 
	_out222: cs = 222; goto _out; 
	_out223: cs = 223; goto _out; 
	_out224: cs = 224; goto _out; 
	_out225: cs = 225; goto _out; 
	_out226: cs = 226; goto _out; 
	_out227: cs = 227; goto _out; 
	_out228: cs = 228; goto _out; 
	_out229: cs = 229; goto _out; 
	_out230: cs = 230; goto _out; 
	_out231: cs = 231; goto _out; 
	_out232: cs = 232; goto _out; 
	_out233: cs = 233; goto _out; 
	_out234: cs = 234; goto _out; 
	_out235: cs = 235; goto _out; 
	_out236: cs = 236; goto _out; 
	_out237: cs = 237; goto _out; 
	_out238: cs = 238; goto _out; 
	_out239: cs = 239; goto _out; 
	_out240: cs = 240; goto _out; 
	_out241: cs = 241; goto _out; 
	_out242: cs = 242; goto _out; 
	_out243: cs = 243; goto _out; 
	_out244: cs = 244; goto _out; 
	_out245: cs = 245; goto _out; 
	_out246: cs = 246; goto _out; 
	_out247: cs = 247; goto _out; 
	_out248: cs = 248; goto _out; 
	_out249: cs = 249; goto _out; 
	_out250: cs = 250; goto _out; 
	_out251: cs = 251; goto _out; 
	_out252: cs = 252; goto _out; 
	_out253: cs = 253; goto _out; 
	_out254: cs = 254; goto _out; 
	_out255: cs = 255; goto _out; 
	_out256: cs = 256; goto _out; 
	_out257: cs = 257; goto _out; 
	_out258: cs = 258; goto _out; 
	_out259: cs = 259; goto _out; 
	_out260: cs = 260; goto _out; 
	_out261: cs = 261; goto _out; 
	_out262: cs = 262; goto _out; 
	_out263: cs = 263; goto _out; 
	_out264: cs = 264; goto _out; 
	_out265: cs = 265; goto _out; 
	_out266: cs = 266; goto _out; 
	_out267: cs = 267; goto _out; 
	_out268: cs = 268; goto _out; 
	_out269: cs = 269; goto _out; 
	_out270: cs = 270; goto _out; 
	_out271: cs = 271; goto _out; 
	_out272: cs = 272; goto _out; 
	_out273: cs = 273; goto _out; 
	_out274: cs = 274; goto _out; 
	_out275: cs = 275; goto _out; 
	_out276: cs = 276; goto _out; 
	_out277: cs = 277; goto _out; 
	_out278: cs = 278; goto _out; 
	_out279: cs = 279; goto _out; 
	_out280: cs = 280; goto _out; 
	_out281: cs = 281; goto _out; 
	_out282: cs = 282; goto _out; 
	_out283: cs = 283; goto _out; 
	_out284: cs = 284; goto _out; 
	_out285: cs = 285; goto _out; 
	_out286: cs = 286; goto _out; 
	_out287: cs = 287; goto _out; 
	_out288: cs = 288; goto _out; 
	_out289: cs = 289; goto _out; 
	_out290: cs = 290; goto _out; 
	_out291: cs = 291; goto _out; 
	_out292: cs = 292; goto _out; 
	_out293: cs = 293; goto _out; 
	_out294: cs = 294; goto _out; 
	_out295: cs = 295; goto _out; 
	_out296: cs = 296; goto _out; 
	_out297: cs = 297; goto _out; 
	_out298: cs = 298; goto _out; 
	_out299: cs = 299; goto _out; 
	_out300: cs = 300; goto _out; 
	_out301: cs = 301; goto _out; 
	_out302: cs = 302; goto _out; 
	_out303: cs = 303; goto _out; 
	_out304: cs = 304; goto _out; 
	_out305: cs = 305; goto _out; 
	_out306: cs = 306; goto _out; 
	_out307: cs = 307; goto _out; 
	_out308: cs = 308; goto _out; 
	_out309: cs = 309; goto _out; 
	_out310: cs = 310; goto _out; 
	_out311: cs = 311; goto _out; 
	_out312: cs = 312; goto _out; 
	_out313: cs = 313; goto _out; 
	_out314: cs = 314; goto _out; 
	_out315: cs = 315; goto _out; 
	_out316: cs = 316; goto _out; 
	_out317: cs = 317; goto _out; 
	_out318: cs = 318; goto _out; 
	_out319: cs = 319; goto _out; 
	_out320: cs = 320; goto _out; 
	_out321: cs = 321; goto _out; 
	_out322: cs = 322; goto _out; 
	_out323: cs = 323; goto _out; 
	_out324: cs = 324; goto _out; 
	_out325: cs = 325; goto _out; 
	_out326: cs = 326; goto _out; 
	_out327: cs = 327; goto _out; 
	_out328: cs = 328; goto _out; 
	_out329: cs = 329; goto _out; 
	_out330: cs = 330; goto _out; 
	_out331: cs = 331; goto _out; 
	_out332: cs = 332; goto _out; 
	_out333: cs = 333; goto _out; 
	_out334: cs = 334; goto _out; 
	_out335: cs = 335; goto _out; 
	_out336: cs = 336; goto _out; 
	_out337: cs = 337; goto _out; 
	_out338: cs = 338; goto _out; 
	_out339: cs = 339; goto _out; 
	_out340: cs = 340; goto _out; 
	_out341: cs = 341; goto _out; 
	_out342: cs = 342; goto _out; 
	_out343: cs = 343; goto _out; 
	_out344: cs = 344; goto _out; 
	_out345: cs = 345; goto _out; 
	_out346: cs = 346; goto _out; 
	_out347: cs = 347; goto _out; 
	_out348: cs = 348; goto _out; 
	_out349: cs = 349; goto _out; 
	_out350: cs = 350; goto _out; 
	_out351: cs = 351; goto _out; 
	_out352: cs = 352; goto _out; 
	_out353: cs = 353; goto _out; 
	_out354: cs = 354; goto _out; 
	_out355: cs = 355; goto _out; 
	_out356: cs = 356; goto _out; 
	_out357: cs = 357; goto _out; 
	_out358: cs = 358; goto _out; 
	_out359: cs = 359; goto _out; 
	_out360: cs = 360; goto _out; 
	_out361: cs = 361; goto _out; 
	_out362: cs = 362; goto _out; 
	_out363: cs = 363; goto _out; 
	_out364: cs = 364; goto _out; 
	_out365: cs = 365; goto _out; 
	_out366: cs = 366; goto _out; 
	_out367: cs = 367; goto _out; 
	_out368: cs = 368; goto _out; 
	_out369: cs = 369; goto _out; 
	_out370: cs = 370; goto _out; 
	_out371: cs = 371; goto _out; 
	_out372: cs = 372; goto _out; 
	_out373: cs = 373; goto _out; 
	_out374: cs = 374; goto _out; 
	_out375: cs = 375; goto _out; 
	_out376: cs = 376; goto _out; 
	_out377: cs = 377; goto _out; 
	_out378: cs = 378; goto _out; 
	_out379: cs = 379; goto _out; 
	_out380: cs = 380; goto _out; 
	_out381: cs = 381; goto _out; 
	_out382: cs = 382; goto _out; 
	_out383: cs = 383; goto _out; 
	_out384: cs = 384; goto _out; 
	_out385: cs = 385; goto _out; 
	_out386: cs = 386; goto _out; 
	_out387: cs = 387; goto _out; 
	_out388: cs = 388; goto _out; 
	_out389: cs = 389; goto _out; 
	_out390: cs = 390; goto _out; 
	_out391: cs = 391; goto _out; 
	_out392: cs = 392; goto _out; 
	_out393: cs = 393; goto _out; 
	_out394: cs = 394; goto _out; 
	_out395: cs = 395; goto _out; 
	_out396: cs = 396; goto _out; 
	_out397: cs = 397; goto _out; 
	_out398: cs = 398; goto _out; 

	_out: {}
	}
#line 199 "mod_fdajax_parser.rl"
    req->cs = cs;

    return 1;
}

int mod_fdajax_pfinish(user_request_p req)
{
  int cs = req->cs;
  
#line 5869 "mod_fdajax_parser.c"
#line 208 "mod_fdajax_parser.rl"
  req->cs = cs;

  if (req->cs == fdamod_parser_error) {
      return -1;
  } else if (req->cs >= fdamod_parser_first_final) {
      return 1;
  }
  return 0;
}

