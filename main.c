#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

void *user_mod_handler = NULL;
int (*user_add)(int n) = NULL;
int (*user_get)(int n) = NULL;

static int open_user_mod() {
    user_mod_handler = dlopen("libuser.so", RTLD_NOW | RTLD_GLOBAL);
    if (!user_mod_handler) {
        printf("%s\n", dlerror());
        return -1;
    }

    user_add = dlsym(user_mod_handler, "add");
    user_get = dlsym(user_mod_handler, "get");
    if (!user_add || !user_get) {
        printf("%s\n", dlerror());
        return -1;
    }
    return 0;
}

static void close_mod_user() {
    dlclose(user_mod_handler);
}

int main(int argc, char **argv) {
    init_cache();

    open_user_mod();
    int user = 4;
    user_add(user);
    user = user_get(0);
    printf("%d\n", user);
    close_mod_user();

    open_user_mod();
    user = user_get(0);
    printf("%d\n", user);
    close_mod_user();

    exit(0);
}
