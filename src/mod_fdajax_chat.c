#include "mod_fdajax_defs.h"

enum gdc_cmd_t chat_add_peer(user_info_p user, int peer_id)
{
    size_t i;
    enum gdc_cmd_t ret = cmdr_cuser_too_many;

    for(i = 0; i < PEERS_MAX; i++) {
        if (ret == cmdr_cuser_too_many) {
            if (user->peers[i] == 0) {
                user->peers[i] = peer_id;
                ret = cmdr_chat_peer_add;
            }
        } else if (ret == cmdr_chat_peer_add) {
            /* make sure there's no duplicates */
            if (user->peers[i] == peer_id) {
                user->peers[i] = 0;
            }
        } else {
            assert(0);
        }
    }
    return ret;
}

enum gdc_cmd_t chat_rm_peer(user_info_p user, int peer_id)
{
    size_t i;

    for(i = 0; i < PEERS_MAX; i++) {
        if (user->peers[i] == peer_id) {
            user->peers[i] = 0;
            return cmdr_chat_peer_rm_1;
        }
    }
    return cmdr_cuser_not_found;
}

int chat_access_peer(user_info_p user, int peer_id)
{
    size_t i;

    for(i = 0; i < PEERS_MAX; i++) {
        if (user->peers[i] == peer_id) {
            return TRUE;
        }
    }
    return FALSE;
}
