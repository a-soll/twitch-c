#include "util.h"
#include <curl/curl.h>

struct Client {
    const char *url;
    const char *client_id;
    const char *client_secret;
    char *memory;
    size_t size;
    const char *bearer;
    struct json_object *fields;
    struct curl_slist *headers;
};

CURLcode login(struct Client *client, CURL *curl_handle);
