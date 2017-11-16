#include "fractions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define TEXT_LENGTH 80

fraction * solveSle(fraction ** matrix, int m, int n, char ** outputText) {

	fraction ** tempMatrix;
	fraction * tempRow;
	fraction * result = NULL;

	fraction bomb;
	fraction reverseBomb;

	int current_rank = 0;
	fraction deleted = {0,1};

	char isRowNull = 0;

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
		bomb = createFraction(0,1);

		int index = 0;
		for (index = current_rank; index < m; index++) {
			if (!isZero(tempMatrix[index][j])){
				bomb = tempMatrix[index][j];
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
	
	*outputText = calloc(TEXT_LENGTH, sizeof(char));
	sprintf_s(*outputText, TEXT_LENGTH, "Система неопределена. Ранг системы: %d", current_rank);

	// Если ранг матрицы равен количеству переменных, то в результат помешаем единственное решение
	if (current_rank == n - 1) {
		strcpy_s(*outputText, TEXT_LENGTH,"Система имеет единственое решение.");
		result = calloc(n - 1, sizeof(fraction));
		for (int i = 0; i < m; i++)
		{
			result[i] = tempMatrix[i][n - 1];
		}
	}
	else {
		for (int i = m - 1; i >= 0; i--)
		{
			isRowNull = 1;
			for (int j = 0; j < n - 1; j++)
			{
				if (!isZero(tempMatrix[i][j])) {
					isRowNull = 0;
					break;
				}
			}
			if (!isRowNull) 
				break;

			if (!isZero(tempMatrix[i][n - 1])) { 
				strcpy_s(*outputText, TEXT_LENGTH, "Система несовместна.");
				break;
			}				
		}
	}

	 //Вывод матрицы на экран
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printFraction(tempMatrix[i][j]);
			printf_s(" ");
		}
		printf_s("\n");
	}
	printf_s("--------------\n");

	// Очистка массива
	for (int i = 0; i < m; i++)
	{
		free(tempMatrix[i]);
	}
	free(tempMatrix);

	return result;
}