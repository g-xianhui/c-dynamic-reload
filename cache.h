#ifndef CACHE_H
#define CACHE_H

// create cache, call before used
void init_cache();

// cache dynamic alloc data
void cache_set_value_addr(const char *key, void *addr);
void* cache_get_value_addr(const char *key);

// copy size bytes begin at addr into cache
void cache_set_copy(const char *key, void *addr, int size);
// withdraw the copy
void cache_get_copy(const char *key, void *buf, int size);

#endif
