#include "util.h"
#include "request.h"
#include "models/client.h"
#include <stdarg.h>

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct Client *mem = (struct Client *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        printf("error: not enough memory\n");
        return 0;
    }
    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;
    return realsize;
}

const char *get_key(struct json_object *from, const char *key) {
    struct json_object *val;

    json_object_object_get_ex(from, key, &val);

    return json_object_get_string(val);
}

// formats string to provided array and returns length
int fmt_string(char *to, const char *s, ...) {
    va_list ap;
    int ret;

    va_start(ap, s);
    ret = vsprintf(to, s, ap);
    va_end(ap);

    return ret;
}

void clean_up(void *client) {
    struct Client *mem = (struct Client *)client;
    free(mem->memory);
    mem->memory = NULL;
    mem->size = 0;
}
