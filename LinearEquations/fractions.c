#include "fractions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printFraction(fraction operand) {
	if (operand.denominator == 1) {
		printf_s("%d", operand.numerator);
		return;
	}

	if (operand.denominator < 0) {
		operand.numerator = -operand.numerator;
		operand.denominator = -operand.denominator;
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
		if (tokenIn == NULL) {
			tokenOut = strtok_s(NULL, " ", &lastOut);
			continue;
		}
		num = atoi(tokenIn);

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
	reduce(&f);

	return f;
}

fraction substraction(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.denominator -
		right.numerator * left.denominator;
	f.denominator = left.denominator * right.denominator;
	reduce(&f);

	return f;
}

fraction multiplication(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.numerator;
	f.denominator = left.denominator * right.denominator;
	reduce(&f);

	return f;
}

fraction division(fraction left, fraction right) {
	fraction f;
	f.numerator = left.numerator * right.denominator;
	f.denominator = left.denominator * right.numerator;
	reduce(&f);

	return f;
}

fraction reverse(fraction operand) {
	fraction f;
	f.numerator = operand.denominator;
	f.denominator = operand.numerator;

	return f;
}

// Нахождение наибольшего общего делителя
int getGcd(int a, int b) {
	return b == 0 ? a : getGcd(b, a % b); 
}

void reduce(fraction * operand) {
	int gcd = 0;

	if (operand->numerator == 0) {
		operand->denominator = 1;
		return;
	}

	gcd = getGcd(operand->numerator, operand->denominator);
	operand->numerator /= gcd;
	operand->denominator /= gcd;
	
	return;
}

char isZero(fraction operand) {
	if (operand.numerator == 0)
		return 1;
	return 0;
}

