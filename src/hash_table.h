#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define PRIMES_LEN 45


#define declarate_hash_table(name, key_type, value_type)\
    typedef struct{\
        key_type key;\
        value_type value;\
    } name ## _item;\
    \
    typedef struct{\
        size_t len, capacity;\
        name ## _item *items;\
    } name ## _row;\
    \
    typedef struct {\
        size_t len, capacity_idx;\
        name ## _row *rows;\
    } name;\
    const value_type * name ## _get_const(name *table, key_type key);\
    value_type * name ## _get(name *table, key_type key);\
    void name ## _insert(name *table, key_type key, value_type value);\
    name * name ## _alloc(void);\
    name ## _row * name ## _next_row(name *table, name ## _row *row);\
    name ## _item * name ## _next_item_in_row(name *table, name ## _row *row, name ## _item *item);\
    int name ## _iter(name *table, name ## _row **row, name ## _item **item)\


#define implement_hash_table(name, key_type, value_type, hash_func, eq_func)\
    const size_t name ## _primes[PRIMES_LEN] = {\
        7,      19,     37,     61,     127,    271,    331,    397,    547,\
        631,    919,    1657,   1801,   1951,   2269,   2437,   2791,   3169,\
        3571,   4219,   4447,   5167,   5419,   6211,   7057,   7351,   8269,\
        9241,   10267,  11719,  12097,  13267,  13669,  16651,  19441,  19927,\
        22447,  23497,  24571,  25117,  26227,  27361,  33391,  35317,  37633\
    };\
    name ## _row * name ## _next_row(name *table, name ## _row *row) {\
        if (table == NULL) return NULL;\
        if (row == NULL) return table->rows;\
        if (row - table->rows >= name ## _primes[table->capacity_idx] - 1) return NULL;\
        \
        return 1 + row;\
    }\
    name ## _item * name ## _next_item_in_row(name *table, name ## _row *row, name ## _item *item) {\
        if (table == NULL) return NULL;\
        if (row == NULL) return NULL;\
        if (item == NULL) return row->items;\
        if (item - row->items >= row->len - 1) return NULL;\
        \
        return 1 + item;\
    }\
    int name ## _iter(name *table, name ## _row **row, name ## _item **item) {\
        if (table == NULL || row == NULL || item == NULL) return 0;\
        if (*row == NULL) {\
            *row = table->rows;\
            while ((*row)->len == 0) {\
                *row = name ## _next_row(table, *row);\
                if (*row == NULL) return 0;\
            }\
            *item = (*row)->items;\
            return 1;\
        }\
        *item = name ## _next_item_in_row(table, *row, *item);\
        if (*item != NULL) return 1;\
        *row = name ## _next_row(table, *row);\
        if (*row == NULL) return 0;\
        while ((*row)->len == 0) {\
            *row = name ## _next_row(table, *row);\
            if (*row == NULL) return 0;\
        }\
        *item = (*row)->items;\
        return 1;\
    }\
    const value_type * name ## _get_const(name *table, key_type key) {\
        return name ## _get(table, key);\
    }\
    value_type * name ## _get(name *table, key_type key)\
    {\
        size_t row_idx, row_iter;\
        name ## _item *item;\
        name ## _row *row;\
        \
        row_idx = hash_func(key) % name ## _primes[table->capacity_idx];\
        row = table->rows + row_idx;\
        for (row_iter = 0; row_iter < row->len; row_iter++) {\
            item = row->items + row_iter;\
            if (eq_func(item->key, key)) {\
                return &item->value;\
            }\
        }\
        return NULL;\
    }\
    void name ## _rehash(name *table)\
    {\
        name ## _item *item_iter, *item_end, *items;\
        name ## _row *new_rows, *row_end, *row_iter, *new_row;\
        \
        row_end = table->rows + name ## _primes[table->capacity_idx];\
        \
        table->capacity_idx += 1;\
        new_rows = (name ## _row *) malloc(name ## _primes[table->capacity_idx] * sizeof(name ## _row));\
        \
        for (size_t row_idx = 0; row_idx < name ## _primes[table->capacity_idx]; row_idx++) {\
            items = (name ## _item *) malloc(\
                    name ## _primes[table->capacity_idx - 10] * sizeof(name ## _item));\
            new_rows[row_idx] = (name ## _row)\
                    { 0, name ## _primes[table->capacity_idx - 10], items };\
        }\
        for (row_iter = table->rows; row_iter != row_end; row_iter++) {\
            item_end = row_iter->items + row_iter->len;\
            for (item_iter = row_iter->items; item_iter != item_end; item_iter++)\
            {\
                size_t row_idx = hash_func(item_iter->key) % name ## _primes[table->capacity_idx];\
                new_row = new_rows + row_idx;\
                if (new_row->len >= new_row->capacity){\
                    name ## _rehash(table);\
                    return;\
                }\
                new_row->items[new_row->len++] = *item_iter;\
            }\
        }\
    }\
    \
    void name ## _insert(name *table, key_type key, value_type value)\
    {\
        size_t row_idx;\
        value_type *table_value;\
        name ## _row *row;\
        \
        table_value = name ## _get(table, key);\
        if (table_value != NULL) {\
            *table_value = value;\
            return;\
        }\
        row_idx = hash_func(key) % name ## _primes[table->capacity_idx];\
        row = table->rows + row_idx;\
        if (row->len >= row->capacity) {\
            name ## _rehash(table);\
            row_idx = hash_func(key) % name ## _primes[table->capacity_idx];\
            row = table->rows + row_idx;\
        }\
        row->items[row->len++] = (name ## _item) { key, value };\
        table->len += 1;\
    }\
    name * name ## _alloc(void) {\
        name *table;\
        name ## _item *items;\
        table = (name *) malloc(sizeof(name));\
        table->rows = (name ## _row *) malloc(name ## _primes[10] * sizeof(name ## _row));\
        table->len = 0;\
        table->capacity_idx = 10;\
        for (size_t i = 0; i < name ## _primes[10]; i++) {\
            items = (name ## _item *) malloc(name ## _primes[0] * sizeof(name ## _item));\
            table->rows[i] = (name ## _row) { 0, name ## _primes[0], items };\
        }\
        return table;\
    }


#endif
