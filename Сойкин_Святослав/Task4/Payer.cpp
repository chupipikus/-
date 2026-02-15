#include "Payer.h"
#include "Utils.h"
#include <sstream>

Payer Payer::createFactory(int id) {
    Payer p;
    p.setId(id);
    p.setName("Payer " + to_string(getRand(1, 20)));
    p.setPhone("062-" + to_string(getRand(121, 333)));
    p.setTariff(getRand(1.0, 5.0));
    p.setDiscount(getRand(0, 20));
    p.setTimeMin(getRand(10, 200));
    p.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));
    return p;
}

Payer Payer::createFromInput(int id) {
    Payer p;
    p.setId(id);

    cout << "    Enter name and initials: " << color(infoColor);
    string name;
    getline(cin, name);
    cout << color(mainColor);
    if (cin.fail() || name.empty()) {
        throw exception("Invalid name input");
    }
    if (name.length() >= 31) {
        throw exception("Name too long (max 30 chars)");
    }
    p.setName(name);

    cout << "    Enter phone number (format 062-xxx, 121<=xxx<=333): " << color(infoColor);
    string phone;
    getline(cin, phone);
    cout << color(mainColor);
    if (phone.empty()) {
        throw exception("Invalid phone number");
    }
    
    if (phone.size() != 8 || phone.substr(0, 4) != "062-") {
        throw exception("Invalid phone format (expected 062-xxx)");
    }
    int gats = atoi(phone.substr(4).c_str());
    if (gats < 121 || gats > 333) {
        throw exception("Invalid GATS number (must be 121-333)");
    }
    p.setPhone(phone);

    cout << "    Enter tariff (cost per minute): " << color(infoColor);
    double tariff;
    if (!(cin >> tariff)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor);
        throw exception("Invalid tariff input");
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);
    if (tariff <= 0) {
        throw exception("Tariff must be positive");
    }
    p.setTariff(tariff);

    cout << "    Enter discount (0-100%): " << color(infoColor);
    int discount;
    if (!(cin >> discount)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor);
        throw exception("Invalid discount input");
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);
    if (discount < 0 || discount > 100) {
        throw exception("Discount must be 0-100");
    }
    p.setDiscount(discount);

    cout << "    Enter time in minutes: " << color(infoColor);
    int timeMin;
    if (!(cin >> timeMin)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor);
        throw exception("Invalid time input");
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);
    if (timeMin <= 0) {
        throw exception("Time must be positive");
    }
    p.setTimeMin(timeMin);

    cout << "    Enter date (day month year): " << color(infoColor);
    short day, month, year;
    if (!(cin >> day >> month >> year)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        cout << color(mainColor);
        throw exception("Invalid date format");
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');
    cout << color(mainColor);

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        throw exception("Invalid date range: day=[1-31], month=[1-12], year=[1900-2100]");
    }
    p.setDate(day, month, year);

    return p;
}

string Payer::toString() const {
    ostringstream oss;
    oss << "ID: " << getId() << ", ���: " << getName() << ", �������: " << getPhone()
        << ", �����: " << fixed << setprecision(2) << getTariff() << ", ������: " << getDiscount()
        << ", ������: " << getTimeMin() << ", ����: " << getDate().toString() << ", �����: " << calculateSum();
    return oss.str();
}