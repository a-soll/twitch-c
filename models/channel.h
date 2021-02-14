#include "client.h"
#include <stdbool.h>

typedef struct Channel {
    char loginid[25];
    char id[10];
    bool is_live;
    char started_at[5];
    char title[140];
} Channel;

void Channel_init(Channel *c);

void Channel_deinit(Channel *c);

void Channel_get(Client *client, Channel *c);
