#include <stdbool.h>
#include "client.h"

typedef struct Channel {
    const char *endpoint;
    char broadcaster_language[2];
    const char *loginid;
    char game_id[10];
    char id[10];
    bool is_live;
    char started_at[25];
    char title[140];
    char thumbnail_url[2048];
} Channel;

void Channel_init(Channel *c);

void Channel_deinit(Channel *c);

// Search for a channel by channel login name
void Channel_get(Client *client, Channel *c, const char *login_name);
