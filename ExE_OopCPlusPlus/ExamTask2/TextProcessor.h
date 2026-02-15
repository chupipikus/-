#pragma once
#include "pch.h"


class TextProcessor
{
	// возвращает вектор слов из строки, состо€щей из русских букв,
	// слова раздел€ютс€ одним или несколкими пробелами
	static vector<string> splitBySpace(const string &line);

	// чтение текста в вектор
	static vector<string> readLines(const string &fileName);

	// запись вектора в файл
	static void writeLines(const string &fileName, const vector<string> &text);

	// соединение строк из вектора через разделиель
	static string join(const string &delimeter, const vector<string> tokens);

public:

	// —формировать частотный словарь
	static map<string, double> makeWordsFrequencyDict(const string &fileName);

	// —формировать частотный словарь букв
	static map<char, double> makeLettersFrequencyDict(const string& fileName);

	// ќбработка файла, в тексте помен€ть местами каждые две соседние строки,
	// сохранить измененный текст в файл result
	static void swapLines(const string &fileName, const string &result);

	// ќбработка файла, в тексте все слова перевести в регистр Capitalize,
	// сохранить измененный текст в файл result
	static void capitalizeText(const string& fileName, const string& result);

	// ”пор€дочить текст по длине строк, сохранить измененный текст в файл result
	static void orderByLen(const string &fileName, const string &result);

	// ”пор€дочить слоыв в строках по алфавиту, сохранить измененный текст в файл result
	static void orderLines(const string& fileName, const string &result);
};

