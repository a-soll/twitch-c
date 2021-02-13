#include "creds.h" // client_id and cliend_secret
#include "request.h"
#include "util.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    struct Client client;
    client.url = "https://api.twitch.tv/helix";
    client.fields = json_object_new_object();
    client.memory = malloc(1);
    client.size = 0;
    client.client_id = client_id;
    client.client_secret = client_secret;
    client.headers = NULL;
    client.curl_handle = NULL;

    login(&client);

    search(&client, "channels", "query=sodapoppin");
    // search(&client, "channels", "query=loserfruit");
    printf("%s\n", json_object_to_json_string_ext(client.fields, JSON_C_TO_STRING_PRETTY));
    // printf("%s\n", json_object_to_json_string(client.fields));
    json_object_put(client.fields);
    curl_slist_free_all(client.headers);
    curl_easy_cleanup(client.curl_handle);
    free(client.memory);
    return 0;
}
