#include "creds.c" // client_id and cliend_secret
#include "request.h"
#include "util.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    CURLcode res;
    char buffer[200];

    struct Client client;
    client.url = "https://api.twitch.tv/helix";
    client.memory = malloc(1);
    client.size = 0;
    client.client_id = client_id;
    client.client_secret = client_secret;
    client.headers = NULL;
    client.curl_handle = NULL;

    struct json_object *parsed_json;


    login(&client);
    search(&client, "channels", "query=loserfruit");
    // search(&client, "channels", "query=pokimane");
    free(client.memory);

    return 0;
}
