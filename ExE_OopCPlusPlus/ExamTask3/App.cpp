#include "pch.h"
#include "App.h"
#include "TicketFactory.h"
#include "Utils.h"

App::App():App(TicketFactory::create(1000, getRand(12, 18)), "tickets.bin") {

} // App::App


App::App(const list<Ticket> tickets, const string& fileName) {
	tickets_ = tickets;
	fileName_ = fileName;
} // App::App

// вывод коллекции заявок в кносоль
void App::show(const string& title) {
	show(title, tickets_);
} // App::show


// вывод выборки заявок в консоль
void App::show(const string& title, list<Ticket>& data) {
	cout << title << "\n" << Ticket::header();

	for (auto ticket: data) {
		cout << "    " << ticket.toTableRow() << "\n";
	} // for ticket

	cout << Ticket::footer();
} // App::show


// вывод выборки заявок в консоль
void App::show(const string& title, vector<Ticket>& data) {
	cout << title << "\n" << Ticket::header();

	for (auto ticket : data) {
		cout << "    " << ticket.toTableRow() << "\n";
	} // for ticket

	cout << Ticket::footer();
} // App::show


// запись коллекции заяок в бинарный файл
void App::save() {
	fstream fs(fileName_, ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App: Ошибка открытия файла " + fileName_ + " для записи").c_str());
	} // if

	for (auto datum : tickets_) {
		datum.save(fs);
	} // for datum

	fs.close();
} // App::save


// чтение коллекции заяок из бинарного файла
void App::load() {
	fstream fs(fileName_, ios::in | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App: Ошибка открытия файла " + fileName_ + " для чтения").c_str());
	} // if

	for (tickets_.clear(); !fs.eof(); fs.peek()) {
		Ticket ticket;
		ticket.load(fs);
		tickets_.emplace_back(ticket);
	} // for fs

	fs.close();
} // App::load


// поменять местами перую и последнюю записи
void App::firstLastSwap() {
	fstream fs(fileName_, ios::in | ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App: Ошибка открытия файла " + fileName_ + " для чтения/записи").c_str());
	} // if

	// прочитать первую запись
	Ticket first;
	first.load(fs);

	// перейти к посленей записи и прочитать ее
	fs.seekg(-Ticket::recordLen(), ios::end);
	Ticket last;
	last.load(fs);

	// перейти к первой записи, записать данные последней записи
	fs.seekp(0, ios::beg);
	last.save(fs);

	// перейти к последней записи, записть данные первой записи
	fs.seekp(-Ticket::recordLen(), ios::end);
	first.save(fs);

	fs.close();
} // App::firstLastSwap


// обмен самой ранней и самой поздней записей
void App::earliestLatestSwap() {
	fstream fs(fileName_, ios::in | ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("App: Ошибка открытия файла " + fileName_ + " для чтения/записи").c_str());
	} // if

	// Для повышения производительности, поиска самой ранней и самой поздней
	// записей за один проход реализуем "божественный" цикл
	Ticket earliest;
	earliest.load(fs);
	Ticket latest = earliest;

	int posEarliest = 0, posLatest = 0;

	// Цикл до достижения конца файла, при достижении конца
	// файла возникает ситуация EOF (End Of File), т.е. ошибка
	// и все файловые операции блокируются до сброса признака
	// ошибки
	for (int i = 1; !fs.eof(); i++, fs.peek()) {
		Ticket ticket;
		ticket.load(fs);

		if (ticket.departureDate() < earliest.departureDate()) {
			earliest = ticket;
			posEarliest = i;
		} // if

		if (ticket.departureDate() > latest.departureDate()) {
			latest = ticket;
			posLatest = i;
		} // if
	} // for i

	// сброс признака ошибки после достижения конца файла, чтобы
	// выполнялись операции записи
	fs.clear();

	// собственно запись в файл с обменом по заданию
	fs.seekp(posEarliest*Ticket::recordLen(), ios::beg);
	latest.save(fs);

	fs.seekp(posLatest * Ticket::recordLen(), ios::beg);
	earliest.save(fs);

	fs.close();
} // App::earliestLatestSwap


