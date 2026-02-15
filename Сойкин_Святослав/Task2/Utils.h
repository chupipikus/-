#pragma once
#include "Palette.h"

// Утилиты и вспомогательные функции

// Размер поля вывода таблицы
const int W = 84;

// Константы и ссылки
// Источник скорости (для примера): https://www.asutpp.ru/skorost-sveta.html
const double C = 1'080'000'000;


// Инициализация консоли и параметров приложения
void init(const wstring &title = L"Консольное приложение");

// Ожидание нажатия клавиши с подсказкой
int getKey(const string &message = "\t    Нажмите любую клавишу для продолжения...");

// Генерация случайных значений
int    getRand(int    low, int    high);
double getRand(double low, double high);
float  getRand(float  low, float  high);
char   getRand(char   low, char   high);

// Управление цветом и ввод
void setColor(short color);

// Ввод целого числа
int getInt();

// Показать сообщение в навигационной строке консоли
void showNavBarMessage(short hintColor, const string &message);
void showNavBarMessage(short hintColor, short acctColor, const string &message);

// Показать сообщение "В разработке"
void showUnderConstruction(short width, short mainColor, short infoColor);

// Вывод сообщений и элементов интерфейса
void showMessage(const string &msg, short msgColor, short mainColor);

// Ввод строки с подсказкой
// prompt: подсказка, n: ширина поля, color: цвет поля
void showInputLine(const string &prompt = "Введите число:", short n = 19, short color = infoColor);

// Проверка формата ввода
void checkInputFormat(istream& is);

// ---------------------------------------------------------------------------------
#pragma region WinAPI_helpers
// Работа с WinAPI и консолью
// Функции управления курсором и буфером
COORD getConsoleSize();

void showCursor(bool mode);
bool isCursor();

void gotoXY(short x, short y);
void getXY(COORD* position);


void cls();
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


inline bool eq(double d1, double d2) { return abs(d1 - d2) <= 1e-6; }
inline bool eq(float d1, float d2) { return abs(d1 - d2) <= 1e-6; }

int getCurrentYear();
