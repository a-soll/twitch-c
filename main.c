#include "creds.h" // client_id and cliend_secret
#include "models/client.h"
#include "models/channel.h"
#include "util.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Client client;
    Client_init(&client, client_id, client_secret);
    Client_login(&client);

    Channel channel;
    Channel_init(&channel);
    Channel_get(&client, &channel, "sodapoppin");
    // search(&client, "channels", "query=loserfruit");
    // printf("%s\n", json_object_to_json_string_ext(client.fields, JSON_C_TO_STRING_PRETTY));

    Client_deinit(&client);

    return 0;
}
