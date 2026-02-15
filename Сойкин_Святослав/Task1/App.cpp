#include "App.h"
#include "Utils.h"

// ������ ��� ���������� ������ ������
static void displayVector(const vector<float>& v, float a = 0.0f, float b = 0.0f, 
                          bool useRange = false, int itemsPerRow = 8) {
    if (v.empty()) {
        cout << color(infoColor) << "    [������ ����]" << color(mainColor) << "\n";
        return;
    }

    const float minVal = *min_element(v.begin(), v.end());
    const float maxVal = *max_element(v.begin(), v.end());

    cout << fixed << setprecision(2);
    int counter = 0;
    
    for (const auto& item : v) {
        // ���� ������ ��������
        short itemColor = mainColor;
        
        if (eq(item, minVal)) {
            itemColor = sumColor;  // ����������� - ����
        } else if (eq(item, maxVal)) {
            itemColor = acctColor; // ������� - ����
        } else if (useRange && item >= a && item <= b) {
            itemColor = hintColor; // ����� ���� ������
        }
        
        cout << color(itemColor) << setw(8) << item << color(mainColor) << "  ";
        
        if (++counter % itemsPerRow == 0) {
            cout << "\n    ";
        }
    }
    
    if (counter % itemsPerRow != 0) {
        cout << "\n";
    }
}

// App: ���������� ������� ��� ������� 1

App::App() : binFile_("task1_vector.bin") {
    // ������ ������ ������� [12,30] � ���������������� ����������
    int n = getRand(12, 30);
    v_.assign(n, 0.0f);
    for (auto &x : v_) x = getRand(-100.0f, 100.0f);
}

// ������ ������ ����� � ��������� ������� ����� (�������� ��������)
float App::readFloatFromCin(const string &prompt) {
    // kept for compatibility but not used in automated run
    cout << prompt;
    float value;
    if (!(cin >> value)) throw std::runtime_error("Invalid input");
    return value;
}

void App::saveToBinary() const {
    ofstream out(binFile_, ios::binary | ios::out | ios::trunc);
    if (!out.is_open()) throw std::runtime_error("�� ������� ������� ���� ��� ������");

    size_t n = v_.size();
    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    if (n) out.write(reinterpret_cast<const char*>(v_.data()), n * sizeof(float));
    if (out.fail()) throw std::runtime_error("������ ������ � �������� ����");
}

void App::loadFromBinary() {
    ifstream in(binFile_, ios::binary | ios::in);
    if (!in.is_open()) throw std::runtime_error("�� ������� ������� ���� ��� ������");

    size_t n = 0;
    in.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (in.fail()) throw std::runtime_error("������ ������ ������� �� ��������� �����");

    vector<float> tmp;
    if (n) {
        tmp.resize(n);
        in.read(reinterpret_cast<char*>(tmp.data()), n * sizeof(float));
        if (in.fail()) throw std::runtime_error("������ ������ ������ �� ��������� �����");
    }

    v_.swap(tmp);
}

void App::run() {
    init(L"Task 1: Vector processing");
    
    cout << "\n" << color(headerColor) 
         << "    ========== ORIGINAL VECTOR ==========" << color(mainColor) << "\n";
    cout << "    Array size: " << color(hintColor) << v_.size() << color(mainColor) << " elements\n\n    ";
    displayVector(v_, 0, 0, false, 8);
    
    saveToBinary();

    float a = getRand(-50.0f, 50.0f);
    float b = a + getRand(0.0f, 100.0f);
    if (a > b) swap(a, b);
    
    cout << "\n" << color(acctColor) << "    Search parameters: " << color(mainColor)
         << "[a = " << fixed << setprecision(2) << a << "; b = " << b << "]\n\n";

    cout << "    1) Count negative elements............: ";
    step_countNegative();
    
    cout << "    2) Count elements outside [a, b].....: ";
    step_countOutsideInterval(a, b);
    
    cout << "    3) Sum before first minimum.........: ";
    step_sumBeforeFirstMin();
    
    cout << "    4) Sum between min and max.........: ";
    step_sumBetweenFirstMinAndFirstMax();
    
    cout << "\n    5) Selection - Negative elements:\n    ";
    step_selectNegatives();
    
    cout << "\n    6) Selection - Elements outside [a, b]:\n    ";
    step_selectOutsideInterval(a, b);
    
    cout << "\n    7) Sort descending:\n    ";
    step_sortDescending();
    
    loadFromBinary();
    cout << "\n    8) Sort by absolute value:\n    ";
    step_sortByAbsAscending();
    
    loadFromBinary();
    cout << "\n    9) Move outside-range elements to end:\n    ";
    step_moveOutsideIntervalToEnd(a, b);

    loadFromBinary();
    cout << "\n" << color(headerColor) 
         << "    ========== RESTORED FROM FILE ==========" << color(mainColor) << "\n    ";
    displayVector(v_, a, b, true, 8);
    
    cout << "\n" << color(sumColor) << "    [Array restored successfully, size: " 
         << v_.size() << "]" << color(mainColor) << "\n\n";
}

// Step implementations
void App::step_countNegative() {
    const auto negCount = count_if(v_.begin(), v_.end(), [](float x){ return x < 0.0f; });
    cout << color(sumColor) << negCount << color(mainColor) << "\n";
}

void App::step_countOutsideInterval(float a, float b) {
    const auto notInInterval = count_if(v_.begin(), v_.end(), [a,b](float x){ return x < a || x > b; });
    cout << color(sumColor) << notInInterval << color(mainColor) << "\n";
}

void App::step_sumBeforeFirstMin() {
    const auto itMin = min_element(v_.begin(), v_.end());
    const float sumBeforeMin = (itMin == v_.begin() || itMin == v_.end()) ? 0.0f : accumulate(v_.begin(), itMin, 0.0f);
    cout << color(sumColor) << fixed << setprecision(2) << sumBeforeMin << color(mainColor) << "\n";
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
    cout << color(sumColor) << fixed << setprecision(2) << sumBetween << color(mainColor) << "\n";
}

void App::step_selectNegatives() {
    vector<float> negatives;
    copy_if(v_.begin(), v_.end(), back_inserter(negatives), [](float x){ return x < 0.0f; });
    cout << color(resColor) << "Count: " << negatives.size() << color(mainColor) << "\n    ";
    if (!negatives.empty()) {
        displayVector(negatives, 0.0f, 0.0f, false, 8);
    } else {
        cout << color(infoColor) << "[empty]" << color(mainColor) << "\n";
    }
}

void App::step_selectOutsideInterval(float a, float b) {
    vector<float> outside;
    copy_if(v_.begin(), v_.end(), back_inserter(outside), [a,b](float x){ return x < a || x > b; });
    cout << color(resColor) << "Count: " << outside.size() << color(mainColor) << "\n    ";
    if (!outside.empty()) {
        displayVector(outside, a, b, true, 8);
    } else {
        cout << color(infoColor) << "[empty]" << color(mainColor) << "\n";
    }
}

void App::step_sortDescending() {
    sort(v_.begin(), v_.end(), greater<float>());
    displayVector(v_, 0.0f, 0.0f, false, 8);
}

void App::step_sortByAbsAscending() {
    sort(v_.begin(), v_.end(), [](float lhs, float rhs){ return fabs(lhs) < fabs(rhs); });
    displayVector(v_, 0.0f, 0.0f, false, 8);
}

void App::step_moveOutsideIntervalToEnd(float a, float b) {
    stable_partition(v_.begin(), v_.end(), [a,b](float x){ return x >= a && x <= b; });
    displayVector(v_, a, b, true, 8);
}
