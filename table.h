#ifndef YOGI_TABLE_H_
#define YOGI_TALBE_H_

#define T Table_T
typedef struct T *T;

T Table_new(int hint,
    int cmp(const void *x, const void *y),
    unsigned hash(const void *key));
void Table_free(T *table);

int Table_length(T table);
void * Table_put(T table, const void *key, void *value);
void * Table_get(T table, const void *key);
void * Table_remove(T table, const void *key);

void Table_map(T table,
    void apply(const void *key, void **value, void *cl),
    void *cl);
void ** Table_toArray(T table, void *end);

#undef T
#endif
