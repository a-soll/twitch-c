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

    json_object_put(client->fields);
    fmt_string(url, "%s/search/%s?query=%s", client->url, c->endpoint, login_name);
    curl_get(client, url);

    res = curl_easy_perform(client->curl_handle);

    response = json_tokener_parse(client->memory);
    data = json_object_object_get(response, "data");
    data_len = json_object_array_length(data);

    for (int i = 0; i < data_len; i++) {
        data_array_obj = json_object_array_get_idx(data, i);
        login = json_object_get_string(json_object_object_get(data_array_obj, "broadcaster_login"));
        if (strcmp(login, login_name) == 0) {
            c->loginid = login;
        }
    }
    json_object_put(response);
    json_object_put(data);
    json_object_put(data_array_obj);
    clean_up(client);
}
