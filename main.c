#include "creds.h" // client_id and cliend_secret
#include "models/channel.h"
#include "models/client.h"
#include "util.h"
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sprint(s)   printf("%s\n", s);

int main() {
    Client client;
    Client_init(&client, client_id, client_secret);
    Client_login(&client);

    Channel channel;
    Channel_init(&channel);
    Channel_get(&client, &channel, "galoiska");
    puts(channel.id);
    puts(channel.started_at);

    sprint(channel.id);
    Client_deinit(&client);

    return 0;
}
