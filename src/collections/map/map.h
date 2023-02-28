#ifndef MAP_H
#define MAP_H

#include <stddef.h>

#define map_add(key, value) _Generic((key), \
    char*: _Generic(value) \
        int: si_map_add
)

#define CAPACITY 16

typedef struct si_map si_map;
struct si_map {
    char* key;
    int value;
};

struct map {
    
}

int si_map_init();
int si_map_clear();
int si_map_add(char*, int);
int si_map_containes_key(char*);

#endif