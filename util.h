#ifndef UTIL_H
#define UTIL_H

#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);

const char *get_key(struct json_object *from, const char *key);

int fmt_string(char *to, const char *s, ...);

// reset size and memory
void clean_up(void *client);

#endif
