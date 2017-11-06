#pragma once

typedef struct rational_fraction {
	int numerator;
	int denominator;
} fraction;

void printFraction(fraction operand);
int parseFraction(char * str, fraction ** arr);
//fraction add(fraction left, fraction right);
//fraction sub(fraction left, fraction right);
//fraction mult(fraction left, fraction right);
//fraction div(fraction left, fraction right);
//fraction reverse(fraction operand);
//
//void reduce(fraction * operand);
//
