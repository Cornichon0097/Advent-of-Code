#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <aoc/input.h>

#define INSTRUCTIONS "md"

#define MUL "mul("

#define DO "do"

#define DONT "don't"

/*
 * Multiply if the instruction is correct
 */
static char *mul(char *str, long *const result)
{
        long a, b;
        char *c;

        if (strncmp(str, MUL, strlen(MUL)) != 0)
                return str + 1;

        str = str + strlen(MUL);
        a   = strtol(str, &c, 10);

        if (*c == ',') {
                str = c + 1;
                b   = strtol(str, &c, 10);

                if (*c == ')')
                        *result = *result + a * b;
        }

        return str;
}

/*
 * "Do or do not. There is no try." - Yoda
 */
char *yoda(char *str, int *const multiply)
{
        if (strncmp(str, DO, strlen(DO)) == 0)
                *multiply = 1;

        if (strncmp(str, DONT, strlen(DONT)) == 0)
                *multiply = 0;

        return str + 1;
}

/*
 * Main function
 */
int main(const int argc, const char *const argv[])
{
        FILE *input;
        char buf[BUFSIZ];
        char *substr;
        long result;
        int multiply;

        input = input_stream(argc, argv);

        result   = 0;
        multiply = 1;

        while (fgets(buf, BUFSIZ, input)) {
                substr = buf;

                while ((substr = strpbrk(substr, INSTRUCTIONS)) != NULL) {
                        switch (*substr) {
                        case 'm':
                                if (multiply)
                                        substr = mul(substr, &result);
                                else
                                        ++substr;
                                break;

                        case 'd':
                                substr = yoda(substr, &multiply);
                                break;

                        default:
                                break;
                        }
                }
        }

        printf("%ld\n", result);

        fclose(input);

        return EXIT_SUCCESS;
}
