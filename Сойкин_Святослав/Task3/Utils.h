#pragma once
#include "Palette.h"

// Утилиты и вспомогательные функции

// Ширина для отрисовки элементов интерфейса
const int W = 84;

// Константа скорости (прим., оставлена для совместимости)
// Источник: https://www.asutpp.ru/skorost-sveta.html
const double C = 1'080'000'000;


// Инициализация приложения (заголовок консоли)
void init(const wstring &title = L"Консольное приложение");

// Получение кода клавиши (с подсказкой)
int getKey(const string &message = "\t    Нажмите любую клавишу для продолжения...");

// Случайные значения
int    getRand(int    low, int    high);
double getRand(double low, double high);
float  getRand(float  low, float  high);
char   getRand(char   low, char   high);

// Управление цветом текста
void setColor(short color);

// Ввод целого числа с проверкой
int getInt();

// Вывод в навигационную строку
void showNavBarMessage(short hintColor, const string &message);
void showNavBarMessage(short hintColor, short acctColor, const string &message);

// Экран "В разработке"
void showUnderConstruction(short width, short mainColor, short infoColor);

// Показать сообщение в основной области
void showMessage(const string &msg, short msgColor, short mainColor);

// Отрисовать поле ввода
void showInputLine(const string &prompt = "Введите число:", short n = 19, short color = infoColor);

// Проверка формата ввода
void checkInputFormat(istream& is);

// ---------------------------------------------------------------------------------
#pragma region WinAPI_helpers
// Работа с WinAPI и консолью

COORD getConsoleSize();

void showCursor(bool mode);
bool isCursor();

void gotoXY(short x, short y);
void getXY(COORD* position);


void cls();
#include <Windows.h>

// Печать UTF-8 строки в CP1251-консоль
void printCp1251(const string& utf8);
#pragma endregion


#pragma region stream_manipulators
// Потоковые манипуляторы и классы-утилиты

// Очистка экрана: cout << cls;
ostream& cls(ostream& os);
// cin >> cls;
istream& cls(istream& is);

// Табуляция: cout << tab;
ostream& tab(ostream& os);

// Включить курсор: cout << cursor
ostream& cursor(ostream& os);
istream& cursor(istream& is);

// Отключить курсор: cout << nocursor
ostream& nocursor(ostream& os);
istream& nocursor(istream& is);

// Печать нескольких переводов строки: cout << endlm(n)
class endlm
{
	int n_;

public:
	endlm(int n) : n_(n) {}

	friend ostream& operator<<(ostream& os, const endlm& obj);
};

// Класс-манипулятор цвета
class color
{
	short color_;

public:
	color(short color) : color_(color) {}

	friend ostream& operator<<(ostream& os, const color& obj);
	friend istream& operator>>(istream& is, const color& obj);
};

// Класс-позиция курсора
class pos
{
	short x_;
	short y_;

public:
	pos(short x, short y) : x_(x), y_(y) {}

	friend ostream& operator<<(ostream& os, const pos& obj);
	friend istream& operator>>(istream& is, const pos& obj);
};

#pragma endregion


// Сравнение с погрешностью
inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }
inline bool eq(float d1, float d2) { return abs(d1 - d2) <= 1e-6; }

int getCurrentYear();
