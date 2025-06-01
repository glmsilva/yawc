#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wchar.h>

long cflines(FILE *file);
long cfwords(FILE *file);
long cfbytes(FILE *file);
long cfchars(FILE *file);

typedef struct
{
    long words;
    long chars;
    long lines;
    long bytes;
} Counter;

int main(int argc, char *argv[])
{

    if (argc <= 2)
    {
        char *path = argv[1];
        FILE *file = fopen(path, "r");

        if (!file)
        {
            fprintf(stderr, "Error handling file %s\n", path);
            return 1;
        }

        Counter c;
        
        c.words = cfwords(file);
        rewind(file);
        c.lines = cflines(file);
        rewind(file);
        c.bytes = cfbytes(file);
        rewind(file);

        printf("%ld %ld %ld %s\n", c.lines, c.words, c.bytes,
               path);
    }

    if (argc >= 3)
    {
        char *op = argv[1];
        char *path = argv[2];

        if (strcmp(op, "-c") == 0)
        {
            FILE *file = fopen(path, "r");

            Counter c;
            c.bytes = cfbytes(file);

            printf("%ld %s\n", c.bytes, path);
        }
        else if (strcmp(op, "-l") == 0)
        {
            FILE *file = fopen(path, "r");

            Counter c;
            c.lines = cflines(file);

            printf("%ld %s\n", c.lines, path);
        }
        else if (strcmp(op, "-w") == 0)
        {
            FILE *file = fopen(path, "r");

            Counter c;
            c.words = cfwords(file);

            printf("%ld %s\n", c.words, path);
        }
        else if (strcmp(op, "-m") == 0)
        {
            FILE *file = fopen(path, "r");

            Counter c;
            c.chars = cfchars(file);

            printf("%ld %s\n", c.chars, path);
        }
    }

    return 0;
}

long cfbytes(FILE *file)
{
    if (!file)
    {
        fprintf(stderr, "Error opening file\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);

    long fileSize = ftell(file);

    if (fileSize == -1L)
    {
        perror("ftell failed");
    }
    else
    {
        return fileSize;
    }
}

long cflines(FILE *file)
{
    char *line_buf = NULL;
    size_t line_buf_size = 0;

    int line_count = 0;
    ssize_t line_size;

    if (!file)
    {
        fprintf(stderr, "Error opening file\n");
        return 1;
    }

    line_size = getline(&line_buf, &line_buf_size, file);

    while (line_size >= 0)
    {
        line_count++;

        line_size = getline(&line_buf, &line_buf_size, file);
    }

    free(line_buf);
    line_buf = NULL;

    return line_count;
}

long cfwords(FILE *file)
{
    if (!file)
    {
        fprintf(stderr, "Error opening a file\n");
        return 1;
    }

    char *line_buf = NULL;
    size_t line_buf_size = 0;
    ssize_t line_size;

    long word_count = 0;
    bool in_word = false;

    while ((line_size = getline(&line_buf, &line_buf_size, file)) >= 0)
    {
        for (int i = 0; i < line_size; i++)
        {
            if (isspace(line_buf[i]))
            {
                in_word = false;
            }
            else if (!in_word)
            {
                in_word = true;
                word_count++;
            }
        }
    }

    free(line_buf);
    line_buf = NULL;

    return word_count;
}

long cfchars(FILE *file)
{
    if (!file)
    {
        fprintf(stderr, "Error handling file \n");
        return 1;
    }

    int c;
    int char_counter = 0;

    setlocale(LC_ALL, "");

    while ((c = fgetwc(file)) != WEOF)
    {
        char_counter++;
    }

    return char_counter;
}