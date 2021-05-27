#ifndef MATH_MODULE_H
#define MATH_MODULE_H

#include <stdio.h>

#define EXIT_SUCCESS 0
#define EXIT_EMPTY_FILE -1
#define EXIT_INVALID_ELEMENT -2

int calculate_sequence_params(FILE *f, float *avg, float *max, float *min);
int calculate_sigma(FILE *f, float avg, float *sigma);

#endif
