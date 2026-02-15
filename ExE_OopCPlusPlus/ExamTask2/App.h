#pragma once
#include "pch.h"
#include "TextProcessor.h"

class App
{
	string fileName_;

	// Вывод текстового файла
	void viewText(const string &title, const string &fileName);
	void viewText(const string& title);

	// Вывод частотного словаря слов
	void show(const string &title, const map<string, double> &freqDict);

	// Вывод частотного словаря букв
	void show(const string& title, const map<char, double>& freqDict);

public:
	App();
	App(const string& fileName);

	// Сформируйте частотный словарь слов текста. Ключом является слово, 
    // значением – количество таких слов в тексте, деленное на общее 
    // количество слов в тексте.
	void doFreqDictWords();

	// Сформируйте частотный словарь букв текста. Ключом является буква 
	// (регистро-независимая), значением – количество вхождений этой буквы
	// в тексте, деленное на общее количество букв в тексте.
	void doFreqDictLetters();
	
	// Поменять местами в тексте каждые две соседние строки, измененный текст 
	// сохранить в файле swap.txt
	void doSwapLines();
	
    // Перевести все слова в тексте в формат: первая буква верхнего регистра, 
    // остальные буквы в нижнем регистре (Это Пример Такого Формата), 
    // сохранить текст в файле capitalize.txt 
	void doWordsCapitalize();
	
	// Упорядочить строки текста по длине, сохранить текст в файл с именем 
	// orderByLen.txt
	void doOrderByLen();
	
	// В каждой строке текста упорядочить слова по алфавиту, оставить между 
    // словами по одному пробелу, сохранить измененный текст в файле с именем 
    // orderliness.txt 
	void doOrderWordsInLines();
};

