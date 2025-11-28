#ifndef AOC_INPUT_H
#define AOC_INPUT_H

#include <stdio.h>

/*
 * Open input stream
 */
FILE *input_stream(int argc, const char *const argv[]);

/*
 * Return input stream number of lines
 */
int input_nl(FILE* stream);

/*
 * Return input stream line size
 */
int input_len(FILE* stream);

#endif /* aoc/input.h */
