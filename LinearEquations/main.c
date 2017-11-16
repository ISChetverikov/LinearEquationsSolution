#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "fractions.h"
#include "gauss.h"

// Константа, задающая длину строки при чтении с файла
// Должна быть больше, чем количество символов в любой строке файла
#define READ_BUFFER_LENGHT 80

int main() {
	fraction ** sleMatrix = NULL;
	fraction * tempRow = NULL;

	FILE * pFile = NULL;
	char * filename = "in.txt";
	char readStr[READ_BUFFER_LENGHT];
	char * pResultStr;
	char * solutionText;

	int n = 0, m = 0, previous_n = -1;

	setlocale(LC_CTYPE, "Russian");
	printf_s("Программа решения СЛУ методом Гаусса\n");

	// Чтение входного файла
    fopen_s(&pFile, filename, "r");
	if (pFile == NULL) {
		printf_s("Ошибка чтения файла %s\n", filename);
		return -1;
	}
	printf_s("Файл %s успешно открыт\n", filename);

	sleMatrix = calloc(0, sizeof(fraction *));

	// Построчное чтение файла
	pResultStr = fgets(readStr, sizeof(readStr), pFile);
	while (pResultStr != NULL)
	{
		n = parseFractions(readStr, &tempRow); // Посмотреть если после числа стоит пробел или несколько
		
		if (n == -1) {
			printf_s("Ошибка чтения дробей в строке %d\n", m+1);
			return;
		}
		if (n != previous_n && previous_n != -1)
		{
			printf_s("Количество элементов в строке %d отличается от предыдущего!\n", m+1);
			return;
		}

		// Увеличиваем двумерный массив дробей на одну строку
		sleMatrix = realloc(sleMatrix, sizeof(fraction *) *(m + 1));
		sleMatrix[m] = calloc(n, sizeof(fraction));
		for (int i = 0; i < n; i++)
		{
			sleMatrix[m][i] = tempRow[i];
		}
		free(tempRow);

		m++;
		previous_n = n;
		pResultStr = fgets(readStr, sizeof(readStr), pFile);
	}
	
	// Проверяем, дошло ли чтение до конца файла
	if (feof(pFile) == 0)
	{
		printf_s("Ошибка чтения из файла!\n");
		return;
	}

	// Вывод на матрицы на экран
	printf_s("Входная расширенная матрица:\n\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printFraction(sleMatrix[i][j]);
			printf_s("\t");
		}
		printf_s("\n");
	}

	printf_s("\n=======================\n\n");
	tempRow = solveSle(sleMatrix, m, n, &solutionText);

	//Вывод матрицы на экран
	printf_s("Эквивалентная специальная ступенчатая матрица:\n\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printFraction(sleMatrix[i][j]);
			printf_s("\t");
		}
		printf_s("\n");
	}

	printf_s("\n=======================\n\n");

	printf_s("%s\n", solutionText);
	if (tempRow != NULL) {
		for (int i = 0; i < m; i++)
		{
			printFraction(tempRow[i]);
			printf_s("\t");
		}
		printf_s("\n");
	}
	printf_s("\n");

	// Очистка памяти
	free(tempRow);
	free(solutionText);
	for (int i = 0; i < m; i++) {
		free(sleMatrix[i]);
	}
	free(sleMatrix);
	fclose(pFile);
	return 0;
}