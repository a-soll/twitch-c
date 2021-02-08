#include "request.h"
#include "util.h"
#include <curl/curl.h>

CURLcode login(struct Client *client) {
    char url[250];
    fmt_string(url, "https://id.twitch.tv/oauth2/token?client_id=%s&client_secret=%s&grant_type=client_credentials", client->client_id, client->client_secret);
    CURLcode res;
    char header[100];

    client->curl_handle = curl_easy_init();
    curl_easy_setopt(client->curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(client->curl_handle, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEDATA, (void *)client);

    res = curl_easy_perform(client->curl_handle);
    client->fields = json_tokener_parse(client->memory);

    // set client headers
    client->headers = curl_slist_append(client->headers, "Content-Type: application/json");
    client->headers = curl_slist_append(client->headers, "Accept: application/json");

    fmt_string(header, "Authorization: Bearer %s", get_key(client->fields, "access_token"));
    client->headers = curl_slist_append(client->headers, header);

    fmt_string(header, "Client-Id: %s", client->client_id);
    client->headers = curl_slist_append(client->headers, header);

    clean_up(client);
    return res;
}

void get(struct Client *client, const char *endpoint, const char *params) {
    CURLcode res;
    char url[100];

    json_object_put(client->fields);
    fmt_string(url, "%s/%s?%s", client->url, endpoint, params);
    curl_easy_setopt(client->curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(client->curl_handle, CURLOPT_HTTPHEADER, client->headers);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEDATA, (void *)client);

    curl_easy_perform(client->curl_handle);
    client->fields = json_tokener_parse(client->memory);

}

void search(struct Client *client, const char *endpoint, const char *params) {
    CURLcode res;
    char url[100];

    json_object_put(client->fields);
    fmt_string(url, "%s/search/%s?%s", client->url, endpoint, params);
    curl_easy_setopt(client->curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(client->curl_handle, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(client->curl_handle, CURLOPT_HTTPHEADER, client->headers);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEDATA, (void *)client);

    res = curl_easy_perform(client->curl_handle);
    // client->fields = json_tokener_parse(client->memory);
    printf("%s\n", client->memory);
    clean_up(client);
    // printf("%s\n", json_object_to_json_string(client->fields));
}
