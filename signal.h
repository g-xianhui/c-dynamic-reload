#ifndef SIGNAL_H
#define SIGNAL_H

#include <signal.h>

typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);

#endif
