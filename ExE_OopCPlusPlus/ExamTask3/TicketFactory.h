#pragma once
#include "pch.h"
#include "Ticket.h"
#include "FlightSeeder.h"

// Фабрика генерации тестовых данных пр заявкам
class TicketFactory
{
	static const vector<FlightSeeder> flights_;
	static const vector<string> paxes_;

public:
	static Ticket create(int idSeed);

	// list по заданию
	static list<Ticket> create(int idSeed, int n);
};
