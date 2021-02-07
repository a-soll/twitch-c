#include <curl/curl.h>
#include "util.h"

struct Client {
    const char *client_id;
    const char *client_secret;
    char *memory;
    size_t size;
    const char *bearer;
    struct json_object *fields;
    struct curl_slist *headers;
};

CURLcode login(struct Client *client, CURL *curl_handle);
