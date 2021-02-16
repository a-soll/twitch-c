#include "channel.h"
#include <json-c/json.h>
#include <string.h>

void Channel_init(Channel *c) {
    c->endpoint = "channels";
}

void Channel_deinit(Channel *c) {
    // free(c->loginid);
    // free(c->started_at);
    // free(c->title);
}

void Channel_get(Client *client, Channel *c, const char *login_name) {
    CURLcode res;
    char url[2048];
    const char *login;
    struct json_object *response, *data, *data_array_obj;
    int data_len;

    fmt_string(url, "%s/search/%s?query=%s", client->url, c->endpoint, login_name);
    // curl_get(client, url);

    client->curl_handle = curl_easy_init();
    curl_easy_setopt(client->curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(client->curl_handle, CURLOPT_CUSTOMREQUEST, "GET");
    curl_easy_setopt(client->curl_handle, CURLOPT_HTTPHEADER, client->headers);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(client->curl_handle, CURLOPT_WRITEDATA, (void *)client);

    res = curl_easy_perform(client->curl_handle);
    response = json_tokener_parse(client->memory);

    data = json_object_object_get(response, "data");
    data_len = json_object_array_length(data);

    // TODO: populate all Channel fields
    for (int i = 0; i < json_object_array_length(data); i++) {
        data_array_obj = json_object_array_get_idx(data, i); // json inside data[] array
        login = get_key(data_array_obj, "broadcaster_login");
        if (strcmp(login, login_name) == 0) {
            c->loginid = login;
            strcpy(c->id, get_key(data_array_obj, "id"));
            break;
        }
    }
    json_object_put(response);
    json_object_put(data_array_obj);
    clean_up(client);
}
