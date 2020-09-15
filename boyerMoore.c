#include "boyerMoore.h"

void makeBadCharArray(int *bcArray, const char *pattern, int patternLength)
{
	if(bcArray == NULL || pattern == NULL)
	{
		printf("포인터 참조 실패. (bcArray:%p, pattern:%p)\n", bcArray, pattern);
		return;
	}

	if(patternLength <= 0)
	{
		printf("패턴의 길이가 0 보다 작거나 같음. (patternLength:%d)\n", patternLength);
	}

	// 총 256 개의 아스키 코드 문자에 대한 정보가 없으므로 전부 -1 로 설정한다.
	int bcArrayIndex = 0;
	for( ; bcArrayIndex < NUM_OF_CHARS; bcArrayIndex++)
	{
		bcArray[bcArrayIndex] = -1;
	}

	// 패턴에 있는 문자들의 위치를 배열의 문자에 등록한다.
	// bcArray['B'] = 1 -> 패턴의 인덱스 1 에 문자 'B' 가 위치해 있다.
	int patternIndex = 0;
	for( ; patternIndex < patternLength; patternIndex++)
	{
		bcArray[(int)(pattern[patternIndex])] = patternIndex;
	}
}

void makeGoodSuffixArray(int *gsArray, const char *pattern, int patternLength)
{
	if(gsArray == NULL || pattern == NULL)
	{
		printf("포인터 참조 실패. (bcArray:%p, pattern:%p)\n", gsArray, pattern);
		return;
	}

	if(patternLength <= 0)
	{
		printf("패턴의 길이가 0 보다 작거나 같음. (patternLength:%d)\n", patternLength);
	}

	// 이동할 거리를 저장할 배열이기 때문에 -1 을 저장하지 않고 패턴의 길이를 저장한다.
	int gsArrayIndex = 0;
	for( ; gsArrayIndex < patternLength; gsArrayIndex++)
	{
		gsArray[gsArrayIndex] = patternLength;
	}

	int suffixIndex = patternLength - 1;
	int partialSuffixIndex = 0;

	while(suffixIndex > 0)
	{
		// 부분문자열 검색 영역이 1 보다 크고, 비교하려는 위치에 일치하는 문자가 있는 경우
		if((partialSuffixIndex >= 0) && (pattern[suffixIndex + partialSuffixIndex] == pattern[partialSuffixIndex]))
		{
			// 부분 문자열 검색 영역을 1 감소시킨다. 
			partialSuffixIndex--;
		}
		// 일치하는 문자가 없거나 부분 문자열의 검색 영역이 없는 경우 (부분 문자열 검색 종료)
		// -> 해당 부분 문자열이 일치하지 않는 문자 앞에 있는 다른 문자열에 대칭되는지 확인한다.
		else
		{
			// 문자 일치 여부와 상관 없이 부분 문자열 검색이 끝난 경우
			// Case 2) prefix 와 suffix 의 일부가 일치하는 경우 - <a>
			// 불일치하는 문자가 발견되면 <a> 의 위치로 패턴을 이동시켜야 한다.
			if(partialSuffixIndex < 0)
			{
				for( ; (suffixIndex + partialSuffixIndex) >= 0; partialSuffixIndex--)
				{
					gsArray[suffixIndex + partialSuffixIndex] = suffixIndex;
				}
			}
			// 일치하는 문자가 없고 부분 문자열 검색이 아직 남아 있는 경우
			// 해당 부분 문자열 검색 영역인 suffix 문자열의 위치를 저장한다.
			// Case 1) 불일치하는 문자 이후의 suffix 와 일치하는 부분이 패턴 내에 존재하는 경우 - <b>
			// 불일치하는 문자가 발견되면 <b> 의 위치로 패턴을 이동시켜야 한다.
			else
			{
				gsArray[suffixIndex + partialSuffixIndex] = suffixIndex;
			}

			// 부분 문자열 검색 영역을 1 증가시킨다.
			partialSuffixIndex = patternLength - suffixIndex;
			// 문자 비교 위치를 왼쪽으로 1 만큼 이동한다.
			suffixIndex--;
		}
	}
}

void searchString(const char *string, const int *bcArray, const char *pattern, const int *gsArray)
{
	if(bcArray == NULL || pattern == NULL || bcArray == NULL || gsArray == NULL)
	{
		printf("포인터 참조 실패. (string:%p, bcArray:%p, pattern:%p, gsArray:%p)\n", string, bcArray, pattern, gsArray);
		return;
	}

	int stringLength = (int)strlen(string);
	int patternLength = (int)strlen(pattern);
	int shiftNumOfString = 0;
	int patternIndex = 0;

	while(shiftNumOfString <= (stringLength - patternLength))
	{
		patternIndex = patternLength - 1;

		// 패턴과 문자열 뒤에서부터 비교하면서 일치하지 않을 때까지 패턴 인덱스를 감소시킨다.
		while((patternIndex >=0) && (pattern[patternIndex] == string[shiftNumOfString + patternIndex]))
		{
			patternIndex--;
		}

		// 완전 일치
		if(patternIndex < 0)
		{
			printf("일치 : %d\n", shiftNumOfString);
			shiftNumOfString += gsArray[0];
		}
		// 일치하지 않으므로 bcArray 와 gsArray 의 값 중 큰 값만큼 비교 위치를 왼쪽에서 오른쪽으로  이동한다.
		else
		{
			shiftNumOfString += MAX(patternIndex - bcArray[shiftNumOfString + patternIndex], gsArray[patternIndex]);
		}
	}
}

