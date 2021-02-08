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


    login(&client);
    search(&client, "channels", "query=loserfruit");

    json_object_put(client.fields);
    curl_slist_free_all(client.headers);
    curl_easy_cleanup(client.curl_handle);
    free(client.memory);
    return 0;
}
