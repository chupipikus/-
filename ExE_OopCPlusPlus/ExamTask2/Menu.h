#pragma once
#ifndef MENU_H
#define MENU_H


#include "pch.h"
#include "MenuItem.h"
#include "Palette.h"


// меню - контейнерный класс с массивом пунктов меню
class Menu
{
	// позиция размещения меню на экране
	COORD startPosition_;
	
	// цвет вывода не выбранного пункта меню
	short itemColor_;

	// цвет вывода выбранного пункта меню
	short currentColor_;

	// вектор пунктов меню 
	vector<MenuItem> menuItems_;

	// возвращает максимальную длину текста пункта меню
	int getMaxLen();

public:

	// конструкторы и деструктор
	Menu();

	Menu(const COORD startPosition, const vector<MenuItem> &menuItems, Palette itemColor, Palette currentColor);

	// Menu(const Menu& other) = default;
	// деструктор
	// ~Menu() = default;
	// операция присваивания
	// Menu& operator=(const Menu& other) = default;

	// аксессоры
	short itemColor() const;
	void itemColor(short value);

	short currentColor() const;
	void currentColor(short value);

	// методы класса
	// вывод пунктов меню
	void show();

	// навигация по пунктам меню - возвращает код выбранной команды
	int navigate();

	// коды стандартных команд 
	static const int CMD_QUIT = 1;
};
#endif
