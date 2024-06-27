#include "greeting.h"
#include "stdio.h"
#include "types.h"

int main(int argc, char **argv) {
    greet(argc, argv);

    ht_string *data = ht_string_alloc();

    ht_string_insert(data, mk_string_nt("first"), mk_string_nt("value"));
    ht_string_insert(data, mk_string_nt("second"), mk_string_nt("bibibibi"));
    ht_string_insert(data, mk_string_nt("third"), mk_string_nt("3"));
    printf("[ data ]\n");
    ht_string_print(data);
    printf("\n");

    const string *first = ht_string_get_const(data, mk_string_nt("first"));
    printf("first is <<%s>>\n", nt_string(*first));

    string *second = ht_string_get(data, mk_string_nt("second"));
    printf("second is <<%s>>\n", nt_string(*second));
    *second = mk_string_nt("ABEMA");
    second = ht_string_get(data, mk_string_nt("second"));
    printf("second is <<%s>>\n", nt_string(*second));

    printf("[ data ]\n");
    ht_string_print(data);
    printf("\n");
    return 0;
}
