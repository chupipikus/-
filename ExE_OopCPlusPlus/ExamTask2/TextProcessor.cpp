#include "TextProcessor.h"

// Сформировать частотный словарь
map<string, double> TextProcessor::makeWordsFrequencyDict(const string& fileName) {
	map<string, double> freqDict;
	
	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	// Построчное чтение и обработка файла
	int wordsCounter = 0;
	for (; !fs.eof(); fs.peek()) {
		string line;
		getline(fs, line);

		// не обрабатываем пустую строку
		if (line.empty()) { 
			continue; 
		} // if

		// Построчная обработка: выделение слов, 
		// подсчет общего количества слов,
		// заполнение словаря
		vector<string> words = splitBySpace(line);
		for (auto word: words) {
			freqDict[word] += 1;
		} // for word

		wordsCounter += words.size();
	} // ehile

	fs.close();

	// нормирование словаря: поделить в каждой паре количество слов
	// на общее количество слов в тексте
	for (auto& item : freqDict) {
		item.second /= wordsCounter;
	} // for item
	
	return freqDict;
} // TextProcessor::makeWordsFrequencyDict


// Сформировать частотный словарь букв
map<char, double> TextProcessor::makeLettersFrequencyDict(const string& fileName) {
	map<char, double> freqDict;

	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	// Построчное чтение и обработка файла
	int lettersCounter = 0;
	for (; !fs.eof(); fs.peek()) {
		string line;
		getline(fs, line);

		// не обрабатываем пустую строку
		if (line.empty()) {
			continue;
		} // if

		// Построчная обработка: подсчет общего количества букв,
		// заполнение словаря
		for (auto ch : line) {
			if (ch == ' ') {
				continue;
			} // if

			freqDict[ch] += 1;
			lettersCounter++;
		} // for ch
	} // while

	fs.close();

	// нормирование словаря: поделить в каждой паре количество букв
	// на общее количество букв в тексте
	for (auto& item : freqDict) {
		item.second /= lettersCounter;
	} // for item

	return freqDict;
} // TextProcessor::makeLettersFrequencyDict


// Обработка файла, в тексте поменять местами каждые две соседние строки,
// сохранить измененный текст в файл result
void TextProcessor::swapLines(const string& fileName, const string& result) {
	vector<string> text = readLines(fileName);

	for (int i = 0; i < text.size() - 1; i += 2) {
		swap(text[i], text[i + 1]);
	} // for i

	writeLines(result, text);
} // TextProcessor::swapLines


// Обработка файла, в тексте все слова перевести в регистр Capitalize,
// сохранить измененный текст в файл result
void TextProcessor::capitalizeText(const string& fileName, const string& result) {
	vector<string> text = readLines(fileName);

	for (auto &line: text) {
		if (line.empty()) {
			continue;
		} // if\

		// обработка каждой строки
		vector<string> words = splitBySpace(line);
		for (auto &word: words) {
			// !! проблему с 'я' обнаружил Гладченко Д., ПВ-521
			word[0] = (word[0] == 'я')? 'Я': toupper(word[0]);
		} // for word

		// формирование строки из преобразованных слов
		line = join(" ", words);
	} // for line

	writeLines(result, text);
} // TextProcessor::capitalizeText


// Упорядочить текст по длине строк, сохранить измененный текст в файл result
void TextProcessor::orderByLen(const string& fileName, const string& result) {
	vector<string> text = readLines(fileName);

	sort(text.begin(), text.end(), [](const string &s1, const string& s2) {
		return s1.size() < s2.size();
	});

	writeLines(result, text);
} // TextProcessor::orderByLen


// Упорядочить слоыв в строках по алфавиту, сохранить измененный текст в файл result
void TextProcessor::orderLines(const string& fileName, const string& result) {
	vector<string> text = readLines(fileName);

	for (auto& line : text) {
		if (line.empty()) {
			continue;
		} // if

		auto words = splitBySpace(line);
		sort(words.begin(), words.end());

		line = join(" ", words);
	} // for line

	writeLines(result, text);
} // TextProcessor::orderLines


// ------------------------------------------------------------------

// возвращает вектор слов из строки, состоящей из русских букв,
// слова разделяются одним или несколкими пробелами
vector<string> TextProcessor::splitBySpace(const string& line) {
	vector<string> words;

	stringstream ss(line);

	while (!ss.fail()) {
		string word;
		ss >> word;

		// игнорируем пустые строки, которые образуются
		// из-за двух поодряд идущих пробелов
		if (word.empty()) {
			continue;
		} // if

		// cout << "DEBUG: " << word << "\n";
		words.emplace_back(word);
	} // while

	return words;
} // TextProcessor::splitBySpace	// чтение текста в вектор


// Чтение файла в вектор 
vector<string> TextProcessor::readLines(const string& fileName) {
	fstream fs(fileName, ios::in);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	// задать кодировку потока ввода CP1251  
	fs.imbue(locale(".1251"));

	// Построчное чтение файла, добавление строки в вектор
	vector<string> text;
	for (;  !fs.eof(); fs.peek()) {
		string line;
		getline(fs, line);
		text.emplace_back(line);
	} // for

	fs.close();
	return text;
} // TextProcessor::readLines


// Запись вектора в файл
void TextProcessor::writeLines(const string& fileName, const vector<string>& text) {
	fstream fs(fileName, ios::out);

	if (!fs.is_open()) {
		throw exception(("TextProcessor: Ошибка открытия файла " + fileName + " для записи").c_str());
	} // if

	// задать кодировку потока вывода CP1251  
	fs.imbue(locale(".1251"));

	// Запись строки из вектора в файл
	for (auto line:text) {
		fs << line << "\n";
	} // for

	fs.close();
} // TextProcessor::writeLines


// соединение строк из вектора через разделиель
string TextProcessor::join(const string& delimeter, const vector<string> tokens) {
	auto line = ""s;

	for (auto& token : tokens) {
		line += token + " ";
	} // for token

	// удалить последний символ строик - добавленный пробел
	line.resize(line.size() - 1);
	return line;
} // TextProcessor::join
