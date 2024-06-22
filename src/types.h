#include "hash_table.h"
#include <stddef.h>


typedef struct range {
    size_t start, end;
} range;
#define range_len(range) ((range).end - (range).start)

typedef struct string {
    size_t len;
    char *data;
} string;

// crate string owning given data.
string mk_string(char *data, size_t len);

// crate string allocating copy of given data.
string al_string(const char *data, size_t len);

// crate string owning given data.
string mk_string_nt(char *data);

// crate string allocating copy of given data.
string al_string_nt(const char *data);

// crate string from slice of given data.
string sl_string(char *data, range slice);

// allocate new null terminated char array, copy of string data.
const char* nt_string(const string *from);


