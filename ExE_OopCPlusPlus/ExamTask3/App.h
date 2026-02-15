#pragma once
#include "pch.h"
#include "Ticket.h"

class App
{
	// коллекция заявок на авиабилеты для обработки
	list<Ticket> tickets_;

	// имя бинарного файла для хранения коллекции заввок 
	// в записях равной длины
	string fileName_;

	// запись коллекции заяок в бинарный файл
	void save();

	// чтение коллекции заяок из бинарного файла
	void load();

	// поменять местами перую и последнюю записи
	void firstLastSwap();

	// обмен самой ранней и самой поздней записей
	void earliestLatestSwap();

	// вывод коллекции заявок в кносоль
	void show(const string &title);

	// вывод выборки заявок в консоль
	void show(const string& title, list<Ticket> &data);
	void show(const string& title, vector<Ticket> &data);

public:
	App();
	App(const list<Ticket> tickets, const string &fileName);

    // Генерация коллекции заявок фабричным методом 
    void doGenerate();

   // Вывод текущего состояния коллекции заявок
   void doShowAll();

   // Добавление заявки, сформированной фабричным методом
   void doAddByFactory();

   // Удаление заявки по идентификатору
   void doDeleteById();

   // Отбор заявок по заданному номеру рейса
   void doFindByFlight();

   // Отбор заявок по фамилии и инициалам пассажира
   void doFindbyPax();

   // Упорядочить заявки по идентификатору
   void doOrderById();

   // Упорядочить заявки по желаемой дате вылета
   void doOrderByDepartureDate();

   // Упорядочить заявки по пункту назначения
   void doOrderByDestination();

   // Запись коллекции заявок на авиабилеты в бинарный файл
   void doSaveToBinary();

   // Чтение коллекции заявок на авиабилеты из бинарного файла
   void doLoadFrombinary();

   // Обмен первой и последней записи в бинарном файле
   void doFirstLastSwap();

   // Обмен первых записей с самыми ранними и поздними датами
   void doEarliestLatestSwap();
};

