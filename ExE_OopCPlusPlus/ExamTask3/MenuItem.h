#pragma once
// пункт меню
class MenuItem
{
	// код команды
	int command_;

	// текст пункта меню
	string text_;

	// признак выбранного пункта меню
	bool selected_;

public:
	// конструкторы и деструктор
	MenuItem();
	
	// MenuItem(int command, const char* text);
	MenuItem(int command, const string &text);

	MenuItem(const MenuItem& other)=default;

	~MenuItem() = default;

	// перегрузка операции присваивания
	MenuItem& operator=(const MenuItem& other) = default;

	// аксессоры
    int command() const;
	const string &text() const;
	bool isSelected() const;
	void selected(bool value);
};

