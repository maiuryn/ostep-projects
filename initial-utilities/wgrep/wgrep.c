#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

// usage:
//      ./wgrep foo bar.txt

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    // Take from stdin
    else if (argc == 2) { 
        char buf[1024];

        while (fgets(buf, 1024, stdin) != NULL) {
            if (strstr(buf, argv[1]))
                printf("%s", buf);
        }
    }

    // Take from files
    else if (argc > 2) {
        for (int i = 2; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");

            if (file == NULL) {
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            
            char **lineptr = malloc(sizeof(char *));
            size_t *n = malloc(sizeof(size_t));
            *n = 0;
            *lineptr = NULL;
            while (getline(lineptr, n, file) != -1) {
                if (strstr(*lineptr, argv[1]))
                    printf("%s", *lineptr);
                free(*lineptr);
                *n = 0;
                *lineptr = NULL;
            }

            free(lineptr);
            free(n);
        }
    }

    return 0;
} 