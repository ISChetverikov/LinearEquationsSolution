#include "fractions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEXT_LENGTH 80

fraction * solveSle(fraction ** matrix, int m, int n, char ** outputText) {

	fraction * tempRow;
	fraction * result = NULL;

	fraction bomb;
	fraction reverseBomb;

	int current_rank = 0;
	fraction deleted = {0,1};

	char isRowNull = 0;

	for (int j = 0; j < n - 1; j++)
	{
		bomb = createFraction(0,1);

		int index = 0;
		for (index = current_rank; index < m; index++) {
			if (!isZero(matrix[index][j])){
				bomb = matrix[index][j];
			    break;
		    }
		}
		if (isZero(bomb))
			continue;

		// Поднятие строки вверх
		tempRow = matrix[index];
		matrix[index] = matrix[current_rank];
		matrix[current_rank] = tempRow;
		
		reverseBomb = reverse(bomb);
		
		// Умножение строки на обратный элемент
		for (int k = j; k < n; k++) {
			matrix[current_rank][k] = multiplication(matrix[current_rank][k], reverseBomb);
		}

		for (int i = 0; i < m; i++) {
			if (i == current_rank)
				continue;

			deleted = matrix[i][j];
			for (int k = j; k < n; k++) {
				
				matrix[i][k] =
					substraction(matrix[i][k], multiplication(matrix[current_rank][k], deleted));
			}
		}
		current_rank++;
	}
	
	*outputText = calloc(TEXT_LENGTH, sizeof(char));
	sprintf_s(*outputText, TEXT_LENGTH,
		"Система неопределена. Ранг основной матрицы системы: %d", current_rank);

	// Если ранг матрицы равен количеству переменных, то в результат помешаем единственное решение
	if (current_rank == n - 1) {
		strcpy_s(*outputText, TEXT_LENGTH,"Система имеет единственое решение.");
		result = calloc(n - 1, sizeof(fraction));
		for (int i = 0; i < m; i++)
		{
			result[i] = matrix[i][n - 1];
		}
	}
	else {
		for (int i = m - 1; i >= 0; i--)
		{
			isRowNull = 1;
			for (int j = 0; j < n - 1; j++)
			{
				if (!isZero(matrix[i][j])) {
					isRowNull = 0;
					break;
				}
			}
			if (!isRowNull) 
				break;

			if (!isZero(matrix[i][n - 1])) { 
				strcpy_s(*outputText, TEXT_LENGTH, "Система несовместна.");
				break;
			}				
		}
	}

	return result;
}