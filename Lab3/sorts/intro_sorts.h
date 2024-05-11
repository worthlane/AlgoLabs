#ifndef __INTRO_H
#define __INTRO_H

static const size_t SHELL_BLOCK    = 85;            // experimental value from 6th point

static const int    OPTIMAL_COEF   = 20;            // experimental value
static const int    OPTIMAL_HEAP_K = 5;            	// experimental value

void TestCoefIntro_sort(int* arr, const size_t n, const int C);
void OptimalIntro_sort(int* arr, const size_t n);

#endif
