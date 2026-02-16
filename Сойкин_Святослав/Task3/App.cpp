#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Request>& lst, const string& title) const {
    cout << "    " << title << "\n"
        << "    +" << setfill('-') << setw(112) << "-" << "+"
        << setfill(' ') << "\n";

    int row = 1;
    for (const auto& r : lst) {
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
            << " | ID: " << setw(2) << r.id
            << " | Destination: " << setw(19) << r.destination
            << " | Flight: " << setw(8) << r.flightNum
            << " | Passenger: " << setw(15) << r.passenger
            << " | Date: " << r.date.toString() << " |\n";
    }
    cout << "    +" << setfill('-') << setw(112) << "-" << "+"
        << setfill(' ') << "\n";
}

void App::doAddRequest() {
    cls();
    showNavBarMessage(hintColor, "    Add new flight ticket request");
    printList(getRequests(), "Current requests");

    cout << "\n    Введите данные новой заявки:\n";
    try {
        requests_.addRequest();
        cout << color(sumColor) << "    Request added successfully\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Updated requests list");
}

void App::doDeleteById() {
    cls();
    showNavBarMessage(hintColor, "    Delete request by ID");
    printList(getRequests(), "Current requests");

    if (getRequests().empty()) {
        cout << color(errColor) << "    No requests\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Введите ID заявки для удаления: " << color(infoColor);
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
        requests_.deleteById(id);
        cout << color(sumColor) << "    Request ID " << id << " deleted\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Updated requests list");
}

void App::doSelectByFlight() {
    cls();
    showNavBarMessage(hintColor, "    Select requests by flight number");
    printList(getRequests(), "Current requests");

    if (getRequests().empty()) {
        cout << color(errColor) << "    No requests\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Введите номер рейса (формат PO-xxxxK): " << color(infoColor);
    string flight;
    getline(cin, flight);
    cout << color(mainColor);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(errColor) << "    Invalid input\n" << color(mainColor);
        getKey();
        return;
    }

    if (flight.empty()) {
        cout << color(errColor) << "    Flight number cannot be empty\n" << color(mainColor);
        getKey();
        return;
    }

    auto res = requests_.selectByFlight(flight);
    if (res.empty()) {
        cout << "    No requests found for flight: " << flight << "\n";
    } else {
        printList(res, "Requests for flight " + flight);
    }
    getKey();
}

void App::doSelectByDate() {
    cls();
    showNavBarMessage(hintColor, "    Select requests by date");
    printList(getRequests(), "Current requests");

    if (getRequests().empty()) {
        cout << color(errColor) << "    No requests\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Введите дату (день месяц год): " << color(infoColor);
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
        auto res = requests_.selectByDate(date);
        if (res.empty()) {
            cout << "    No requests found for date: " << date.toString() << "\n";
        } else {
            printList(res, "Requests for date " + date.toString());
        }
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }
    getKey();
}

void App::doSelectByPassenger() {
    cls();
    showNavBarMessage(hintColor, "    Select requests by passenger name");
    printList(getRequests(), "Current requests");

    if (getRequests().empty()) {
        cout << color(errColor) << "    No requests\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Введите имя пассажира: " << color(infoColor);
    string pass;
    getline(cin, pass);
    cout << color(mainColor);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(errColor) << "    Invalid input\n" << color(mainColor);
        getKey();
        return;
    }

    if (pass.empty()) {
        cout << color(errColor) << "    Passenger name cannot be empty\n" << color(mainColor);
        getKey();
        return;
    }

    auto res = requests_.selectByPassenger(pass);
    if (res.empty()) {
        cout << "    No requests found for passenger: " << pass << "\n";
    } else {
        printList(res, "Requests for passenger " + pass);
    }
    getKey();
}

void App::doSortById() {
    cls();
    showNavBarMessage(hintColor, "    Sort requests by ID");
    printList(getRequests(), "Current requests");

    requests_.sortById();
    cout << color(sumColor) << "    Sorted by ID\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Sorted requests");
}

void App::doSortByDate() {
    cls();
    showNavBarMessage(hintColor, "    Sort requests by date");
    printList(getRequests(), "Current requests");

    requests_.sortByDate();
    cout << color(sumColor) << "    Sorted by date\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Sorted requests");
}

void App::doSortByDestination() {
    cls();
    showNavBarMessage(hintColor, "    Sort requests by destination");
    printList(getRequests(), "Current requests");

    requests_.sortByDestination();
    cout << color(sumColor) << "    Sorted by destination\n" << color(mainColor);

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Sorted requests");
}

void App::doChangeRequest() {
    cls();
    showNavBarMessage(hintColor, "    Modify request");
    printList(getRequests(), "Current requests");

    if (getRequests().empty()) {
        cout << color(errColor) << "    No requests\n" << color(mainColor);
        getKey();
        return;
    }

    cout << "\n    Введите ID заявки для изменения: " << color(infoColor);
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

    cout << "\n    Введите данные новой заявки:\n";
    try {
        requests_.changeRequest(id);
        cout << color(sumColor) << "    Request ID " << id << " modified\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Modified requests");
}

void App::doSaveToBinaryFixed() {
    cls();
    showNavBarMessage(hintColor, "    Save requests to binary file");
    printList(getRequests(), "Current requests");

    try {
        requests_.saveToBinaryFixed(binFile_);
        cout << color(sumColor) << "    Saved to " << binFile_ << color(mainColor) << "\n";
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Current requests");
}

void App::doLoadFromBinaryFixed() {
    cls();
    showNavBarMessage(hintColor, "    Load requests from binary file");
    printList(getRequests(), "Current requests");

    try {
        requests_.loadFromBinaryFixed(binFile_);
        cout << color(sumColor) << "    Loaded from " << binFile_ << color(mainColor) << "\n";
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Loaded requests");
}

void App::doSwapFirstLastInFile() {
    cls();
    showNavBarMessage(hintColor, "    Swap first and last records in file");
    printList(getRequests(), "Current requests");

    try {
        requests_.swapFirstLastInFile(binFile_);
        cout << color(sumColor) << "    First and last records swapped in file\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Current requests");
}

void App::doSwapEarliestLatestInFile() {
    cls();
    showNavBarMessage(hintColor, "    Swap earliest/latest date records in file");
    printList(getRequests(), "Current requests");

    try {
        requests_.swapEarliestLatestInFile(binFile_);
        cout << color(sumColor) << "    Earliest/latest date records swapped in file\n" << color(mainColor);
    } catch (const exception& e) {
        cout << color(errColor) << "    Error: " << e.what() << color(mainColor) << "\n";
    }

    getKey("\n    Press any key to continue...");
    cls();
    printList(getRequests(), "Current requests");
}
