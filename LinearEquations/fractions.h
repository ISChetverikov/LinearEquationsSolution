#pragma once

// ��������� �������� ������������ ���������� ������ � �������� ������� ���
// ������ ������ � ������ (��� � ������ parseFractions)
#define FRACTIONS_ARRAY_MAX_LENGTH 80 

// ���������, �������� ������������ �����
typedef struct rational_fraction {
	int numerator;
	int denominator;
} fraction;

// ����� ����� �� ����� �������
// params:
//     operand - ��������� �����
void printFraction(fraction operand);

// ���������� � ������ ���� ������, ����������� ��������
// params:
//     str - ������ � �������
//     arr - (out) ��������� �� ������ ��������� ������, ������ ���������� ��������� ������ ��� ����!
// return: � ������ ������� -1, � ��������� ������ ���������� ��������� � ������ ������
int parseFractions(char * str, fraction ** arr);

// �������� ������
// params:
//     left  - ����� �������
//     right - ������ �������
// return: �������� ����� ������
fraction addition(fraction left, fraction right);

// ��������� ������
// params:
//     left  - ����� �������
//     right - ������ �������
// return: �������� �������� ������
fraction substraction(fraction left, fraction right);

// ��������� ������
// params:
//     left  - ����� �������
//     right - ������ �������
// return: �������� ����������� ������
fraction multiplication(fraction left, fraction right);

// ������� ������ (�������� �� ���� ������� �������� �� �����������)
// params:
//     left  - ����� �������
//     right - ������ �������
// return: �������� ������� ������
fraction division(fraction left, fraction right);

// ���������� �������� ����� (�������� �� ���� ������ �� �����������)
// params:
//     operand - �����
// return: �������� �������� �����
fraction reverse(fraction operand);

// ���������� �����
// params:
//     operand - ��������� �� ����������� �����
void reduce(fraction * operand);

// ��������� �� ��������� ����� ����
// params:
//     operand - ������������ �����
// return: 1 - ����� ����� ����, 0 - � ��������� ������
char isZero(fraction operand);

int getGcd(int, int);