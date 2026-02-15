// набор полезных функций
#include "pch.h"
#include "Utils.h"
#include "Colors.h"
#include "Palette.h"

// статическая переменная - локально-глобальная переменная
// глобальная переменная, доступная только в текущем файле
// исходного кода - инкапсуляция переменной
// время жизни переменной == время жизни (работы) программы
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void init(const wstring& title) {
	SetConsoleTitleW(title.c_str());
	SetConsoleOutputCP(CODE_PAGE);
	SetConsoleCP(CODE_PAGE);
	srand(GetTickCount());
	cout << fixed << setprecision(2) << boolalpha;

	setColor(mainColor);
	cls();
}


// получение кода нажатой клавиши
int getKey(const string& message) {
	cout << message;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	return key;
} // getKey


// генерация случайного числа типа int в диапазоне [low, high]
int getRand(int low, int high) {
	return low + rand() % (high - low + 1);
} // getRand


// генерация случайного числа типа double в диапазоне [low, high]
double getRand(double low, double high) {
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// генерация случайного числа типа flost в диапазоне [low, high]
float getRand(float low, float high) {
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// генерация случайного символа в диапазоне [low, high]
char getRand(char low, char high) {
	return (char)getRand((int)low, (int)high);
} // getRand


// задание цвета консоли
// использование статической переменной h
void setColor(short color) {
	SetConsoleTextAttribute(h, color);
} // setColor


// ввод целого числа
int getInt() {
	int value;
	while (true) {
		// собственно ввод
		cout << "? ";
		cin >> value;

		// Если ввели число, выход из цикла и из функции
		if (!cin.fail()) break;

		// Если это не число - сброс состояния ошибки,
		// очистка буфера ввода
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	} // while

	return value;
} // getInt


// проверка формата ввода
void checkInputFormat(istream& is) {
	// проверка формата ввода
	if (is.fail()) {
		// сброс признака ошибки и очистка буфера ввода
		is.clear();
		is.ignore(is.rdbuf()->in_avail(), '\n');

		// выброс исключения
		throw exception("Введено не число");
	} // if	
} // checkInputFormat


// вывод верхней строки окна - строки навигации при исполнении задач
void showNavBarMessage(short hintColor, const string& message) {
	setColor(hintColor);

	gotoXY(0, 0);

	// определить в коде ширину консоли (WinAPI)
	const COORD conSize = getConsoleSize();
	cout << setw(conSize.X) << left << message << right;
	setColor(mainColor);

	gotoXY(0, 4);
} // showNavBarMessage


// вывод верхней строки окна - строки навигации при исполнении задач,
// Последоыательности, выделенные символами ~~ выводим цветом acctColor
void showNavBarMessage(short hintColor, short acctColor, const string& message) {
	setColor(hintColor);
	gotoXY(0, 0);

	// определить в коде ширину консоли (WinAPI)
	const COORD conSize = getConsoleSize();

	// цикл вывода строки с управлением цветом
	bool acctFlag = false;
	int len = 0;
	for (int i = 0; message[i] != 0; i++) {
		if (message[i] == '~') {
			setColor(!acctFlag ? acctColor : hintColor);
			acctFlag = !acctFlag;
			continue;
		} // if

		cout << message[i];
		++len;
	} // for i 

	// Вывести "хвост" сроки
	cout << setw(conSize.X - len - 1) << " ";
	setColor(mainColor);

	gotoXY(0, 4);
} // showNavBarMessage


// Вывод сообщения "Функция в разработке"
void showUnderConstruction(short width, short mainColor, short infoColor) {
	ostringstream oss;
	oss << "\n\n\n\n" << left
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    [Информация]" << "\n"
		<< "\t" << setw(width) << "    Функция в разработке" << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    Нажмите любую клавишу для продолжения..." << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << " " << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << right;
	showMessage(oss.str(), infoColor, mainColor);
} // showUnderConstruction


// вывод сообщения
void showMessage(const string& msg, short msgColor, short mainColor) {
	setColor(msgColor);
	cout << left << msg << right;
	setColor(mainColor);
} // showMessage


// вывод приглашения ко вводу, представления строки ввода, цвет переключается
// в заданный color
void showInputLine(const string& prompt, short n, short color) {
	// вывести подсказку ввода
	cout << prompt;

	COORD pos;
	getXY(&pos);

	// включить цвет и вывести "строку ввода"
	setColor(color);
	cout << setw(n) << "  ";

	// переместить курсор в начало "строки ввода"
	gotoXY(pos.X + 1, pos.Y);
} // showInputLine


// ---------------------------------------------------------------------------------
#pragma region WinAPI_helpers
// включение или выключение курсора консоли
// mode: true  - включить курсор
//       false - выключить курсор
void showCursor(bool mode) {
	// структура winAPI
	CONSOLE_CURSOR_INFO info;

	// получение данных в эту структуру, используется еще
	// одна перегрузка операции & - на этот раз это получение
	// адреса переменной

	// h - хэндл консоли
	// info - указатель на структуру
	GetConsoleCursorInfo(h, &info);

	info.bVisible = mode;
	SetConsoleCursorInfo(h, &info);
} // void showCursor


// возвращает значение видимости курсора - true: видимый или false: не видимый
bool isCursor() {
	CONSOLE_CURSOR_INFO info;

	// h - хэндл консоли
	// info - указатель на структуру
	GetConsoleCursorInfo(h, &info);

	return info.bVisible;
} // isCursorVisible


// позиционирование курсора в заданную позицию консоли
void gotoXY(short x, short y) {
	SetConsoleCursorPosition(h, COORD{ x, y });
} // gotoXY


// получить текущую позицию курсора
void getXY(COORD* position) {
	CONSOLE_SCREEN_BUFFER_INFO cbuf;
	GetConsoleScreenBufferInfo(h, &cbuf);

	position->X = cbuf.dwCursorPosition.X;
	position->Y = cbuf.dwCursorPosition.Y;
} // getXY

// TODO: получить цвет в текущей позиции курсора


// очистка экрана консоли
void cls() {
	COORD coordScreen = { 0, 0 }; // исходная позиция для курсора
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	// Получим число символьных ячеек в текущем буфере.

	if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

	// размер окна консоли в символах
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Заполним полностью экран пробелами - это и есть очистка
	// cCharsWritten - счетчик записанных символов
	if (!FillConsoleOutputCharacter(h, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	// Установим соответствующие атрибуты буфера из текущих атрибутов.
	if (!FillConsoleOutputAttribute(h, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Поместим курсор в начальную позицию после очистки экрана - верхний левый угол
	SetConsoleCursorPosition(h, coordScreen);
} // cls


// получение размера экрана консоли
COORD getConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	return csbi.dwSize;
} // getConsoleSize
#pragma endregion


#pragma region stream_manipulators
// "манипулятор" вывода без параметров для очистки экрана
// cout << cls;
ostream& cls(ostream& os) {
	cls();
	return os;
} // cls


// "манипулятор" ввода без параметров для очистки экрана
// cin >> cls;
istream& cls(istream& is) {
	cls();
	return is;
} // cls


// "манипулятор" вывода без параметров для вывода символа табуляции
// cout << tab;
ostream& tab(ostream& os) {
	os << "\t";
	return os;
} // tab


// "манипулятор" вывода для включения текстового курсора
ostream& cursor(ostream& os) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// возврат потока вывода - только для возможности встраивания
	// в цепочку операций вывода
	return os;
} // cursor


// "манипулятор" ввода для включения текстового курсора
istream& cursor(istream& is) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	// возврат потока ввода - только для возможности встраивания
	// в цепочку операций ввода
	return is;
} // cursor


// "манипулятор" вывода для выключения текстового курсора
ostream& nocursor(ostream& os) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// возврат потока вывода - только для возможности встраивания
	// в цепочку операций вывода
	return os;
} // nocursor


// "манипулятор" ввода для выключения текстового курсора
istream& nocursor(istream& is) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	// возврат потока ввода - только для возможности встраивания
	// в цепочку операций ввода
	return is;
} // nocursor


// "манипулятор" вывода с параметром для вывода
// заданного количества символов перевода строки
ostream& operator<<(ostream& os, const endlm& obj) {
	for (int i = 0; i < obj.n_; ++i) {
		os << "\n";
	}
	return os;
} // operator<<


// "манипулятор" вывода с параметром для установки цвета символа 
// и цвета фона
ostream& operator<<(ostream& os, const color& obj) {
	SetConsoleTextAttribute(h, obj.color_);
	return os;
} // operator<<


// "манипулятор" ввода с параметром для установки цвета символа 
// и цвета фона
istream& operator>>(istream& is, const color& obj) {
	SetConsoleTextAttribute(h, obj.color_);
	return is;
} // operator>>


// "манипулятор" вывода с параметром для установки позиции курсора в консоли 
ostream& operator<<(ostream& os, const pos& obj) {
	SetConsoleCursorPosition(h, { obj.x_, obj.y_ });
	return os;
} // operator<<

// "манипулятор" ввода с параметром для установки позиции курсора в консоли 
istream& operator>>(istream& is, const pos& obj) {
	SetConsoleCursorPosition(h, { obj.x_, obj.y_ });
	return is;
} // operator>>
#pragma endregion


// получить текущий год
int getCurrentYear() {
	time_t t = time(nullptr);
	struct tm tm = *localtime(&t);
	return (tm.tm_year + 1900);
} // getCurrentYear
