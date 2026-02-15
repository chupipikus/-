#include "pch.h"
#include "FlightSeeder.h"
#include "TicketFactory.h"
#include "Utils.h"

// Инициализация статических полей
const vector<FlightSeeder> TicketFactory::flights_ = {
	{"S7 1221", "Москва"}, {"S7 1230", "Тюмень"}, {"S7 1211", "Казань"}, 
	{"S7 1211", "Владивосток"}, {"S7 1233", "Астрахань"},

	{"Урал 678", "Москва"}, {"Урал 223", "Екатеринбург"}, {"Урал 230", "Казань"},
	{"Урал 221", "Адлер"}, {"Урал 776", "Саратов"},

	{"Россмя 788", "Москва"}, {"Россмя 789", "Тюмень"}, {"Россмя 780", "Казань"},
	{"Россмя 787", "Владивосток"}, {"Россмя 778", "Астрахань"},

	{"Югра 4578", "Москва"}, {"Югра 4228", "Минск"}, {"Югра 4555", "Казань"},
	{"Югра 1178", "Иваново"}, {"Югра 4567", "Архангельск"},

};


const vector<string> TicketFactory::paxes_ = {
	"Измайлов М.О.", "Гурова П.Р.", "Ревякина Г.Е.", "Давыдов И.А.", "Лесков Ш.Е.",
	"Шавыркин Б.П.", "Жарикова Р.Р.", "Свиридова Н.Н.", "Искандеров Л.П.", "Сомова Р.А.",
	"Костин В.Ф.", "Васнецов Р.П.", "Достоев Ф.М.", "Зеркин З.Н.", "Ашкеназин А.А."
};


Ticket TicketFactory::create(int idSeed) {
	auto flightSeed = flights_[getRand(0, flights_.size()-1)];
	string flight      = flightSeed.flight;
	string destination = flightSeed.destination;

	string pax = paxes_[getRand(0, paxes_.size()-1)];

	// простой способ формирования случайной даты
	Date departureDate = Date::now() + getRand(14, 48);

	return Ticket(idSeed, destination, flight, pax, departureDate);
} // TicketFactory::create


list<Ticket> TicketFactory::create(int idSeed, int n) {
	list<Ticket> data;
	for (int i = 0; i < n; i++) {
		data.emplace_back(create(idSeed + i));
	} // for i
	return data;
} // TicketFactory::create
