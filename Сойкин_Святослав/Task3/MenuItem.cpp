#include "pch.h"
#include "MenuItem.h"
// пункт меню

// конструкторы и деструктор

MenuItem::MenuItem() :MenuItem(1, "Текст пункта меню"s) {}

MenuItem::MenuItem(int command, const string &text):
	command_(command), text_(text), selected_(false)
{
} // MenuItem::MenuItem

// аксессоры
int MenuItem::command() const { return command_; }
const string &MenuItem::text() const { return text_; }

bool MenuItem::isSelected() const { return selected_; }
void MenuItem::selected(bool value) { selected_ = value; }
