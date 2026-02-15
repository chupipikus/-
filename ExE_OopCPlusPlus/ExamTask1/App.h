#pragma once
#include "pch.h"
#include "VectorProcess.h"

class App
{
	// обработка вектора по заданию
	VectorProcess vectorProcess_;

	// им€ бинарного файла дл€ хранени€ вектора
	string fileName_;

	// ¬ывод вектора в консоль, по m элементов в строке, точность 
	// precision знаков
	void show(const string &title, float a = 0, float b = 0, int m = 8, int precision = 3);
	
	static void show(const string &title, const vector<float> &data, int m = 8, int precision = 3);

public:
	App();
	App(const VectorProcess &vectorProcess, const string &fileName);

	// ќбработка по заданию
	void doProcess();
};

