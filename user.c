#include "user.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

static int *user_list = NULL;
static int i = 0;

int add(int id) {
    user_list[i % 100] = id;
    return id;
}

int del(int n) {
    user_list[n % 100] = 0;
    return n;
}

int get(int n) {
    return user_list[n % 100];
}

void __attribute__((constructor)) init_user(void) {
    printf("init_user\n");
    int *old_list = cache_get_value_addr("user");
    if (old_list)
        user_list = old_list;
    else
        user_list = malloc(sizeof(int) * 100);
}

void __attribute__((destructor)) fini_user(void) {
    printf("fnit_user\n");
    cache_set_value_addr("user", user_list);
}
