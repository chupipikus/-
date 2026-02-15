#include "pch.h"
#include "Utils.h"
#include "Menu.h"

#include "FKeys.h"

Menu::Menu() :startPosition_(), itemColor_(mainColor), currentColor_(infoColor), menuItems_() {}

Menu::Menu(const COORD startPosition, const vector<MenuItem>& menuItems, Palette itemColor, Palette currentColor):
	startPosition_(startPosition),
	itemColor_(itemColor),
	currentColor_(currentColor),
    menuItems_(menuItems)  // тут вызываются копирующий конструктор
{
	// при старте выбранным является первый пункт меню
	menuItems_[0].selected(true);
} // Menu::Menu


// аксессоры
short Menu::itemColor() const { return itemColor_; }
void Menu::itemColor(short value) { itemColor_ = value; }

short Menu::currentColor() const { return currentColor_; }
void Menu::currentColor(short value) { currentColor_ = value; }

// методы класса


// возвращает максимальную длину текста пункта меню
int Menu::getMaxLen() {
	return (int)max_element(menuItems_.begin(), menuItems_.end(),
		[](MenuItem& mi1, MenuItem& mi2) { return mi1.text().length() < mi2.text().length();  })->text().length();
} // Menu::getMaxLen


// вывод пунктов меню
void Menu::show() {
	// максимальная длина текста в пункте меню
	int maxLen = getMaxLen();
	cout << left;

	// вывод в заданные позиции, все элемены одинаковой ширины,
	// а также выводим 4хпробельные поля перед и после текста
	int rowOffset = 0;
	for (auto mi:menuItems_) {
		cout<< pos(startPosition_.X, startPosition_.Y + rowOffset++)
			<< color(mi.isSelected()?currentColor_:itemColor_)
			<< "    " << setw(maxLen)<< mi.text() << "    ";
	} // for mi
	cout << right;
} // Menu::show


// навигация по пунктам меню - возвращает код выбранной команды
int Menu::navigate() {
	int cmd = -1;

	// выключить курсор
	cout << nocursor;

	// цикл ввода кодов клавиш, выход - по ENTER/RETURN или ESCAPE
	auto it = find_if(menuItems_.begin(), menuItems_.end(), 
		[](const MenuItem& mi) { return mi.isSelected(); });

	while (true) {
		// вывод пунктов меню
		show();
		
		// вводим код нажатой клавиши
		short key = _getch();
		if (key == 0 || key == 224) key = _getch();

		// выход из цикла с командой, соответствующей пункту меню
		if (key == VK_RETURN) {
			cmd = it->command();
			break;
		} // if

		// выход из цикла со стандартной командой - выход
		if (key == VK_ESCAPE || key == K_F10) {
			cmd = CMD_QUIT;
			break;
		} // if

		// отработка клавиш управления курсором
		switch (key) {
		// по стрелке вниз
		case K_DOWN:
			// текущий пункт меню делаем не выбранным
			it->selected(false);

			// переходим к следующему пункту меню
			if (it == menuItems_.end() - 1) {
				it = menuItems_.begin();
			}
			else {
				it++;
			} // if
			break;

		// по стрелке вверх
		case K_UP:
			// текущий пункт меню делаем не выбранным
			it->selected(false);

			// переходим к предыдущему пункту меню
			if (it == menuItems_.begin()) {
				it = menuItems_.end() - 1;
			}
			else {
				it--;
			} // if
			break;

		case K_HOME:
			if (it != menuItems_.begin()) {
				// текущий пункт меню делаем не выбранным
				it->selected(false);

				it = menuItems_.begin();
			} // if
			break;

			case K_END:
			if (it != menuItems_.end() - 1) {
				// текущий пункт меню делаем не выбранным
				it->selected(false);

				it = menuItems_.end() - 1;
			} // if
			break;
		} // switch

		// i-й пункт меню делаем выбранным
		it->selected(true);
	} // while

	// включить курсор, восстановить цвет
	cout << cursor << color(mainColor);
	return cmd;
} // Menu::navigate
