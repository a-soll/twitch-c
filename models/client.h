#ifndef CLIENT_H
#define CLIENT_H

#include <curl/curl.h>
#include "../util.h"

typedef struct Client {
    const char *url;
    const char *client_id;
    const char *client_secret;
    char *memory;
    size_t size;
    struct json_object *fields;
    struct curl_slist *headers;
    CURL *curl_handle;
} Client;

void Client_init(Client *c, const char *client_id, const char *client_secret);

void Client_login(Client *client);

void Client_deinit(Client *c);

void curl_get(Client *client, const char *url);

#endif // !CLIENT_H
