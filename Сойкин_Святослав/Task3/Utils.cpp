// Утилиты и вспомогательные функции
#include "pch.h"
#include "Utils.h"
#include "Colors.h"
#include "Palette.h"

// Внутренний дескриптор консоли
static HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void init(const wstring &title) {
	SetConsoleTitle(title.c_str());
	SetConsoleOutputCP(CODE_PAGE);
	SetConsoleCP(CODE_PAGE);
	srand(GetTickCount());
	cout << fixed << setprecision(2) << boolalpha;
    
	setColor(mainColor);
	cls();
} // init


// Получение кода нажатой клавиши
int getKey(const string &message) {
	cout << message;
	int key = _getch();
	if (key == 0 || key == 224) key = _getch();

	return key;
} // getKey


// Случайное целое число в диапазоне [low, high]
int getRand(int low, int high) {
	return low + rand() % (high - low + 1);
} // getRand


// Случайное число (double) в диапазоне [low, high]
double getRand(double low, double high) {
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// Случайное число (float) в диапазоне [low, high]
float getRand(float low, float high) {
	return low + (high - low) * rand() / RAND_MAX;
} // getRand


// Случайный символ в диапазоне [low, high]
char getRand(char low, char high) {
	return (char)getRand((int)low, (int)high);
} // getRand


// Установить цвет текста в консоли
// Использует внутренний дескриптор h
void setColor(short color) {
	SetConsoleTextAttribute(h, color);
} // setColor


// Ввод целого числа с проверкой формата
int getInt() {
	int value;
	while(true) {
		// Просим ввести число
		cout << "? ";
		cin >> value;

		// Если ввод корректен — выходим
		if (!cin.fail()) break;

		// Иначе — очищаем состояние и пропускаем остаток строки
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail(), '\n');
	} // while

	return value;
} // getInt


// Проверка формата ввода
void checkInputFormat(istream& is) {
	// Если поток в ошибочном состоянии
	if (is.fail()) {
		// очищаем состояние и пропускаем оставшуюся часть строки
		is.clear();
		is.ignore(is.rdbuf()->in_avail(), '\n');

		// выбрасываем исключение с текстом на русском
		throw exception("Ошибка ввода");
	} // if	
} // checkInputFormat


// Показать сообщение в навигационной строке
void showNavBarMessage(short hintColor, const string &message) {
	setColor(hintColor);

	gotoXY(0, 0);

	// Отобразить сообщение в первой строке консоли
	const COORD conSize = getConsoleSize();
	cout << setw(conSize.X) << left << message << right;
	setColor(mainColor);

	gotoXY(0, 4);
} // showNavBarMessage


// Показать сообщение в навигационной строке с подсветкой части текста
// Часть текста, заключённая в символы '~', будет окрашена в acctColor
void showNavBarMessage(short hintColor, short acctColor, const string &message) {
	setColor(hintColor);
	gotoXY(0, 0);

	const COORD conSize = getConsoleSize();

	// Вывод с возможностью смены цвета в пределах одной строки
	bool acctFlag = false;
	int len = 0;
	for (int i = 0; message[i] != 0; i++) {
		if (message[i] == '~') { 
			setColor(!acctFlag?acctColor:hintColor);
			acctFlag = !acctFlag;
			continue;
		} // if

		cout << message[i];
		++len;
	} // for i 

	// Заполнить оставшуюся часть строки пробелами
	cout << setw(conSize.X - len - 1) << " ";
	setColor(mainColor);

	gotoXY(0, 4);
} // showNavBarMessage


// Показать экран "В разработке"
void showUnderConstruction(short width, short mainColor, short infoColor) {
	ostringstream oss;
	oss << "\n\n\n\n" << left
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    [В разработке]" << "\n"
		<< "\t" << setw(width) << "    Раздел в разработке" << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << "    Здесь пока нет содержимого для отображения..." << "\n"
		<< "\t" << setw(width) << " " << "\n"
		<< "\t" << setw(width) << " " << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << right;
	showMessage(oss.str(), infoColor, mainColor);
} // showUnderConstruction


// Показать сообщение
void showMessage(const string &msg, short msgColor, short mainColor) {
	setColor(msgColor);
	cout << left << msg << right;
	setColor(mainColor);
} // showMessage


// Показать поле ввода
// Выводит подсказку `prompt`, рисует поле шириной `n` и устанавливает курсор внутри
void showInputLine(const string &prompt, short n, short color) {
	// Вывести подсказку
	cout << prompt;               
    
	COORD pos;
	getXY(&pos);

	// Отрисовать поле ввода
	setColor(color);              
	cout << setw(n) << "  ";

	// Установить курсор внутри поля (смещение +1)
	gotoXY(pos.X + 1, pos.Y);
} // showInputLine


