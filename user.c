#include "user.h"
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_USER    10

static int *user_list = NULL;
static int i = 0;

int add(int id) {
    user_list[i++ % MAX_USER] = id;
    return id;
}

int del(int n) {
    user_list[n % MAX_USER] = 0;
    return n;
}

int get(int n) {
    return user_list[n % MAX_USER];
}

void print() {
    int i;
    for (i = 0; i < MAX_USER; i++)
        printf("%d ", user_list[i]);
    printf("\n");
}

void __attribute__((constructor)) init_user(void) {
    printf("init_user\n");
    int *old_list = cache_get_value_addr("user_list");
    if (old_list)
        user_list = old_list;
    else
        user_list = malloc(sizeof(int) * MAX_USER);
    cache_get_copy("user_index", &i, sizeof(i));
}

void __attribute__((destructor)) fini_user(void) {
    printf("fnit_user\n");
    cache_set_value_addr("user_list", user_list);
    cache_set_copy("user_index", &i, sizeof(i));
}
