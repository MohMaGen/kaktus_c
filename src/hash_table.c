#include "types.h"
#include <stdio.h>


implement_hash_table(ht_string, string, string, string_hash, string_eq)
void ht_string_fprint(FILE *output, ht_string *table) {
    ht_string_row *row_iter = NULL;
    ht_string_item *item_iter = NULL;
    while (ht_string_iter(table, &row_iter, &item_iter)) {
        fprintf(output, "`%s`: `%s`\n", nt_string(item_iter->key), nt_string(item_iter->value));
    }
}

void ht_string_print(ht_string *table) {
    ht_string_fprint(stdout, table);
}



