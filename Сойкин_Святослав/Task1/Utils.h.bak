#pragma once
#include "Palette.h"

// набор полезных функций

// ширина "панелей" вывода сообщений приложения
const int W = 84;

// Константа для задания на 12.01.2026 
// Скорость света в вакууме, км/ч
// Источник: https://www.asutpp.ru/skorost-sveta.html 
const double C = 1'080'000'000;


// процедура подготовки консоли к работе приложения
void init(const wstring &title = L"Заголовок приложения");

// получение кода нажатой клавиши
int getKey(const string &message = "\t    Нажмите любую клавишу для продолжения...");

// генерация случайного числа
int    getRand(int    low, int    high);
double getRand(double low, double high);
float  getRand(float  low, float  high);
char   getRand(char   low, char   high);

// задание цвета консоли
void setColor(short color);

// ввод целого числа
int getInt();

// Функция для вывода верхней строки окна при решении задачи
void showNavBarMessage(short hintColor, const string &message);
void showNavBarMessage(short hintColor, short acctColor, const string &message);

// вывод сообщения "В разработке" 
void showUnderConstruction(short width, short mainColor, short infoColor);

// вывод произвольного текстового сообщения
void showMessage(const string &msg, short msgColor, short mainColor);

// вывод приглашения ко вводу, представления строки ввода, цвет переключается
// в заданный color
void showInputLine(const string &prompt = "Введите число:", short n = 19, short color = infoColor);

// проверка формата ввода
void checkInputFormat(istream& is);

// ---------------------------------------------------------------------------------
#pragma region применение структур в WinAPI
// получение размера экрана консоли
COORD getConsoleSize();

void showCursor(bool mode);
bool isCursor();

void gotoXY(short x, short y);
void getXY(COORD* position);


void cls();
#pragma endregion


#pragma region реализация манипуляторов вывода
// имитация манипулятора вывода без параметра

// "манипулятор" вывода без параметров для очистки экрана
// cout << cls;
ostream& cls(ostream& os);
// cin >> cls;
istream& cls(istream& os);

// "манипулятор" вывода без параметров для вывода символа табуляции
// cout << tab;
ostream& tab(ostream& os);

// "манипулятор" вывода для включения текстового курсора
ostream& cursor(ostream& os);
istream& cursor(istream& is);

// "манипулятор" вывода для выключения текстового курсора
ostream& nocursor(ostream& os);
istream& nocursor(istream& is);

// "манипулятор" вывода с параметрами для вывода
// для вывода заданного количества символа перевода строки
// этот класс нужен только для хранения параметра манипулятора
class endlm
{
	// параметр манипулятора
	int n_;

public:
	endlm(int n) : n_(n) {}

	// очень важно -- константная ссылка на объект
	friend ostream& operator<<(ostream& os, const endlm& obj);
};

// задание цвета символов и цвета фона
class color
{
	// параметр манипулятора
	short color_;

public:
	color(short color) : color_(color) {}

	// очень важно -- константная ссылка на объект
	friend ostream& operator<<(ostream& os, const color& obj);
	friend istream& operator>>(istream& is, const color& obj);
};

// задание позиции курсора
class pos
{
	// параметр манипулятора
	short x_;
	short y_;

public:
	pos(short x, short y) : x_(x), y_(y) {}

	// очень важно -- константная ссылка на объект
	friend ostream& operator<<(ostream& os, const pos& obj);
	friend istream& operator>>(istream& is, const pos& obj);
};

#pragma endregion



// проверка на равенство для вещественнных типов
inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }
inline bool eq(float d1, float d2) { return abs(d1 - d2) <= 1e-6; }

int getCurrentYear();
