#include "Ticket.h"

// Конструкторы
Ticket::Ticket() {} // Ticket::Ticket

Ticket::Ticket(int id, const string& destination, const string& flight,
	const string& pax, const Date& departureDate
) {
	this->id(id);
	this->destination(destination);
	this->flight(flight);
	this->pax(pax);
	this->departureDate(departureDate);
} // Ticket::Ticket

// Аксессоры

// числовой идентификатор
int Ticket::id() const { return id_;  } // Ticket::id
void Ticket::id(int value) { id_ = value;  } // Ticket::id

// пункт назначения
string Ticket::destination() const { 
	return destination_; 
} // Ticket::destination

void   Ticket::destination(const string& value) {
	destination_ = value.empty()
		? throw exception("Ticket: недопустимое название пункта назначения.")
		: value;
} // Ticket::destination


// номер рейса (например, PO-2212K)
string Ticket::flight() const { return flight_; }
void   Ticket::flight(const string& value) {
	flight_ = value.empty()
		? throw exception("Ticket: недопустимый номер рейса.")
		: value;
}


// фамилию и инициалы пассажира (Иванов П.О., …)
string Ticket::pax() const { return pax_; }
void   Ticket::pax(const string& value) {
	pax_ = value.empty()
		? throw exception("Ticket: не указано ФИО пассажира.")
		: value;
}


// желаемая дата вылета (класс Date, который был предложен в течение курса)   
Date Ticket::departureDate() const { return departureDate_; }
void Ticket::departureDate(const Date& value) {
	departureDate_ = value;
}


// Запись в бинарный фпйл, чтение из бинарного файла
void Ticket::save(fstream& fs) {
	int len = max(LEN_DESTINATION, max(LEN_FLIGHT, LEN_PAX));
	char* buf = new char[len] {};
	
	fs.write((char *)&id_, sizeof(int));

	strcpy(buf, destination_.c_str());
	fs.write(buf, LEN_DESTINATION);

	memset(buf, 0, len);
	strcpy(buf, flight_.c_str());
	fs.write(buf, LEN_FLIGHT);

	memset(buf, 0, len);
	strcpy(buf, pax_.c_str());
	fs.write(buf, LEN_PAX);

	short temp[] = { departureDate_.getDay(), departureDate_.getMonth(), departureDate_.getYear() };
	fs.write((char*)temp, sizeof(temp));

	delete[] buf;
} // Ticket::save


// Чтение из бинарного файла
void Ticket::load(fstream& fs) {
	int len = max(LEN_DESTINATION, max(LEN_FLIGHT, LEN_PAX));
	char* buf = new char[len] {};

	fs.read((char*)&id_, sizeof(int));

	fs.read(buf, LEN_DESTINATION);
	destination_ = buf;

	fs.read(buf, LEN_FLIGHT);
	flight_ = buf;

	fs.read(buf, LEN_PAX);
	pax_ = buf;

	short temp[3];
	fs.read((char*)temp, sizeof(temp));

	departureDate_.setDate(temp[0], temp[1], temp[2]);

	delete[] buf;
} // Ticket::load


// Длина одной записи в бинарном файле
int Ticket::recordLen() {
	return sizeof(int) + LEN_DESTINATION + LEN_FLIGHT + LEN_PAX + 3*sizeof(short);
} // Ticket::recordLen


// Вывод в строковом формате
string Ticket::toString() {
	ostringstream oss;
	oss << "Ticket {" << id_ << ": " 
		<< pax_ << ", " << flight_ << ", "
		<< destination_ << ", " << departureDate_
		<< "}";
	return oss.str();
} // Ticket::toString


// Вывод в формате строки таблицы
string Ticket::toTableRow() {
	ostringstream oss;
	oss << "| " << setw(4) << id_ << " "
		<< "| " << left << setw(20) << pax_ << " " 
		<< "| " << setw(12) << flight_ << " "
		<< "| " << setw(20) << destination_ << right << " " 
		<< "| " << setw(11) << departureDate_ << " |";
	return oss.str();
} // Ticket::toTableRow


// формирование шапки таблицы
string Ticket::header() { return 
    "    +------+----------------------+--------------+----------------------+-------------+\n"s
	"    |  Ид. | ФИО пассажира        | Номер рейса  | Пункт назначения     | Дата вылета |\n"s
	"    +------+----------------------+--------------+----------------------+-------------+\n"s;
} // Ticket::header


// формирование подвала таблицы
string Ticket::footer() {
	return "    +------+----------------------+--------------+----------------------+-------------+\n"s;
} // Ticket::footer
