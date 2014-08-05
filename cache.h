#ifndef CACHE_H
#define CACHE_H

void init_cache();
void cache_set_value_addr(const char *key, void *addr);
void* cache_get_value_addr(const char *key);

#endif
