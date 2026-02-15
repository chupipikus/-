#pragma once
#include "pch.h"
#include "Requests.h"

class App {
private:
    Requests requests_;
    string binFile_ = "task3_requests.bin";

public:
    App();
    const string& getBinFile() const { return binFile_; }
    const list<Request>& getRequests() const { return requests_.getList(); }

    void doAddRequest();
    void doDeleteById();
    void doSelectByFlight();
    void doSelectByDate();
    void doSelectByPassenger();
    void doSortById();
    void doSortByDate();
    void doSortByDestination();
    void doChangeRequest();
    void doSaveToBinaryFixed();
    void doLoadFromBinaryFixed();
    void doSwapFirstLastInFile();
    void doSwapEarliestLatestInFile();

    void printList(const list<Request>& lst, const string& title) const;
};