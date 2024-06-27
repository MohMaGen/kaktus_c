#include "types.h"
#include <stdlib.h>
#include <string.h>

string mk_string(char *data, size_t len) {
    return (string) { len, data };
}

string al_string(const char *data_to_copy, size_t len)
{
    char * data;

    data = (char*) malloc(len * sizeof(char));
    strcpy(data, data_to_copy);

    return (string) {len, data};
}

string mk_string_nt(char *data) {
    return (string) { strlen(data), data };
}

string al_string_nt(const char *data_to_copy)
{
    size_t  len;
    char    *data;

    len     = strlen(data_to_copy);
    data    = (char*) malloc(len * sizeof(char));
    strcpy(data, data_to_copy);

    return (string) {len, data};
}

string sl_string(char *data, range slice) {
    return (string) {range_len(slice), data + slice.start};
}

char* nt_string(string from) {
    char *data;

    data = (char*) malloc((from.len + 1) * sizeof(char));
    memcpy((void*)data, (void*)from.data, from.len);
    data[from.len] = '\0';

    return data;
}

int string_eq(string fst, string snd)
{
    if (fst.len != snd.len) {
        return 0;
    }

    for (size_t idx = 0; idx < fst.len; idx++) {
        if (fst.data[idx] != snd.data[idx]) {
            return 0;
        }
    }

    return 1;
}


size_t string_hash(string from) //k=33 algoritm
{
    size_t hash, str_iter;
    int c;

    hash = 5381;
    for (str_iter = 0; str_iter < from.len; str_iter++) {
        c = ((unsigned char*) from.data)[str_iter];
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}
