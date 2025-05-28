#include <stdio.h> 
#include <string.h>
#include <limits.h>

int main(int argc, char* argv[]) {
    if (argc >= 2) {
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
        }
    }
    
    return 0;
}
