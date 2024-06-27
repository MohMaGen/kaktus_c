#include "greeting.h"
#include <stdio.h>


const char kaktus[] =   "\n\n"
                        " _         _    _                   \n"
                        "| | ____ _| | _| |_ _   _ ___   ___ \n"
                        "| |/ / _` | |/ / __| | | / __| / __|\n"
                        "|   < (_| |   <| |_| |_| \\__ \\| (__ \n"
                        "|_|\\_\\__,_|_|\\_\\\\__|\\__,_|___(_)___|\n"
                        "                                    \n"
                        "\n\n";

void greet(int argc, char **argv) {
    puts(kaktus);

    puts("==========[ args ]==========");
    for (unsigned int iterator = 0; iterator < argc; iterator++) {
        printf(" %d %s\n", iterator, *(argv + iterator));
    }
}
