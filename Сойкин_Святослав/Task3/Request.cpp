#include "Request.h"
#include "Utils.h"
#include <cctype>

// Helper to validate flight format PO-xxxxK
static bool isValidFlightNum(const string& flight) {
    if (flight.length() != 8) return false;
    if (flight[0] != 'P' || flight[1] != 'O' || flight[2] != '-') return false;
    if (flight[7] != 'K') return false;
    for (int i = 3; i < 7; ++i) {
        if (!isdigit(flight[i])) return false;
    }
    return true;
}

// Manual input with validation
Request Request::createFromInput(int id) {
    Request r;
    r.id = id;

    // Input destination
    cout << "    ����� ����������: " << color(infoColor);
    string dest;
    getline(cin, dest);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        throw exception("Error reading destination");
    }
    if (dest.empty() || dest.length() > 30) {
        throw exception("Destination empty or too long (max 30 chars)");
    }
    strncpy(r.destination, dest.c_str(), 30);
    r.destination[30] = '\0';

    // Input flight number (format: PO-xxxxK)
    cout << color(mainColor) << "    ����: " << color(infoColor);
    string flight;
    getline(cin, flight);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        throw exception("Error reading flight number");
    }
    if (!isValidFlightNum(flight)) {
        throw exception("Invalid flight format. Expected: PO-xxxxK (e.g., PO-2212K)");
    }
    strncpy(r.flightNum, flight.c_str(), 15);
    r.flightNum[15] = '\0';

    // Input passenger (format: FirstName I.I.)
    cout << color(mainColor) << "    ��������: " << color(infoColor);
    string pass;
    getline(cin, pass);
    if (cin.fail()) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        throw exception("Error reading passenger name");
    }
    if (pass.empty() || pass.length() > 30) {
        throw exception("Passenger name empty or too long (max 30 chars)");
    }
    strncpy(r.passenger, pass.c_str(), 30);
    r.passenger[30] = '\0';

    // Input date (day month year)
    cout << color(mainColor) << "    ����: ";
    short day, month, year;
    if (!(cin >> day >> month >> year)) {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail(), '\n');
        throw exception("Invalid date format. Expected: day month year (e.g., 15 2 2026)");
    }
    cin.ignore(cin.rdbuf()->in_avail(), '\n');

    // Validate date ranges
    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2100) {
        throw exception("Invalid date values. day=[1-31], month=[1-12], year=[1900-2100]");
    }

    try {
        r.date.setDate(day, month, year);
    } catch (const exception& e) {
        throw exception(("Date error: " + string(e.what())).c_str());
    }

    cout << color(mainColor);
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

    // Ensure null-termination (in case source used full-length strings)
    out.destination[30] = '\0';
    out.flightNum[15] = '\0';
    out.passenger[30] = '\0';

    out.date.setDate(day, month, year);
    return true;
}