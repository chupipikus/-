#pragma once
#include "pch.h"
#include "TextProcessor.h"

class App {
    string fileName_;

    void viewText(const string& title, const string& fname); // overload for new files
    void show(const string& title, const map<string, double>& freqDict);

public:
    App();
    App(const string& fileName);

    void doFreqDictWords();
    void doFreqDictLetters();
    void doSwapLines();
    void doWordsCapitalize();
    void doOrderByLen();
    void doOrderWordsInLines();
};