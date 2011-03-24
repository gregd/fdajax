#include "mod_fdajax_defs.h"

unsigned int g_ev_mask_by_index[FDA_TYPES_MAX] = { FDA_EV_UNW, FDA_EV_GEN, FDA_EV_CHAT, FDA_EV_TOQ, 
												   FDA_EV_TWP, FDA_EV_SUO, FDA_EV_SUS, FDA_EV_SHO, 
												   FDA_EV_SHS, FDA_EV_SHC, FDA_EV_MES, FDA_EV_ORD,
												   FDA_EV_CCD, FDA_EV_ITM, FDA_EV_LNE, FDA_EV_USR,
												   FDA_GRP_MAIN, FDA_GRP_CHAT, FDA_GRP_QUES, FDA_GRP_ANSW,
												   FDA_GRP_OFRS, FDA_GRP_PRIC, FDA_GRP_OPIN, FDA_GRP_USER,
												   FDA_GRP_ORDS, FDA_GRP_GEIC, FDA_GRP_FEED, FDA_GRP_MESE,
												   FDA_GRP_NETK, FDA_GRP_TASK, FDA_GRP_FRID, FDA_GRP_INFO };

char *g_ev_name_by_index[FDA_TYPES_MAX] = { "unw", "gen", "chat", "toq", 
											"twp", "suo", "sus", "sho", 
											"shs", "shc", "mes", "ord", 
											"ccd", "itm", "lne", "usr",
											"main", "gchat", "ques", "answ",
											"ofrs", "pric", "opin", "users",
											"ords", "geic", "feed", "mese",
											"netk", "task", "frid", "info" };

int event_bit_to_index(unsigned int ev) 
{
    switch (ev) {
    case FDA_EV_UNW:   return 0;
    case FDA_EV_GEN:   return 1;
    case FDA_EV_CHAT:  return 2;
    case FDA_EV_TOQ:   return 3;
    case FDA_EV_TWP:   return 4;      
    case FDA_EV_SUO:   return 5;
    case FDA_EV_SUS:   return 6;
    case FDA_EV_SHO:   return 7;
    case FDA_EV_SHS:   return 8;
    case FDA_EV_SHC:   return 9;
    case FDA_EV_MES:   return 10;
    case FDA_EV_ORD:   return 11;
    case FDA_EV_CCD:   return 12;
    case FDA_EV_ITM:   return 13;
    case FDA_EV_LNE:   return 14;
    case FDA_EV_USR:   return 15;
	case FDA_GRP_MAIN: return 16;
	case FDA_GRP_CHAT: return 17;
	case FDA_GRP_QUES: return 18;
	case FDA_GRP_ANSW: return 19;
	case FDA_GRP_OFRS: return 20;
	case FDA_GRP_PRIC: return 21;
	case FDA_GRP_OPIN: return 22;
	case FDA_GRP_USER: return 23;
	case FDA_GRP_ORDS: return 24;
	case FDA_GRP_GEIC: return 25;
	case FDA_GRP_FEED: return 26;
	case FDA_GRP_MESE: return 27;
	case FDA_GRP_NETK: return 28;
	case FDA_GRP_TASK: return 29;
	case FDA_GRP_FRID: return 30;
	case FDA_GRP_INFO: return 31;
    default:           assert(0);
    }
}

int event_find_index_by_name(char *s)
{
	int i;

	if (NULL == s) {
		return -1;
	}
	for (i = 0; i < FDA_TYPES_MAX; i++) {
		printf("%d %s %s\n", i, s, g_ev_name_by_index[i]);
		if (strcmp(s, g_ev_name_by_index[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int event_check_ids(win_info_p win, mes_info_p mes, int ev_nr)
{
	int win_i, mes_i, ret = FALSE;

	if (0 == win->ev.ids_len[ev_nr]) {
		/* zero means any id */
		ret = TRUE;
	} else if (0 == mes->ev.ids_len[ev_nr]) {
		/* ??? */
		ret = TRUE;
	} else {
		/* TRUE if win ids set include any of id from mes set */
		for (mes_i = 0; (!ret) && (mes_i < mes->ev.ids_len[ev_nr]); mes_i++) {
			for (win_i = 0; win_i < win->ev.ids_len[ev_nr]; win_i++) {
				if (mes->ev.ids[ev_nr][mes_i] == win->ev.ids[ev_nr][win_i]) {
					ret = TRUE;
					break;
				}
			}
		}
	}
	return ret;
}
