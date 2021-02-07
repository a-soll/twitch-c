#include "creds.c" // client_id and cliend_secret
#include "request.h"
#include "util.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    CURL *curl_handle;
    CURLcode res;
    char buffer[200];

    struct Client client;
    client.url = "https://api.twitch.tv/helix";
    client.memory = malloc(1);
    client.size = 0;
    client.client_id = client_id;
    client.client_secret = client_secret;
    client.headers = NULL;

    struct json_object *parsed_json;

    curl_handle = curl_easy_init();

    login(&client, curl_handle);
    printf("%s\n", client.bearer);

    free(client.memory);
    return 0;
}
