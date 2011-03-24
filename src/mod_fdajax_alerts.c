#include "mod_fdajax_defs.h"

void alert_free_slot(user_info_p user, size_t i)
{
	if (user->alerts[i].id > 0) {
		user->alerts[i].id = 0;
		if (user->alerts[i].mes) {
			buffer_free(user->alerts[i].mes);
			user->alerts[i].mes = NULL;
		}
	}
}

unsigned int alert_max_id(user_info_p user)
{
	unsigned int ret = 0;
	size_t i;

	for (i = 0; i < ALERTS_MAX; i++) {
		if (user->alerts[i].id > ret) {
			ret = user->alerts[i].id;
		}
	}
	return ret;
}

int alert_cancel(user_info_p user, unsigned int id)
{
	size_t i;

	if (0 == id) {
		return FALSE;
	}
	for (i = 0; i < ALERTS_MAX; i++) {
		if (user->alerts[i].id == id) {
			alert_free_slot(user, i);
			return TRUE;
		}
	}
	return FALSE;
}

size_t alert_find_slot(user_info_p user)
{
	size_t i, j = 0, min_id = UINT_MAX;

	for (i = 0; i < ALERTS_MAX; i++) {
		if (user->alerts[i].id == 0) {
			return i;
		}
		if (user->alerts[i].id < min_id) {
			j = i;
			min_id = user->alerts[j].id;
		}
	}
	alert_free_slot(user, j);
	return j;
}

int alert_add(server *srv, plugin_data *p, connection *con, user_info_p user, user_request_p req)
{
	size_t i;
	alert_info_p palert;

    UNUSED(srv);
    UNUSED(p);
    UNUSED(con);

	i = alert_find_slot(user);
	palert = &(user->alerts[i]);

	palert->id = ++(user->last_alert);
    palert->mes = req->mes;
    req->mes = NULL;

	return TRUE;
}

int alert_add_from_mes(server *srv, plugin_data *p, user_info_p user, mes_info_p mes)
{
	size_t i;
	alert_info_p palert;

    UNUSED(srv);
    UNUSED(p);

	i = alert_find_slot(user);
	palert = &(user->alerts[i]);

	palert->id = ++(user->last_alert);

	palert->mes = buffer_init();
	buffer_append_string_buffer(palert->mes, p->unw_prefix);	
	buffer_append_string_buffer(palert->mes, mes->mes);	
	return TRUE;	
}

int alert_append(server *srv, plugin_data *p, user_info_p user, buffer *buf, unsigned int last_id)
{
	size_t i;
	int count = 0;
    UNUSED(srv);

	for (i = 0; i < ALERTS_MAX; i++) {
		if (user->alerts[i].id > last_id) {
			buffer_append_nl(buf);		   
			buffer_append_string_buffer(buf, p->js_alert_id_func);
			buffer_append_string(buf, "(");
			buffer_append_long(buf, user->alerts[i].id);
			buffer_append_string(buf, ");\n");
			buffer_append_string_buffer(buf, user->alerts[i].mes);			
			count++;
		}
	}
	return count;
}

enum gdc_cmd_t alert_push(server *srv, plugin_data *p, user_info_p user)
{
    win_info_p win;
    size_t i;
	unsigned int maid = alert_max_id(user);
	
	UNUSED(srv);	
	UNUSED(p);

	if (0 == maid) {
		return cmdr_ok;
	}

    for(i = 0; i < WINDOWS_MAX; i++) {
        win = user->windows[i];
        if (NULL == win || 
			NULL == win->con ||
			((win->ev.types & FDA_EV_UNW) == 0) ||
			win->last_alert >= maid) {
            continue;
		}
		alert_append(srv, p, user, window_get_buffer(win), win->last_alert);	   
		win->last_alert = maid;
	}	

    return cmdr_mes_sent;
}
