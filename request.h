#include "util.h"
#include <curl/curl.h>

struct Client {
    char *url;
    const char *client_id;
    const char *client_secret;
    char *memory;
    size_t size;
    struct json_object *fields;
    struct curl_slist *headers;
    CURL *curl_handle;
};

CURLcode login(struct Client *client);

void get(struct Client *client, const char *endpoint, const char *params);

void search(struct Client *client, const char *endpoint, const char *params);
