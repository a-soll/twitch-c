#include <stdbool.h>

typedef struct Channel {
    char *loginid;
    char *id;
    bool is_live;
    char *started_at;
    char *title;
};
