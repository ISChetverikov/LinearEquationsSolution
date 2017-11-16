#pragma once

//  онстанта задающа€ максимальное количесвто дробей в временом массиве при
// поиске дробей в строке (исп в методе parseFractions)
#define FRACTIONS_ARRAY_MAX_LENGTH 80 

// —труктура, задающа€ рациональную дробь
typedef struct rational_fraction {
	int numerator;
	int denominator;
} fraction;

// ¬ывод дроби на экран консоли
// params:
//     operand - выводима€ дробь
void printFraction(fraction operand);

// Ќахождение в строке всех дробей, разделенных пробелом
// params:
//     str - строка с дроб€ми
//     arr - (out) указатель на массив найденных дробей, внутри происходит выделение пам€ти под него!
// return: в случае неудачи -1, в противном случае количество найденных в строке дробей
int parseFractions(char * str, fraction ** arr);

// —ложение дробей
// params:
//     left  - левый операнд
//     right - правый операнд
// return: значение суммы дробей
fraction addition(fraction left, fraction right);

// ¬ычитание дробей
// params:
//     left  - левый операнд
//     right - правый операнд
// return: значение разности дробей
fraction substraction(fraction left, fraction right);

// ”множение дробей
// params:
//     left  - левый операнд
//     right - правый операнд
// return: значение призведени€ дробей
fraction multiplication(fraction left, fraction right);

// ƒеление дробей (проверка на ноль правого операнда не выполн€етс€)
// params:
//     left  - левый операнд
//     right - правый операнд
// return: значение делени€ дробей
fraction division(fraction left, fraction right);

// Ќахождение обратной дроби (проверка на ноль внутри не выполн€етс€)
// params:
//     operand - дробь
// return: значение обратной дроби
fraction reverse(fraction operand);

// —окращение дроби
// params:
//     operand - указатель на сокращаемую дробь
void reduce(fraction * operand);

// —равнение на равенство дроби нулю
// params:
//     operand - сравниваема€ дробь
// return: 1 - дробь равна нулю, 0 - в противном случае
char isZero(fraction operand);

int getGcd(int, int);