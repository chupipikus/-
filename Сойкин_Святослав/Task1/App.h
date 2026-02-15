#pragma once
#include "pch.h"

class App {
    vector<float> v_;
    string binFile_;

    // steps of Task 1 implemented as separate functions
    void step_countNegative();
    void step_countOutsideInterval(float a, float b);
    void step_sumBeforeFirstMin();
    void step_sumBetweenFirstMinAndFirstMax();
    void step_selectNegatives();
    void step_selectOutsideInterval(float a, float b);
    void step_sortDescending();
    void step_sortByAbsAscending();
    void step_moveOutsideIntervalToEnd(float a, float b);

    float readFloatFromCin(const string &prompt);

    void saveToBinary() const;
    void loadFromBinary();

public:
    App();
    void run();
};
