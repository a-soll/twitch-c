#include "client.h"

void Client_init(Client *c, const char *client_id, const char *client_secret) {
    c->url = "https://api.twitch.tv/helix";
    c->memory = malloc(1);
    c->size = 0;
    c->client_id = client_id;
    c->client_secret = client_secret;
    c->headers = NULL;
    c->curl_handle = NULL;
}

void Client_deinit(Client *c) {
    json_object_put(c->fields);
    free(c->memory);
    curl_slist_free_all(c->headers);
}

void Client_login(Client *client) {
    char url[250];

    fmt_string(url, "https://id.twitch.tv/oauth2/token?client_id=%s&client_secret=%s&grant_type=client_credentials", client->client_id, client->client_secret);
    char header[100];

    client->curl_handle = curl_easy_init();
    curl_easy_setopt(client->curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(client->curl_handle, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEDATA, (void *)client);

    curl_easy_perform(client->curl_handle);

    client->fields = json_tokener_parse(client->memory);

    // set client headers
    client->headers = curl_slist_append(client->headers, "Content-Type: application/json");
    client->headers = curl_slist_append(client->headers, "Accept: application/json");

    fmt_string(header, "Authorization: Bearer %s", get_key(client->fields, "access_token"));
    client->headers = curl_slist_append(client->headers, header);

    fmt_string(header, "Client-Id: %s", client->client_id);
    client->headers = curl_slist_append(client->headers, header);
    clean_up(client);
}

void curl_get(Client *client, const char *url) {
    client->curl_handle = curl_easy_init();
    curl_easy_setopt(client->curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(client->curl_handle, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(client->curl_handle, CURLOPT_HTTPHEADER, client->headers);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEDATA, (void *)client);
}
