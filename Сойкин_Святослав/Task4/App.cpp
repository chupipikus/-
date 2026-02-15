#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Payer>& lst, const string& title) const {

    const int consoleWidth = static_cast<int>(getConsoleSize().X);
    const int totalWidth = max(40, consoleWidth - 16);

    // fixed column sizes
    const int colRow = 4;   // index
    const int colId = 4;
    const int colPhone = 12;
    const int colTariff = 8;
    const int colDisc = 4;
    const int colMin = 5;
    const int colDate = 10;
    const int colSum = 10;

    int fixedCols = colRow + colId + colPhone + colTariff + colDisc + colMin + colDate + colSum + 9; // separators
    int nameCol = max(6, totalWidth - fixedCols);

    auto fit = [](const string& s, int maxLen) {
        if (maxLen <= 0) return string();
        if ((int)s.size() <= maxLen) return s;
        if (maxLen <= 3) return string(maxLen, '.');
        return s.substr(0, maxLen - 3) + "...";
    };

    cout << "     " << title << "\n"

    // header
         << " "
         << left << setw(colRow - 1) << "#" << " | "
         << left << setw(colId) << "ID" << " | "
         << left << setw(nameCol) << "Name" << " | "
         << left << setw(colPhone) << "Phone" << " | "
         << right << setw(colTariff) << "Tariff" << " | "
         << right << setw(colDisc) << "Disc" << " | "
         << right << setw(colMin) << "Min" << " | "
         << left << setw(colDate) << "Date" << " | "
         << right << setw(colSum) << "Sum" << "\n"

         << string(totalWidth + 16, '-') << "\n";

    int row = 1;
    for (const auto& p : lst) {
        cout << " "
             << left << setw(colRow - 1) << row++ << " | "
             << left << setw(colId) << p.getId() << " | "
             << left << setw(nameCol) << fit(p.getName(), nameCol) << " | "
             << left << setw(colPhone) << fit(p.getPhone(), colPhone) << " | ";

        ostringstream ssum;
        ssum << fixed << setprecision(2) << p.calculateSum();

        cout << right << setw(colTariff) << fixed << setprecision(2) << p.getTariff() << " | "
             << right << setw(colDisc) << p.getDiscount() << " | "
             << right << setw(colMin) << p.getTimeMin() << " | "
             << left << setw(colDate) << p.getDate().toString() << " | "
             << right << setw(colSum) << ssum.str() << "\n";
    }

    cout << string(totalWidth + 16, '-') << "\n";
}

void App::doAddPayer() {
    cls();
    showNavBarMessage(hintColor, "    Add new payer");
    printList(payers_.getList(), "Current payers");

    cout << "\n    Enter new payer data:\n";
    try {
        payers_.addPayerFromKeyboard();
        cout << color(sumColor) << "    Payer added successfully\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Updated payers list");
}

void App::doDeleteById() {
    cls();
    showNavBarMessage(hintColor, "    Delete payer by ID");
    printList(payers_.getList(), "Current payers");

    if (payers_.getList().empty()) {
        cout << color(errColor) << "    No payers\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Enter payer ID to delete: " << color(infoColor);
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor) << color(errColor) << "    Invalid ID input\n" << color(mainColor);
        getKey();
        return;
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);

    try {
        payers_.deleteById(id);
        cout << color(sumColor) << "    Payer ID " << id << " deleted\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Updated payers list");
}

void App::doSelectByPhone() {
    cls();
    showNavBarMessage(hintColor, "    Select payers by phone number");
    printList(payers_.getList(), "Current payers");

    if (payers_.getList().empty()) {
        cout << color(errColor) << "    No payers\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Enter phone number (format 062-xxx): " << color(infoColor);
    string phone;
    getline(cin, phone);
    cout << color(mainColor);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(errColor) << "    Invalid input\n" << color(mainColor);
        getKey();
        return;
    }

    if (phone.empty()) {
        cout << color(errColor) << "    Phone number cannot be empty\n" << color(mainColor);
        getKey();
        return;
    }

    auto res = payers_.selectByPhone(phone);
    if (res.empty()) {
        cout << "    No payers found for phone: " << phone << "\n";
    } else {
        printList(res, "Payers for phone " + phone);
    }
    getKey();
}

void App::doSelectByName() {
    cls();
    showNavBarMessage(hintColor, "    Select payers by name");
    printList(payers_.getList(), "Current payers");

    if (payers_.getList().empty()) {
        cout << color(errColor) << "    No payers\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Enter name/initials: " << color(infoColor);
    string name;
    getline(cin, name);
    cout << color(mainColor);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(errColor) << "    Invalid input\n" << color(mainColor);
        getKey();
        return;
    }

    if (name.empty()) {
        cout << color(errColor) << "    Name cannot be empty\n" << color(mainColor);
        getKey();
        return;
    }

    auto res = payers_.selectByName(name);
    if (res.empty()) {
        cout << "    No payers found for name: " << name << "\n";
    } else {
        printList(res, "Payers for name " + name);
    }
    getKey();
}

