#include "channel.h"

void Channel_deinit(Channel *c) {
    free(c->id);
    free(c->loginid);
    free(c->started_at);
    free(c->title);
}

void Channel_get(Client *client, Channel *c) {
    
}
