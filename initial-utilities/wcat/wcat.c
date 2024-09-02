#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(0);
    }

    for (int i = 1; i < argc; i++) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }

        char buf[1024];
        while (fgets(buf, 1024, file) != NULL) {
            printf("%s", buf);
        }
    }

    return 0;
}