#include "cache.h"
#include "table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Table_T key_addrs = NULL;

static int str_cmp(const void *x , const void *y) {
    return strcmp(x, y);
}

static unsigned str_hash(const void *_str) {
    const char *str = (const char *)_str;
    unsigned int hash = 0;
    while (*str) {
        // equivalent to: hash = 65599*hash + (*str++);
        hash = (*str++) + (hash << 6) + (hash << 16) - hash;
    }
    return (hash & 0x7FFFFFFF);
}

void init_cache() {
    printf("init_cache\n");
    key_addrs = Table_new(0, str_cmp, str_hash);
}

void cache_set_value_addr(const char *key, void *addr) {
    printf("set_value_addr [%s:%p]\n", key, addr);
    Table_put(key_addrs, key, addr);
}

void* cache_get_value_addr(const char *key) {
    printf("get_value_addr[%s]\n", key);
    return Table_get(key_addrs, key);
}