void App::doSelectByDate() {
    cls();
    showNavBarMessage(hintColor, "    Select payers by payment date");
    printList(payers_.getList(), "Current payers");

    if (payers_.getList().empty()) {
        cout << color(errColor) << "    No payers\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Enter date (day month year): " << color(infoColor);
    short day, month, year;
    if (!(cin >> day >> month >> year)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor) << color(errColor) << "    Invalid date input\n" << color(mainColor);
        getKey();
        return;
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        cout << color(errColor) << "    Invalid date range: day=[1-31], month=[1-12], year=[1900-2100]\n" << color(mainColor);
        getKey();
        return;
    }

    try {
        Date date(day, month, year);
        auto res = payers_.selectByDate(date);
        if (res.empty()) {
            cout << "    No payers found for date: " << date.toString() << "\n";
        } else {
            printList(res, "Payers for date " + date.toString());
        }
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }
    getKey();
}

void App::doSelectBySumRange() {
    cls();
    showNavBarMessage(hintColor, "    Select payers by sum range");
    printList(payers_.getList(), "Current payers");

    if (payers_.getList().empty()) {
        cout << color(errColor) << "    No payers\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Enter sum range (low high): " << color(infoColor);
    double low, high;
    if (!(cin >> low >> high)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor) << color(errColor) << "    Invalid input\n" << color(mainColor);
        getKey();
        return;
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);

    if (low < 0 || high < 0 || low > high) {
        cout << color(errColor) << "    Invalid range\n" << color(mainColor);
        getKey();
        return;
    }

    auto res = payers_.selectBySumRange(low, high);
    if (res.empty()) {
        cout << "    No payers found in range " << low << " - " << high << "\n";
    } else {
        printList(res, "Payers in sum range " + to_string(static_cast<int>(low)) + "-" + to_string(static_cast<int>(high)));
    }
    getKey();
}

void App::doTotalPayments() {
    cls();
    showNavBarMessage(hintColor, "    Total payments");
    printList(payers_.getList(), "Current payers");

    double total = payers_.totalPayments();
    cout << "\n    Total payments: " << color(sumColor) << fixed << setprecision(2) << total << color(mainColor) << "\n";

    getKey("\n    Press any key to continue...");
}

void App::doSortById() {
    cls();
    showNavBarMessage(hintColor, "    Sort payers by ID");
    printList(payers_.getList(), "Current payers");

    payers_.sortById();
    cout << color(sumColor) << "    Sorted by ID\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Sorted payers");
}

void App::doSortByPhone() {
    cls();
    showNavBarMessage(hintColor, "    Sort payers by phone");
    printList(payers_.getList(), "Current payers");

    payers_.sortByPhone();
    cout << color(sumColor) << "    Sorted by phone\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Sorted payers");
}

void App::doSortBySumDescending() {
    cls();
    showNavBarMessage(hintColor, "    Sort payers by sum (descending)");
    printList(payers_.getList(), "Current payers");

    payers_.sortBySumDescending();
    cout << color(sumColor) << "    Sorted by sum (descending)\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Sorted payers");
}

void App::doSortByTimeDescending() {
    cls();
    showNavBarMessage(hintColor, "    Sort payers by time (descending)");
    printList(payers_.getList(), "Current payers");

    payers_.sortByTimeDescending();
    cout << color(sumColor) << "    Sorted by time (descending)\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Sorted payers");
}

void App::doChangePayer() {
    cls();
    showNavBarMessage(hintColor, "    Modify payer");
    printList(payers_.getList(), "Current payers");

    if (payers_.getList().empty()) {
        cout << color(errColor) << "    No payers\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Enter payer ID to modify: " << color(infoColor);
    int id;
    if (!(cin >> id)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor) << color(errColor) << "    Invalid ID input\n" << color(mainColor);
        getKey();
        return;
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);

    cout << "\n    Generating new data (factory method):\n";
    try {
        payers_.changePayer(id);
        cout << color(sumColor) << "    Payer ID " << id << " modified\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Modified payers");
}

void App::doSaveToCSV() {
    cls();
    showNavBarMessage(hintColor, "    Save payers to CSV file");
    printList(payers_.getList(), "Current payers");

    try {
        payers_.saveToCSV(csvFile_);
        cout << color(sumColor) << "    Saved to " << csvFile_ << color(mainColor) << "\n";
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
}

void App::doLoadFromCSV() {
    cls();
    showNavBarMessage(hintColor, "    Load payers from CSV file");
    printList(payers_.getList(), "Current payers");

    try {
        payers_.loadFromCSV(csvFile_);
        cout << color(sumColor) << "    Loaded from " << csvFile_ << color(mainColor) << "\n";
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(payers_.getList(), "Loaded payers");
}
