#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "fractions.h"
#include "gauss.h"

// ���������, �������� ����� ������ ��� ������ � �����
// ������ ���� ������, ��� ���������� �������� � ����� ������ �����
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
	printf_s("��������� ������� ��� ������� ������\n");

	// ������ �������� �����
    fopen_s(&pFile, filename, "r");
	if (pFile == NULL) {
		printf_s("������ ������ ����� %s\n", filename);
		return -1;
	}
	printf_s("���� %s ������� ������\n", filename);

	sleMatrix = calloc(0, sizeof(fraction *));

	// ���������� ������ �����
	pResultStr = fgets(readStr, sizeof(readStr), pFile);
	while (pResultStr != NULL)
	{
		n = parseFractions(readStr, &tempRow); // ���������� ���� ����� ����� ����� ������ ��� ���������
		
		if (n == -1) {
			printf_s("������ ������ ������ � ������ %d\n", m+1);
			return;
		}
		if (n != previous_n && previous_n != -1)
		{
			printf_s("���������� ��������� � ������ %d ���������� �� �����������!\n", m+1);
			return;
		}

		// ����������� ��������� ������ ������ �� ���� ������
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
	
	// ���������, ����� �� ������ �� ����� �����
	if (feof(pFile) == 0)
	{
		printf_s("������ ������ �� �����!\n");
		return;
	}

	// ����� �� ������� �� �����
	printf_s("������� ����������� �������:\n\n");
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			printFraction(sleMatrix[i][j]);
			printf_s("\t");
		}
		printf_s("\n");
	}

	printf_s("\n=======================\n\n");
	tempRow = solveSle(sleMatrix, m, n, &solutionText);

	//����� ������� �� �����
	printf_s("������������� ����������� ����������� �������:\n\n");
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

	// ������� ������
	free(tempRow);
	free(solutionText);
	for (int i = 0; i < m; i++) {
		free(sleMatrix[i]);
	}
	free(sleMatrix);
	fclose(pFile);
	return 0;
}