#pragma region Методы обработки по заданию

// Генерация коллекции заявок фабричным методом 
void App::doGenerate() {
	showNavBarMessage(hintColor, "    Генерация коллекции заявок фабричным методом");

	tickets_ = list<Ticket>(getRand(12, 18));
	int id = getRand(1, 9) * 1000;
	generate(tickets_.begin(), tickets_.end(), [&id]() {
		return TicketFactory::create(id++);
	});

	show("    Сформирована коллекция заявок на авиабилеты");
} // App::doGenerate


// Вывод текущего состояния коллекции заявок
void App::doShowAll() {
	showNavBarMessage(hintColor, "  Вывод текущего состояния коллекции заявок");

	show("    Коллекция заявок на авиабилеты:");
} // App::doShowAll


// Добавление заявки, сформированной фабричным методом
void App::doAddByFactory() {
	showNavBarMessage(hintColor, "");

	// добавление
	int idMax = max_element(tickets_.begin(), tickets_.end(), 
		[](const Ticket& t1, const Ticket& t2) { return t1.id() < t2.id(); })->id();
	auto ticket = TicketFactory::create(idMax + 1);
	tickets_.emplace_back(ticket);

	// Вывести измененную коллекцию
	show("    В коллекцию добавлена заявка с ид. "s + to_string(ticket.id()));
} // App::doAddByFactory


// Удаление заявки по идентификатору
void App::doDeleteById() {
	showNavBarMessage(hintColor, "  Удаление заявки по идентификатору");

	show("    Коллекция заявок на авиабилеты:");

	// ввод идентфикатора для удаления записи
	int id;
	cout<< "\n    Идентфикатор записи для удаления: "
		<< color(infoColor) << setw(31) << " ";
	COORD position;
	getXY(&position);
	cin >> pos(position.X - 30, position.Y) >> cursor >> id >> nocursor >> color(mainColor);
	checkInputFormat(cin);

	if (id <= 0) {
		throw exception("App. Некорректное значение идентификатора");
	} // if

	cout << pos(4, position.Y) << setw(80) << " " << pos(4, position.Y);

	// получение итератора для удаления из коллекции
	auto it = find_if(tickets_.begin(), tickets_.end(),
		[id](const Ticket& ticket) {
			return ticket.id() == id;
		}
	);
	if (it == tickets_.end()) {
		cout<< color(errColor) << "    Не найдена запись с ид. " 
			<< id << "    " << color(mainColor);
		return;
	} // if

	tickets_.erase(it);
	show("    Из коллекции удалена заявка с ид. "s + to_string(id) + ":"s);
} // App::doDeleteById


// Отбор заявок по заданному номеру рейса
void App::doFindByFlight() {
	showNavBarMessage(hintColor, "   Отбор заявок по заданному номеру рейса");

	show("    Коллекция заявок на авиабилеты:");

	// ввод номера рейса для отбора записей
	string flight;
	cout << "\n    Номер рейса для отбора заявок: "
		<< color(infoColor) << setw(31) << " ";
	COORD position;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getXY(&position);
	cout << pos(position.X - 30, position.Y) << cursor;
	getline(cin, flight);
	cout << nocursor << color(mainColor);

	if (flight.empty()) {
		throw exception("App. Не указан номер рейса для отбора заявок");
	} // if

	cout << pos(4, position.Y) << setw(80) << " " << pos(4, position.Y);

	// отбор заявок на заданный номер рейса
	vector<Ticket> result;
	copy_if(tickets_.begin(), tickets_.end(), back_inserter(result), [flight](const Ticket& ticket) {
		return ticket.flight() == flight;
	});
	show("    Из коллекции выбраны заявка/заявки на рейс номер '"s + flight + "':"s, result);
} // App::doFindByFlight


