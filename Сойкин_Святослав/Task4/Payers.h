#pragma once
#include "pch.h"
#include "Payer.h"

class Payers {
private:
    list<Payer> list_;
    int nextId_ = 1;

public:
    Payers();

    void addPayer();
    void deleteById(int id);
    list<Payer> selectByPhone(const string& phone) const;
    list<Payer> selectByName(const string& name) const;
    list<Payer> selectByTariff(double tariff) const;
    list<Payer> selectByDiscount(int discount) const;
    list<Payer> selectByDate(const Date& date) const;
    list<Payer> selectBySumRange(double low, double high) const;
    double totalPayments() const;
    void sortById();
    void sortByName();
    void sortByPhone();
    void sortBySumDescending();
    void sortByTimeDescending();
    void changePayer(int id);

    const list<Payer>& getList() const { return list_; }

    void saveToCSV(const string& fname) const;
    void loadFromCSV(const string& fname);
};