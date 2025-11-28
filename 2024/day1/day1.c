#include <stdlib.h>
#include <stdio.h>

#include <aoc/input.h>

/*
 * Parse input stream
 */
static int parse(FILE *const stream, int **const left, int **const right)
{
        char buf[BUFSIZ];
        int *l, *r;
        int size = input_nl(stream);

        *left  = (int *) malloc(size * sizeof(int));
        *right = (int *) malloc(size * sizeof(int));

        l = *left;
        r = *right;

        while (fgets(buf, BUFSIZ, stream))
                sscanf(buf, "%d %d\n", l++, r++);

        return size;
}

/*
 * Compare two integers
 */
static int compare(const void *const a, const void *const b)
{
        return (*(int *) a - *(int *) b);
}

/*
 * Compute the distance between two lists
 */
static int distance(int *const left, int *const right, const int size)
{
        int distance = 0;
        int i;

        qsort(left, size, sizeof(int), &compare);
        qsort(right, size, sizeof(int), &compare);

        for (i = 0; i < size; ++i)
                distance = distance + left[i] + right[i];

        return distance;
}

/*
 * Compute the similarity score between two lists
 */
static int sim_score(int *const left, int *const right, const int size)
{
        int score = 0;
        int val, l, r;
        int i, j;

        qsort(left, size, sizeof(int), &compare);
        qsort(right, size, sizeof(int), &compare);

        for (i = 0, r = 0; (i < size) && (r < size); i = l) {
                val = left[i];

                for (l = i; left[l] == val; ++l)
                        ;

                for (j = r; right[j] < val; ++j)
                        ;

                for (r = j; right[r] == val; ++r)
                        ;

                score = score + val * (l - i) * (r - j);
        }

        return score;
}

/*
 * Main function
 */
int main(const int argc, const char *const argv[])
{
        FILE *input;
        int *left, *right;
        int size;

        input = input_stream(argc, argv);
        size  = parse(input, &left, &right);
        fclose(input);

        /* printf("%d\n", distance(left, right, size)); */
        printf("%d\n", sim_score(left, right, size));

        free(left);
        free(right);

        return EXIT_SUCCESS;
}
