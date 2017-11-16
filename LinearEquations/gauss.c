#include "fractions.h"
#include <string.h>
#include <stdlib.h>

fraction * solveSle(fraction ** matrix, int m, int n) {

	fraction ** tempMatrix;
	fraction * tempRow;

	fraction bomb;
	fraction reverseBomb;

	int current_rank = 0;
	fraction deleted = {0,0};

	// Копирование массива
	tempMatrix = calloc(m, sizeof(fraction *));
	for (int i = 0; i < n; i++)
	{
		tempMatrix[i] = calloc(n, sizeof(fraction));
		memcpy(tempMatrix[i], matrix[i], n * sizeof(fraction));
	}

	// Создать конструкторы для дробей
	for (int j = 0; j < n; j++)
	{
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				printFraction(matrix[i][j]);
				printf_s(" ");
			}
			printf_s("\n");
		}
		printf_s("--------------\n");

		bomb.numerator = 0;
		bomb.denominator = 1;

		int index = 0;
		for (index = j; index < m; index++) {
			if (!isZero(tempMatrix[index][j])){
				bomb.numerator = tempMatrix[index][j].numerator;
				bomb.denominator = tempMatrix[index][j].denominator;
			    break;
		    }
		}
		if (isZero(bomb))
			continue;

		// Поднятие строки вверх
		tempRow = tempMatrix[index];
		tempMatrix[index] = tempMatrix[current_rank];
		tempMatrix[current_rank] = tempRow;
		
		reverseBomb = reverse(bomb);
		// Умножение строки на обратный элемент
		for (int k = j; k < n; k++) {
			tempMatrix[current_rank][k] = multiplication(tempMatrix[current_rank][k], reverseBomb);
		}

		for (int i = 0; i < m; i++) {
			if (i == current_rank)
				continue;

			deleted = tempMatrix[i][j];
			for (int k = j; k < n; k++) {
				
				tempMatrix[i][k] =
					substraction(tempMatrix[i][k], multiplication(tempMatrix[current_rank][k], deleted));
			}
		}
		current_rank++;
	}
}