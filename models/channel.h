#include <stdbool.h>
#include "client.h"

typedef struct Channel {
    const char *endpoint;
    const char *loginid;
    char id[10];
    bool is_live;
    char started_at[5];
    char title[140];
} Channel;

void Channel_init(Channel *c);

void Channel_deinit(Channel *c);

// Search for a channel by channel login name
void Channel_get(Client *client, Channel *c, const char *login_name);
