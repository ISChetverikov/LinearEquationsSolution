#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "fractions.h"

int addMatrixRow(fraction ** Matrix, int m, int n, fraction * row) {
	
	

	
	return 0;
}

int main() {
	fraction ** sleMatrix = NULL;
	fraction * matrixRow = NULL;
	FILE * pFile = NULL;
	char * filename = "in.txt";
	char readStr[80];
	char * pResultStr;
	int n = 0, m = 0, previous_n = -1;

	setlocale(LC_CTYPE, "Russian");
	printf_s("Программа решения СЛУ\n");

    fopen_s(&pFile, filename, "r");
	if (pFile == NULL) {
		printf_s("Ошибка чтения файла %s\n", filename);
		return -1;
	}
	printf_s("Файл %s успешно открыт\n", filename);

	sleMatrix = calloc(0, sizeof(fraction *));
	pResultStr = fgets(readStr, sizeof(readStr), pFile);
	while (pResultStr != NULL)
	{
		n = parseFraction(readStr, &matrixRow);
		
		if (n != previous_n && previous_n != -1)
		{
			printf_s("Количество элементов в строках различается!\n");
			return;
		}

	    
		sleMatrix = realloc(sleMatrix, sizeof(fraction *) *(m + 1));
		sleMatrix[m] = calloc(n, sizeof(fraction));
		for (int i = 0; i < n; i++)
		{
			sleMatrix[m][i] = matrixRow[i];
		}
		free(matrixRow);

		m++;
		previous_n = n;
		pResultStr = fgets(readStr, sizeof(readStr), pFile);
	} ;
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printFraction(sleMatrix[i][j]);
			printf_s(" ");
		}
		printf_s("\n");
	}

	fraction f = divFraction(sleMatrix[0][1], sleMatrix[0][1]);
	reduce(&f);
	printFraction(f);

	// Проверяем, дошло ли чтение до конца файла
	if (feof(pFile) == 0) 
	{
		printf_s("Ошибка чтения из файла!\n");
		return;
	}

	printf_s("\n");

	for (int i = 0; i < m; i++) {
		free(sleMatrix[i]);
	}
	free(sleMatrix);
	fclose(pFile);
	return 0;
}