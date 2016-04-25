#include "time.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char *argv[])
{
    time_t t;
    int i = 0;

    if (argc == 1) {
        printf("%s ...\n", argv[0]);
        return 0;
    }

    for (i = 1; i < argc; i++) {
        t = atoi(argv[i]);
        printf("%s : %s\n", argv[i], ctime(&t));
    }

    return 0;
}
