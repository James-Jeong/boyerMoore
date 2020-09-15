#include "boyerMoore.h"

int main()
{
	char string[] = "AABAACAADAABAAABAA";
	char pattern[] = "AABA";

	int patternLength = (int)strlen(pattern);
	int *bcArray = malloc(sizeof(int) * NUM_OF_CHARS);
	int *gsArray = malloc(sizeof(int) * (size_t)patternLength);

	makeBadCharArray(bcArray, pattern, patternLength);
	makeGoodSuffixArray(gsArray, pattern, patternLength);
	searchString(string, bcArray, pattern, gsArray);

	free(bcArray);
	free(gsArray);

	return 1;
}

