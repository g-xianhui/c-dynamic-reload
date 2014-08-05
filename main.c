#include "cache.h"
#include "signal.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

void *user_mod_handler = NULL;
int (*user_add)(int n) = NULL;
int (*user_get)(int n) = NULL;
int (*user_print)() = NULL;

static int open_user_mod() {
    user_mod_handler = dlopen("libuser.so", RTLD_NOW | RTLD_GLOBAL);
    if (!user_mod_handler) {
        printf("%s\n", dlerror());
        return -1;
    }

    user_add = dlsym(user_mod_handler, "add");
    user_get = dlsym(user_mod_handler, "get");
    user_print = dlsym(user_mod_handler, "print");
    if (!user_add || !user_get || !user_print) {
        printf("%s\n", dlerror());
        return -1;
    }
    return 0;
}

static void close_mod_user() {
    dlclose(user_mod_handler);
}

static int reload_flag = 0;
static void sig_reload(int signo) {
    reload_flag = 1;
}

int main(int argc, char **argv) {
    init_cache();
    open_user_mod();

    if (signal(SIGTERM, sig_reload) == SIG_ERR) {
        perror("signal");
        exit(-1);
    }

    int i = 1;
    while (1) {
        if (reload_flag) {
            close_mod_user();
            open_user_mod();
            reload_flag = 0;
        }
        user_print();
        user_add(i++);
        sleep(5);
    }

    close_mod_user();
    exit(0);
}
