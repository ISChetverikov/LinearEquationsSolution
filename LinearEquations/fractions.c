#include "fractions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFraction(fraction operand) {
	if (operand.denominator == 1) {
		printf_s("%d", operand.numerator);
		return;
	}

	printf_s("%d/%d", operand.numerator, operand.denominator);
	return;
}

// Сначала разбиваем строку пробелом, затем каждый кусок разбиваем "/"
// и пытаемся найти числитель и знаменатель
int parseFractions(char * str, fraction ** pArr) {
	fraction tempArr[FRACTIONS_ARRAY_MAX_LENGTH];

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
			if (denom == 0) // Знаменатель не обнаружен или равен нулю
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

fraction addition(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.denominator +
		right.numerator * left.denominator;
	f.denominator = left.denominator * right.denominator;

	return f;
}

fraction substraction(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.denominator -
		right.numerator * left.denominator;
	f.denominator = left.denominator * right.denominator;

	return f;
}

fraction multiplication(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.numerator;
	f.denominator = left.denominator * right.denominator;

	return f;
}

fraction division(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.denominator;
	f.denominator = left.denominator * right.numerator;

	return f;
}

fraction reverse(fraction operand) {
	fraction f;
	f.numerator = operand.denominator;
	f.denominator = operand.numerator;

	return f;
}

// Нахождение наибольшего общего делителя
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b); 
}

void reduce(fraction * operand) {
	int gcd = 0;

	if (operand->numerator == 0) {
		operand->denominator = 1;
		return;
	}

	gcd = (operand->numerator, operand->denominator);
	operand->numerator /= gcd;
	operand->denominator /= gcd;
	
	return;
}

char isZero(fraction operand) {
	if (operand.numerator == 0)
		return 1;
	return 0;
}

