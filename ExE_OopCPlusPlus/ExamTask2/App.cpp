#include "App.h"
#include "Utils.h"

App::App() :App("test.txt") {}
App::App(const string& fileName) {
	fileName_ = fileName;
} // App::App

// Сформируйте частотный словарь слов текста. Ключом является слово, 
// значением – количество таких слов в тексте, деленное на общее 
// количество слов в тексте.
void App::doFreqDictWords() {
	showNavBarMessage(hintColor, "    Формирование частотного словаря слов текста");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Сформировать частотный словарь слов
	map<string, double> freqDict = TextProcessor::makeWordsFrequencyDict(fileName_);

	// Вывести словарь
	show("\n\n    Частотный словарь слов текста, файл " + fileName_ + ":", freqDict);
} // App::doFreqDictWords


// Сформируйте частотный словарь букв текста. Ключом является буква 
// (регистро-независимая), значением – количество вхождений этой буквы
// в тексте, деленное на общее количество букв в тексте.
void App::doFreqDictLetters() {
	showNavBarMessage(hintColor, "    Формирование частотного словаря букв текста");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Сформировать частотный словарь букв
	map<char, double> freqDict = TextProcessor::makeLettersFrequencyDict(fileName_);

	// Вывести словарь
	show("\n\n    Частотный словарь букв текста, файл " + fileName_ + ":", freqDict);
} // App::doFreqDictLetters


// Поменять местами в тексте каждые две соседние строки, измененный текст 
// сохранить в файле swap.tx
void App::doSwapLines() {
	showNavBarMessage(hintColor, "    Поменять местами в тексте каждые две соседние строки");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Обработка файла, в тексте поменять местами каждые две соседние строки,
	// сохранить измененный текст в файл result
	string result = "swap.txt";
	TextProcessor::swapLines(fileName_, result);

	// Вывод обработанного файла
	viewText("Файл " + result + ", в тексте каждые две соседние строки поменяли местами:", result);
} // App::doSwapLines


// Перевести все слова в тексте в формат: первая буква верхнего регистра, 
// остальные буквы в нижнем регистре (Это Пример Такого Формата), 
// сохранить текст в файле capitalize.txt 
void App::doWordsCapitalize() {
	showNavBarMessage(hintColor, "    Все слова текста перевести в регистр Capitalize, запись в файл");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Обработка файла, в тексте все слова перевести в регистр Capitalize,
	// сохранить измененный текст в файл result
	string result = "capitalize.txt";
	TextProcessor::capitalizeText(fileName_, result);

	// Вывод обработанного файла
	viewText("Файл " + result + ", в тексте каждые две соседние строки поменяли местами:", result);
} // App::doWordsCapitalize


// Упорядочить строки текста по длине, сохранить текст в файл с именем 
// orderByLen.txt
void App::doOrderByLen() {
	showNavBarMessage(hintColor, "    Упорчдочить строки текста по длине, запись в файл");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Упорядочить текст по длине строк, сохранить измененный текст в файл result
	string result = "orderByLen.txt";
	TextProcessor::orderByLen(fileName_, result);

	// Вывод обработанного файла
	viewText("Файл " + result + ", текст упорядочен по длине строк:", result);
} // App::doOrderByLen


// В каждой строке текста упорядочить слова по алфавиту, оставить между 
// словами по одному пробелу, сохранить измененный текст в файле с именем 
// orderlines.txt 
void App::doOrderWordsInLines() {
	showNavBarMessage(hintColor, "    Упорчдочить слова а строках текста по алфавиту, запись в файл");

	// Показать файл для обработки
	viewText("Файл " + fileName_ + ", текст для обработки:");

	// Упорядочить слоыв в строках \по алфавиту, сохранить измененный текст в файл result
	string result = "orderlines.txt";
	TextProcessor::orderLines(fileName_, result);

	// Вывод обработанного файла
	viewText("Файл " + result + ", слова в чтроках упорядочены по алфавиту:", result);
} // App::doOrderWordsInLines


// -------------------------------------------------------

void App::viewText(const string & title, const string &fileName) {
	cout<< "     " << title << "\n"
		<< "     +" << setfill('-') << setw(92) << "-" << "+" 
		<< setfill(' ') << "\n";

	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("App: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	int row = 1;
	while (!fs.eof()) {
		string line;
		getline(fs, line);

		cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
			<< " | " << left << setw(90) << line << right << " |\n";

		fs.peek();
	} // ehile

	fs.close();
	cout<< "     +" << setfill('-') << setw(92) << "-" << "+"
		<< setfill(' ') << "\n";
} // App::viewText


// Делегирующий вызов для вывода файла fileName_
void App::viewText(const string& title) {
	viewText(title, fileName_);
} // App::viewText


// Вывод частотного словаря слов
void App::show(const string& title, const map<string, double>& freqDict) {
	cout << "    " << title << "\n" << setprecision(3);
	
	int counter = 1;
	double r = 0;
	for (auto &item: freqDict) {
		cout<< "    " << left << setw(20) << item.first << right
			<< setw(5) << item.second << " || ";

		if (counter++ % 3 == 0) {
			cout << "\n";
		} // if

		r += item.second;
	} // for item 

	cout << "\n    Сумма частот: " << r << "\n\n";
} // App::show 


// Вывод частотного словаря букв
void App::show(const string& title, const map<char, double>& freqDict) {
	cout << "    " << title << "\n" << setprecision(3);

	int counter = 1;
	double r = 0;
	for (auto& item : freqDict) {
		cout << "    " << item.first << "  "
			<< setw(5) << item.second << " || ";

		if (counter++ % 5 == 0) {
			cout << "\n";
		} // if

		r += item.second;
	} // for item 

	cout << "\n    Сумма частот: " << r << "\n\n";
} // App::show 
