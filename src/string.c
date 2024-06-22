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

const char* nt_string(const string *from) {
    char *data;

    data = (char*) malloc((from->len + 1) * sizeof(char));
    strcpy(data, from->data);
    data[from->len] = '\0';

    return data;
}
