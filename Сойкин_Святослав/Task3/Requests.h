#pragma once
#include "pch.h"
#include "Request.h"

class Requests {
    list<Request> list_;
    int nextId_ = 1;

public:
    Requests();

    void addRequest();
    void deleteById(int id);
    list<Request> selectByFlight(const string& flight);
    list<Request> selectByDate(const Date& date);
    list<Request> selectByPassenger(const string& pass);
    void sortById();
    void sortByDate();
    void sortByDestination();
    void changeRequest(int id);  // фабричным

    const list<Request>& getList() const { return list_; }

    void saveToBinaryFixed(const string& fname) const;
    void loadFromBinaryFixed(const string& fname);

    void swapFirstLastInFile(const string& fname);
    void swapEarliestLatestInFile(const string& fname);
};