#include "request.h"
#include "util.h"
#include <curl/curl.h>

CURLcode login(struct Client *client, CURL *curl_handle) {
    char url[500];
    fmt_string(url, "https://id.twitch.tv/oauth2/token?client_id=%s&client_secret=%s&grant_type=client_credentials", client->client_id, client->client_secret);
    CURLcode res;

    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)client);

    res = curl_easy_perform(curl_handle);
    curl_slist_append(client->headers, "Content-Type: application/json");
    curl_slist_append(client->headers, "Accept: application/json");
    client->fields = json_tokener_parse(client->memory);
    client->bearer = get_key(client->fields, "access_token");
    return res;
}
