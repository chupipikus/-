#include "Request.h"
#include "Utils.h"

Request Request::createFactory(int id) {
    Request r;
    r.id = id;
    string dest = "����� ���������� " + to_string(getRand(1, 15));
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";
    string pass = "������ " + to_string(getRand(1, 30)) + " �.�.";
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));

    strncpy(r.destination, dest.c_str(), 30); r.destination[30] = '\0';
    strncpy(r.flightNum, flight.c_str(), 15); r.flightNum[15] = '\0';
    strncpy(r.passenger, pass.c_str(), 30); r.passenger[30] = '\0';
    r.date = d;
    return r;
}
    if (dest.length() >= 31) {
        throw exception("Destination too long (max 30 chars)");
    }
    strncpy(r.destination, dest.c_str(), 30);
    r.destination[30] = '\0';

    cout << "    Enter flight number (format PO-xxxxK): " << color(infoColor);
    string flight;
    getline(cin, flight);
    cout << color(mainColor);
    if (cin.fail() || flight.empty()) {
        throw exception("Invalid flight number input");
    }
    if (flight.length() >= 16) {
        throw exception("Flight number too long (max 15 chars)");
    }
    strncpy(r.flightNum, flight.c_str(), 15);
    r.flightNum[15] = '\0';

    cout << "    Enter passenger name: " << color(infoColor);
    string pass;
    getline(cin, pass);
    cout << color(mainColor);
    if (cin.fail() || pass.empty()) {
        throw exception("Invalid passenger input");
    }
    if (pass.length() >= 31) {
        throw exception("Passenger name too long (max 30 chars)");
    }
    strncpy(r.passenger, pass.c_str(), 30);
    r.passenger[30] = '\0';

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

    r.date.setDate(day, month, year);
    return r;
}
string Request::toString() const {
    ostringstream oss;
    oss << "ID: " << id << ", ����� ����������: " << destination << ", ����: " << flightNum
        << ", ��������: " << passenger << ", ����: " << date.toString();
    return oss.str();
}

void Request::writeBinary(ostream& os) const {
    os.write(reinterpret_cast<const char*>(&id), sizeof(id));
    os.write(destination, 31);
    os.write(flightNum, 16);
    os.write(passenger, 31);
    short day = date.getDay();
    short month = date.getMonth();
    short year = date.getYear();
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

bool Request::readBinary(istream& is, Request& out) {
    if (!is.read(reinterpret_cast<char*>(&out.id), sizeof(out.id))) return false;
    if (!is.read(out.destination, 31)) return false;
    if (!is.read(out.flightNum, 16)) return false;
    if (!is.read(out.passenger, 31)) return false;
    short day, month, year;
    if (!is.read(reinterpret_cast<char*>(&day), sizeof(day))) return false;
    if (!is.read(reinterpret_cast<char*>(&month), sizeof(month))) return false;
    if (!is.read(reinterpret_cast<char*>(&year), sizeof(year))) return false;

    out.destination[30] = '\0';
    out.flightNum[15] = '\0';
    out.passenger[30] = '\0';

    out.date.setDate(day, month, year);
    return true;
}