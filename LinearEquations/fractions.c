#include "fractions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Нам это не нужно
int create(int numerator, int denominator, fraction * f) {
	if (denominator == 0)
		return 0;

	f->numerator = numerator;
	f->denominator = denominator;
	
	return 1;
}

void printFraction(fraction operand) {
	if (operand.denominator == 1) {
		printf_s("%d", operand.numerator);
		return;
	}

	printf_s("%d/%d", operand.numerator, operand.denominator);
}

//fraction add(fraction left, fraction right) {
//
//}
//fraction sub(fraction left, fraction right);
//fraction mult(fraction left, fraction right);
//fraction div(fraction left, fraction right);
//fraction reverse(fraction operand);
//
//void reduce(fraction * operand);
//
//
int parseFraction(char * str, fraction ** pArr) {

	fraction tempArr[80];
	char * tokenOut, * lastOut;
	char * tokenIn, * lastIn;
	
	int count = 0;
	int num = 0, denom = 0;

	tokenOut = strtok_s(str, " ", &lastOut);

	while (tokenOut != NULL)
	{
		tokenIn = strtok_s(tokenOut, "/", &lastIn);
		if (tokenIn == NULL)
			continue;

		num = atoi(tokenIn);
		if (num == 0)
			continue;

		tokenIn = strtok_s(NULL, "/", &lastIn);
		if (tokenIn == NULL)
			denom = 1;
		else {
			denom = atoi(tokenIn);
			if (denom == 0)
				return -1;
		}
		
		tempArr[count].numerator = num;
		tempArr[count].denominator = denom;
		++count;

		tokenOut = strtok_s(NULL, " ", &lastOut);
	}

	*pArr = calloc(count, sizeof(fraction));
	memcpy(*pArr, tempArr, sizeof(fraction)*count);

	return count;
}
