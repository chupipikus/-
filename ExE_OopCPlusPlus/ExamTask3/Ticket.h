#pragma once
#include "pch.h"
#include "Object.h"
#include "Date.h"


// Заявка на авиабилет содержит:
// числовой идентификатор, пункт назначения, номер рейса (например, PO-2212K), фамилию и инициалы пассажира (Иванов П.О., …), желаемую дату вылета (класс Date, который был предложен в течение курса).  
class Ticket : public Object
{
	// числовой идентификатор
	int id_;

	// пункт назначения
	string destination_;

	// номер рейса (например, PO-2212K)
	string flight_;

	// фамилию и инициалы пассажира (Иванов П.О., …)
	string pax_;

	// желаемая дата вылета (класс Date, который был предложен в течение курса)   
	Date departureDate_;

public:

	// Длины строковых полей при записи в бинарный файл
	static const int LEN_DESTINATION = 31, LEN_FLIGHT = 16, LEN_PAX = 33;

	// Конструкторы
	Ticket();
	Ticket(int id, const string &destination, const string &flight, 
		const string &pax, const Date &departureDate
	);

	// Аксессоры

	// числовой идентификатор
	int id() const;
	void id(int value);

	// пункт назначения
	string destination() const;
	void   destination(const string &value);

	// номер рейса (например, PO-2212K)
	string flight() const;
	void   flight(const string& value);

	// фамилию и инициалы пассажира (Иванов П.О., …)
	string pax() const;
	void   pax(const string& value);

	// желаемая дата вылета (класс Date, который был предложен в течение курса)   
	Date departureDate() const;
	void departureDate(const Date &value);

	// Запись в бинарный фпйл, чтение из бинарного файла
	void save(fstream &fs);
	void load(fstream &fs);

	// Длина одной записи в бинарном файле
	static int recordLen();

	// Вывод в строковом формате
	string toString() override;

	// Вывод в формате строки таблицы
	string toTableRow();

	// формирование шапки и подвала таблицы
	static string header();
	static string footer();
};