// Отбор заявок по фамилии и инициалам пассажира
void App::doFindbyPax() {
	showNavBarMessage(hintColor, "  Отбор заявок по фамилии и инициалам пассажира");

	show("    Коллекция заявок на авиабилеты:");

	// ввод фамилии и инициалов пассажира для отбора записей
	string pax;
	cout << "\n    Фамилия и иницивлы пассажира для отбора заявок: "
		<< color(infoColor) << setw(31) << " ";
	COORD position;
	getXY(&position);
	cout << pos(position.X - 30, position.Y) << cursor;
	cin.ignore(cin.rdbuf()->in_avail(), '\n');
	getline(cin, pax);
	cout << nocursor << color(mainColor);

	if (pax.empty()) {
		throw exception("App. Не указан пассажир для отбора заявок");
	} // if

	cout << pos(4, position.Y) << setw(80) << " " << pos(4, position.Y);

	// отбор заявок пассажира
	vector<Ticket> result;
	copy_if(tickets_.begin(), tickets_.end(), back_inserter(result), [pax](const Ticket &ticket) {
		return ticket.pax() == pax;
	});
	show("    Из коллекции выбраны заявка/заявки пассажира "s + pax + ":"s, result);
} // App::doFindbyPax


// Упорядочить заявки по идентификатору
void App::doOrderById() {
	showNavBarMessage(hintColor, "");

	tickets_.sort([](const Ticket& t1, const Ticket& t2) {
		return t1.id() < t2.id();
	});
	show("    Завявки упорядочены по идентификаторам:");
} // App::doOrderById


// Упорядочить заявки по желаемой дате вылета
void App::doOrderByDepartureDate() {
	showNavBarMessage(hintColor, "  Упорядочить заявки по желаемой дате вылета");
	
	tickets_.sort([](const Ticket& t1, const Ticket& t2) {
		return t1.departureDate() < t2.departureDate();
	});
	show("    Заявки упорядочены по желаемой дате вылета:");
} // App::doOrderByDepartureDate


// Упорядочить заявки по пункту назначения
void App::doOrderByDestination() {
	showNavBarMessage(hintColor, "  Упорядочить заявки по пункту назначения");

	tickets_.sort([](const Ticket& t1, const Ticket& t2) {
		return t1.destination() < t2.destination();
	});
	show("    Заявки упорядочены по пункту назначения:");
} // App::doOrderByDestination


// Запись коллекции заявок на авиабилеты в бинарный файл
void App::doSaveToBinary() {
	showNavBarMessage(hintColor, "  Запись коллекции заявок на авиабилеты в бинарный файл");
	
	save();
	show("    Коллекция сохранена в бинарный файл '" + fileName_ + "':");
} // App::doSaveToBinary


// Чтение коллекции заявок на авиабилеты из бинарного файла
void App::doLoadFrombinary() {
	showNavBarMessage(hintColor, "");

	load();
	show("    Коллекция восстановлнена из бинарного файла '" + fileName_ + "':");
} // App::doLoadFrombinary


// Обмен первой и последней записи в бинарном файле
void App::doFirstLastSwap() {
	showNavBarMessage(hintColor, "Обмен первой и последней записи в бинарном файле");

	// загрузить и показать данные в файле до обмена
	load();
	show("    Данные в файле до обмена первой и последней записей:");
	firstLastSwap();
	
	// загрузить и показать данные в файле после обмена
	load();
	show("\n\n    Данные в файле после обмена первой и последней записей:");
} // App::doFirstLastSwap


// Обмен первых записей с самыми ранними и поздними датами
void App::doEarliestLatestSwap() {
	showNavBarMessage(hintColor, "  Обмен первых записей с самыми ранними и поздними датами");

	// загрузить данные из файла до обмена
	load();
	show("    Данные в файле до обмена самой ранней и самой поздней записей:");
	
	// обмен по заданию
	earliestLatestSwap();

	// загрузить и показать данные в файле после обмена
	load();
	show("\n\n    Данные в файле после обмена самой ранней и самой поздней записей:");
} // App::doEarliestLatestSwap
#pragma endregion
