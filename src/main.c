#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    if (argc >= 3) {
        if (strcmp(argv[1], "-c") == 0){
            char *op = argv[1];
            char *path = argv[2];
            
            FILE *file = fopen(path, "r");

            fseek(file, 0, SEEK_END);

            long fileSize = ftell(file);
            if (fileSize == -1L) {
                perror("ftell failed");
            }
            else {
                printf("%ld %s\n", fileSize, path);
            }
        } else if (strcmp(argv[1], "-l") == 0) {
            char *op = argv[1];
            char *path = argv[2];

            FILE *file = fopen(path, "r");

            char *line_buf = NULL;
            size_t line_buf_size = 0;

            int line_count = 0;
            ssize_t line_size;

            if (!file) {
                    fprintf(stderr, "Error opening file %s\n", path);
                    return 0;
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
        }
    }
    
    return 0;
}
