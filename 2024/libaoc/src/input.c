#include <stdio.h>
#include <stdlib.h>

#include <aoc/input.h>

/*
 * Open input stream
 */
FILE *input_stream(const int argc, const char *const argv[])
{
        FILE *input;

        if (argc < 2)
                return stdin;

        input = fopen(argv[1], "r");

        if (input == NULL) {
                fprintf(stderr, "Failed to open %s", argv[1]);
                perror("fopen()");
                fprintf(stderr, "Usage: %s [input]\n", argv[0]);
                exit(EXIT_FAILURE);
        }

        return input;
}

/*
 * Return input stream number of lines
 */
int input_nl(FILE *const stream)
{
        long offset = ftell(stream);
        int count = 0;
        int c;

        fseek(stream, 0L, SEEK_SET);

        for (c = getc(stream); c != EOF; c = getc(stream)) {
                if (c == '\n')
                        ++count;
        }

        fseek(stream, offset, SEEK_SET);

        return count;
}

/*
 * Return input stream line size
 */
int input_len(FILE *const stream)
{
        long offset = ftell(stream);
        int size = 0;
        int c;

        fseek(stream, 0L, SEEK_SET);

        for (c = getc(stream); (c != EOF) && (c != '\n'); c = getc(stream))
                ++size;

        fseek(stream, offset, SEEK_SET);

        return size;
}
