#include <stdio.h>

int main(int argc, char *argv[])
{
    unsigned long result = 0;
    int i = 0;

    if (argc == 1) {
        printf("%s hex...\n", argv[0]);
        return 0;
    }

    for (i = 1; i < argc; i++) {
        result = 0;
        sscanf(argv[i], "%lx", &result);
        printf("[Hex] %s : [DEC] %lu\n", argv[i], result);
    }

    return 0;
}
