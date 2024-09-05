#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// add 5 byte chunk 
// 4 bytes for int, 1 byte for char
// void concat_res(char **res, int *res_size, int amount, char c) {
//     // error checking maybe...
//     if (*res = NULL)
//         *res = malloc(sizeof(char) * 5);
//     else
//         *res = realloc(*res, *res_size + 5);

//     *((int *) (*res + *res_size)) = amount;
//     *(*res + *res_size + 4) = c;
//     *res_size += 5;
// }

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    // char *res = NULL;
    // int res_size = 0;

    int first = 1;
    int prev = 0;
    int curr = 0;
    int count = 1;

    for (int i = 1; i < argc; i++) {
        FILE *file = fopen(argv[i], "r");

        // set prev for the first file
        if (first) {
            curr = fgetc(file);
            first = 0;
        }

        do {
            prev = curr;
            int temp = fgetc(file);

            if (temp != EOF) 
                curr = temp;

            if (prev == curr && temp != EOF) {
                count++;
            }
            else {
                // concat_res(&res, &res_size, count, (char) prev);

                if (temp != EOF || (temp == EOF && i == argc - 1)) {
                    fwrite(&count, 4, 1, stdout);
                    fwrite(&prev, 1, 1, stdout);
                    count = 1;
                }
                if (temp == EOF) break;
            }
        }
        while (1);

        fclose(file);
    }

    // fwrite(res, 1, res_size, stdout);
}