#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stdint.h>

#define hash_table(name, key_type, value_type)\
    typedef struct{\
        key_type key;\
        value_type value;\
    } name ## _item;\
    \
    typedef struct{\
        size_t len;\
        name ## _item *items;\
    } name ## _row;\
    \
    typedef struct {\
        size_t size, capacity;\
        name ## _row *data;\
    } name\

#endif
