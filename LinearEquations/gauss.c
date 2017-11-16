#include "fractions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

fraction * solveSle(fraction ** matrix, int m, int n) {
	char * solutionText = "";

	fraction ** tempMatrix;
	fraction * tempRow;

	fraction bomb;
	fraction reverseBomb;

	int current_rank = 0;
	fraction deleted = {0,1};

	char flag = 0;

	// Копирование массива
	tempMatrix = calloc(m, sizeof(fraction *));
	for (int i = 0; i < m; i++)
	{
		tempMatrix[i] = calloc(n, sizeof(fraction));
		memcpy(tempMatrix[i], matrix[i], n * sizeof(fraction));
	}

	// Создать конструкторы для дробей
	for (int j = 0; j < n; j++)
	{
		bomb.numerator = 0;
		bomb.denominator = 1;

		int index = 0;
		for (index = current_rank; index < m; index++) {
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

		/*for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				printFraction(tempMatrix[i][j]);
				printf_s(" ");
			}
			printf_s("\n");
		}
		printf_s("--------------\n");*/

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
	
	if (current_rank == n - 1) {
		solutionText = "Система имеет единственое решение.";
	}
	else {
		for (int i = m; i >= 0; i--)
		{
			flag = 0;
			for (int j = 0; j < n - 1; j++)
			{
				if (!isZero(tempMatrix[i][j]))
					break;
				flag = 1;
			}
			if (flag == 0) break;

			if (!isZero(tempMatrix[i][n - 1]))
				solutionText = "Системе несовместна.";
			else
				solutionText = "Система неопределена.";
		}
	}


	// Очистка массива
	for (int i = 0; i < m; i++)
	{
		free(tempMatrix[i]);
	}
	free(tempMatrix);
}