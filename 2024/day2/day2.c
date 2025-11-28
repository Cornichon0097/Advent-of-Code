#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <aoc/input.h>

#define OPPOSITE_SIGNS(a, b) (((a) ^ (b)) >> 31)

/*
 * Determine whether the specified report is safe
 */
static int is_safe(const char *const report)
{
        char *token;
        int val, prev;
        int delta;

        prev  = (int) strtol(report, &token, 10);
        delta = 0;

        while ((*token != '\n') && (*token != '\0')) {
                val = (int) strtol(token, &token, 10);

                if ((abs(prev - val) == 0) || (abs(prev - val) > 3))
                        return 0;

                if (delta == 0)
                        delta = prev - val;
                else if (OPPOSITE_SIGNS(delta, prev - val))
                        return 0;

                for (; *token == ' '; ++token)
                        ;

                prev = val;
        }

        return 1;
}

/*
 * Remove the next element pointed to by token in a report
 */
static char *remove_next(char *token)
{
        for (; *token == ' '; ++token)
                ;

        for (; (*token != ' ') && (*token != '\n'); ++token)
                *token = ' ';

        return token;
}

/*
 * Determine whether the specified report is safe
 */
static int dampaner(const char *const report)
{
        char buf[BUFSIZ];
        char *token;

        token = strcpy(buf, report);

        while (*token != '\n') {
                token = remove_next(token);

                if (is_safe(buf))
                        return 1;

                memcpy(buf, report, token - buf);
        }

        return 0;
}

/*
 * Main function
 */
int main(const int argc, const char *const argv[])
{
        FILE *input;
        char buf[BUFSIZ];
        int count;

        input = input_stream(argc, argv);
        count = 0;

        while (fgets(buf, BUFSIZ, input)) {
                /* if (is_safe(buf)) */
                if (dampaner(buf))
                        ++count;
        }

        printf("%d\n", count);

        fclose(input);

        return EXIT_SUCCESS;
}
