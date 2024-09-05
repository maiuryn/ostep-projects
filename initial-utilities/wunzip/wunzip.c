#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");
        
        long buf = 0;
        ssize_t read = fread(&buf, 5, 1, file); 

        while (read > 0) {
            int count = (int) buf;
            char c = (char) *((long *) (((char *)&buf) + 4));

            for (int i = 0; i < count; i++)
                printf("%c", c);

            read = fread(&buf, 5, 1, file); 
        }

        fclose(file); 
    }

    return 0;
}