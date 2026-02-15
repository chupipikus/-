#pragma once
#include "pch.h"
#include "Payers.h"

class App {
private:
    Payers payers_;
    string csvFile_ = "task4_payers.csv";

public:
    App();

    void printList(const list<Payer>& lst, const string& title) const;

    void doAddPayer();
    void doDeleteById();
    void doSelectByTariff();
    void doSelectByDiscount();
    void doSelectBySumRange();
    void doSortById();
    void doSortByName();
    void doSortBySumDescending();
    void doChangePayer();
    void doSaveToCSV();
    void doLoadFromCSV();
};