// ---------------------------------------------------------------------------------
#pragma region WinAPI_helpers
// Управление видимостью курсора
// mode: true  - показать курсор
//       false - скрыть курсор
void showCursor(bool mode) {
	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(h, &info);

	info.bVisible = mode;
	SetConsoleCursorInfo(h, &info);
} // void showCursor


// Проверить видимость курсора: true - видим, false - скрыт
bool isCursor() {
	CONSOLE_CURSOR_INFO info;

	GetConsoleCursorInfo(h, &info);

	return info.bVisible;
} // isCursor


// Перемещает курсор в позицию (x,y)
void gotoXY(short x, short y) {
	SetConsoleCursorPosition(h, COORD{ x, y });
} // gotoXY


// Записать текущую позицию курсора в `position`
void getXY(COORD* position) {
	CONSOLE_SCREEN_BUFFER_INFO cbuf;
	GetConsoleScreenBufferInfo(h, &cbuf);

	position->X = cbuf.dwCursorPosition.X;
	position->Y = cbuf.dwCursorPosition.Y;
} // getXY

// TODO: реализовать дополнительные утилиты по необходимости


// Очистить экран
void cls() {
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	if (!GetConsoleScreenBufferInfo(h, &csbi)) return;

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	if (!FillConsoleOutputCharacter(h, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	if (!FillConsoleOutputAttribute(h, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	SetConsoleCursorPosition(h, coordScreen);
} // cls


// Размер консольного буфера
COORD getConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(h, &csbi);

	return csbi.dwSize;
} // getConsoleSize

// Convert UTF-8 to CP1251 and print to cout
void printCp1251(const string& utf8) {
	if (utf8.empty()) return;
	int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
	if (wlen == 0) { cout << utf8; return; }
	vector<wchar_t> wbuf(wlen);
	MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, wbuf.data(), wlen);

	int len = WideCharToMultiByte(1251, 0, wbuf.data(), -1, nullptr, 0, nullptr, nullptr);
	if (len == 0) { cout << utf8; return; }
	vector<char> buf(len);
	WideCharToMultiByte(1251, 0, wbuf.data(), -1, buf.data(), len, nullptr, nullptr);

	cout.write(buf.data(), len - 1);
}
#pragma endregion


#pragma region stream_manipulators
// Потоковые манипуляторы и вспомогательные операторы

// Очистка экрана: cout << cls;
ostream& cls(ostream& os) {
	cls();
	return os;
} // cls


// Очистка экрана (ввод): cin >> cls;
istream& cls(istream& is) {
	cls();
	return is;
} // cls


// Табуляция: cout << tab;
ostream& tab(ostream& os) {
	os << "\t";
	return os;
} // tab


// Включить курсор в потоке: cout << cursor
ostream& cursor(ostream& os) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	return os;
} // cursor


// Включить курсор для ввода: cin >> cursor
istream& cursor(istream& is) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = true;
	SetConsoleCursorInfo(h, &info);

	return is;
} // cursor


// Отключить курсор: cout << nocursor
ostream& nocursor(ostream& os) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	return os;
} // nocursor


// Отключить курсор для ввода: cin >> nocursor
istream& nocursor(istream& is) {
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(h, &info);

	info.bVisible = false;
	SetConsoleCursorInfo(h, &info);

	return is;
} // nocursor


// Печать нескольких переводов строки: cout << endlm(n)
ostream& operator<<(ostream& os, const endlm& obj) {
	for (int i = 0; i < obj.n_; ++i) {
		os << "\n";
	}
	return os;
} // operator<<


// Установить цвет в потоке: cout << color(c)
ostream& operator<<(ostream& os, const color& obj) {
	SetConsoleTextAttribute(h, obj.color_);
	return os;
} // operator<<


// Установить цвет из потока: cin >> color(c)
istream& operator>>(istream& is, const color& obj) {
	SetConsoleTextAttribute(h, obj.color_);
	return is;
} // operator>>


// Переместить курсор через поток: cout << pos(x,y)
ostream& operator<<(ostream& os, const pos& obj) {
	SetConsoleCursorPosition(h, { obj.x_, obj.y_ });
	return os;
} // operator<<

// Переместить курсор через ввод: cin >> pos(x,y)
istream& operator>>(istream& is, const pos& obj) {
	SetConsoleCursorPosition(h, { obj.x_, obj.y_ });
	return is;
} // operator>>
#pragma endregion


// Текущий год
int getCurrentYear() {
	time_t t = time(nullptr);
	struct tm tm = *localtime(&t);
	return (tm.tm_year + 1900);
} // getCurrentYear
