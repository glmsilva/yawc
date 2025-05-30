#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    if (argc >= 3) {
        char *op = argv[1];
        char *path = argv[2];

        if (strcmp(op, "-c") == 0){
            FILE *file = fopen(path, "r");

            if (!file) {
                    fprintf(stderr, "Error opening file %s\n", path);
                    return 0;
            }

            fseek(file, 0, SEEK_END);

            long fileSize = ftell(file);
            if (fileSize == -1L) {
                perror("ftell failed");
            }
            else {
                printf("%ld %s\n", fileSize, path);
            }
        } else if (strcmp(op, "-l") == 0) {
            FILE *file = fopen(path, "r");

            char *line_buf = NULL;
            size_t line_buf_size = 0;

            int line_count = 0;
            ssize_t line_size;

            if (!file) {
                    fprintf(stderr, "Error opening file %s\n", path);
                    return 1;
            }

            line_size = getline(&line_buf, &line_buf_size, file);

            while (line_size >= 0) {
                line_count++;

                line_size = getline(&line_buf, &line_buf_size, file);
            }

            free(line_buf);
            line_buf = NULL;

            fclose(file);

            printf("%d %s\n", line_count, path);
        } else if (strcmp(op, "w")) {
            FILE *file = fopen(path, "r");

            if (!file) {
                fprintf(stderr, "Error opening a file %s\n", path);
                return 1;
            }

            char *line_buf = NULL;
            size_t line_buf_size = 0;

            ssize_t line_size;

            line_size = getline(&line_buf, &line_buf_size, file);
            long word_count = 0;

            while(line_size >= 0) {
                for (int i = 0; i <= strlen(line_buf); i++) {
                    if (line_buf[i] == ' ' && line_buf[i + 1] != ' ') {
                      word_count++; 
                    }
                }

                line_size = getline(&line_buf, &line_buf_size, file);
            }

            free(line_buf);
            line_buf = NULL;

            fclose(file);

            printf("%ld %s\n", word_count, path);
        }
    }
    
    return 0;
}
