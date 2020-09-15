#ifndef __BOYER_MOORE_H__
#define __BOYER_MOORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_CHARS 256
#define MAX(A, B) ( ((A) > (B)) ?  A : B )

void makeBadCharArray(int *bcArray, const char *pattern, int patternLength);
void makeGoodSuffixArray(int *gsArray, const char *pattern, int patternLength);
void searchString(const char *string, const int *bcArray, const char *pattern, const int *gsArray);

#endif // #ifndef __BOYER_MOORE_H__
