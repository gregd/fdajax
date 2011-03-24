#include "mod_fdajax_defs.h"

void group_init(grp_info_p grp, int i)
{
    grp->grp_id = i;
    message_list_init(&(grp->mes_list));
    grp->first_node = grp->last_node = NULL;
}

grp_info_p group_find(plugin_data *p, unsigned int ev)
{
    int i = event_bit_to_index(ev);
    if (i >= FDA_GRP_START && i <= FDA_GRP_END) {
        return &(p->groups[i - FDA_GRP_START]);
    } else {
        return NULL;
    }
}

void group_add_window(grp_info_p grp, win_info_p win)
{
    win_node_p node = malloc(sizeof(win_node_t));
    if (!node) {
        return;
    }
    node->win = win;
    node->next = node->prev = NULL;
    if (NULL == grp->first_node) {
        grp->first_node = grp->last_node = node;
        return;
    }
    grp->last_node->next = node;
    node->prev = grp->last_node;
    grp->last_node = node;
}

void group_rm_window(grp_info_p grp, win_info_p win)
{
    win_node_p node = grp->first_node;;

    while (node && node->win != win) {
        node = node->next;
    }
    if (!node) {
        return;
    }
    if (grp->first_node == node) { grp->first_node = node->next; }
    if (grp->last_node == node)  { grp->last_node = node->prev; }
    if (node->next)              { node->next->prev = node->prev; }
    if (node->prev)              { node->prev->next = node->next; }
    node->next = node->prev = NULL;

    free(node);
}

void group_remove_old_mes(server *srv, plugin_data *p)
{
    grp_info_p grp;
    int i;

    for (i = 0; i < FDA_MAX_GROUPS; i++) {
        grp = &(p->groups[i]);
        message_remove_old(srv, p, &(grp->mes_list));
    }
}
