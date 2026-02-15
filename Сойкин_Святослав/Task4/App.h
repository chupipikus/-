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
    void doSelectByPhone();
    void doSelectByName();
    void doSelectByDate();
    void doSelectBySumRange();
    void doTotalPayments();
    void doSortById();
    void doSortByPhone();
    void doSortBySumDescending();
    void doSortByTimeDescending();
    void doChangePayer();
    void doSaveToCSV();
    void doLoadFromCSV();
};