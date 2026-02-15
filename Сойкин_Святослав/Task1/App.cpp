#include "App.h"
#include "Utils.h"

App::App() : binFile_("task1_vector.bin") {
    int n = getRand(12, 30);
    v_.assign(n, 0.0f);
    for (auto &x : v_) x = getRand(-100.0f, 100.0f);
}

float App::readFloatFromCin(const string &prompt) {
    cout << prompt;
    float value;
    if (!(cin >> value)) throw std::runtime_error("Invalid input");
    return value;
}

void App::saveToBinary() const {
    ofstream out(binFile_, ios::binary | ios::out | ios::trunc);
    if (!out.is_open()) throw std::runtime_error("Unable to open file for writing");

    size_t n = v_.size();
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    if (n) out.write(reinterpret_cast<const char*>(v_.data()), n * sizeof(float));
    if (out.fail()) throw std::runtime_error("Error writing to binary file");
}

void App::loadFromBinary() {
    ifstream in(binFile_, ios::binary | ios::in);
    if (!in.is_open()) throw std::runtime_error("Unable to open binary file for reading");

    size_t n = 0;
    in.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (in.fail()) throw std::runtime_error("Error reading vector size");

    vector<float> tmp;
    if (n) {
        tmp.resize(n);
        in.read(reinterpret_cast<char*>(tmp.data()), n * sizeof(float));
        if (in.fail()) throw std::runtime_error("Error reading vector data");
    }

    v_.swap(tmp);
}

// ????? ???? ??? ????? ??? ??????
void App::displayVector(const string& title, const vector<float>& data, int itemsPerRow, bool useColor, float a, float b, int precision) {
    cout << "    " << color(resColor) << title << " (n=" << data.size() << ")\n" << color(mainColor);
    if (data.empty()) {
        cout << "    (empty)\n";
        return;
    }

    // determine min / max for coloring
    float mn = *min_element(data.begin(), data.end());
    float mx = *max_element(data.begin(), data.end());

    int counter = 0;
    for (size_t i = 0; i < data.size(); ++i) {
        float item = data[i];
        short itemColor = mainColor;
        if (useColor) {
            if (eq(item, mn)) {
                itemColor = sumColor;
            } else if (eq(item, mx)) {
                itemColor = acctColor;
            } else if (a <= item && item <= b) {
                itemColor = hintColor;
            } else {
                itemColor = mainColor;
            }
        }

        cout << "    " << color(itemColor) << setw(8) << fixed << setprecision(precision) << item
             << color(mainColor) << "  ";

        if (++counter % itemsPerRow == 0 || i == data.size() - 1) cout << "\n";
    }
}

void App::run() {
    showNavBarMessage(hintColor, "    Vector processing. 9 operations for floating-point array analysis");

    cout << "\n    Initial vector: " << color(infoColor);
    displayVector("", v_, 8);

    saveToBinary();

    float a = getRand(-50.0f, 50.0f);
    float b = a + getRand(0.0f, 100.0f);
    if (a > b) swap(a, b);

    cout << color(mainColor) << "\n    Interval [a, b]: a=" << color(acctColor) 
        << fixed << setprecision(2) << a << color(mainColor) << ", b=" << color(acctColor) 
        << b << color(mainColor) << "\n";

    cls();
    showNavBarMessage(hintColor, "    Results of 9 operations");

    cout << "\n";

    step_countNegative();
    step_countOutsideInterval(a, b);
    step_sumBeforeFirstMin();
    step_sumBetweenFirstMinAndFirstMax();

    cout << "\n";

    step_selectNegatives();
    step_selectOutsideInterval(a, b);

    // 7) sorted descending (show colored result)
    step_sortDescending();
    displayVector("", v_, 8, true, a, b);

    // restore and show 8) sorted by absolute value
    loadFromBinary();
    step_sortByAbsAscending();
    displayVector("", v_, 8, true, a, b);

    // restore and show 9) move outside interval to end
    loadFromBinary();
    step_moveOutsideIntervalToEnd(a, b);

    loadFromBinary();
    cout << "\n    " << color(resColor) << "Vector restored from file (size=" << v_.size() << ")" << color(mainColor) << "\n";
    displayVector("Original data", v_, 8, true, a, b);
}

void App::step_countNegative() {
    const auto negCount = count_if(v_.begin(), v_.end(), [](float x){ return x < 0.0f; });
    cout << "    1) Count of negative elements: " << color(sumColor) << setw(6) << negCount << color(mainColor) << "\n";
}

void App::step_countOutsideInterval(float a, float b) {
    const auto notInInterval = count_if(v_.begin(), v_.end(), [a,b](float x){ return x < a || x > b; });
    cout << "    2) Count outside [a,b]: " << color(sumColor) << setw(6) << notInInterval << color(mainColor) << "\n";
}

void App::step_sumBeforeFirstMin() {
    const auto itMin = min_element(v_.begin(), v_.end());
    const float sumBeforeMin = (itMin == v_.begin() || itMin == v_.end()) ? 0.0f : accumulate(v_.begin(), itMin, 0.0f);
    cout << "    3) Sum before min: " << color(sumColor) << fixed << setprecision(3) << setw(10) << sumBeforeMin << color(mainColor) << "\n";
}

void App::step_sumBetweenFirstMinAndFirstMax() {
    const auto itMin = min_element(v_.begin(), v_.end());
    const auto itMax = max_element(v_.begin(), v_.end());
    float sumBetween = 0.0f;
    if (itMin != v_.end() && itMax != v_.end() && itMin != itMax) {
        auto first = min(itMin, itMax);
        auto last = max(itMin, itMax);
        if (distance(first, last) > 1) sumBetween = accumulate(next(first), last, 0.0f);
    }
    cout << "    4) Sum between min and max: " << color(sumColor) << fixed << setprecision(3) << setw(10) << sumBetween << color(mainColor) << "\n";
}

void App::step_selectNegatives() {
    vector<float> negatives;
    copy_if(v_.begin(), v_.end(), back_inserter(negatives), [](float x){ return x < 0.0f; });
    cout << "\n    5) Negative elements selected:\n";
    if (!negatives.empty()) {
        displayVector("", negatives, 8);
    } else {
        cout << "    (empty)\n";
    }
}

void App::step_selectOutsideInterval(float a, float b) {
    vector<float> outside;
    copy_if(v_.begin(), v_.end(), back_inserter(outside), [a,b](float x){ return x < a || x > b; });
    cout << "\n    6) Elements outside [a,b]:\n";
    if (!outside.empty()) {
        displayVector("", outside, 8);
    } else {
        cout << "    (empty)\n";
    }
}

void App::step_sortDescending() {
    sort(v_.begin(), v_.end(), greater<float>());
    cout << "\n    7) Sorted descending:\n";
}

void App::step_sortByAbsAscending() {
    sort(v_.begin(), v_.end(), [](float lhs, float rhs){ return fabs(lhs) < fabs(rhs); });
    cout << "\n    8) Sorted by absolute value:\n";
}

void App::step_moveOutsideIntervalToEnd(float a, float b) {
    stable_partition(v_.begin(), v_.end(), [a,b](float x){ return x >= a && x <= b; });
    cout << "\n    9) Elements outside [a,b] moved to end:\n";
    displayVector("", v_, 8, true, a, b);
}
