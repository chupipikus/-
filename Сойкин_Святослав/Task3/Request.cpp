#include "Request.h"
#include "Utils.h"

Request Request::createFactory(int id) {
    Request r;
    r.id = id;
    string dest = "Пункт назначения " + to_string(getRand(1, 15));
    string flight = "PO-" + to_string(getRand(1000, 9999)) + "K";
    string pass = "Иванов " + to_string(getRand(1, 30)) + " П.О.";
    Date d;
    d.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));

    strncpy(r.destination, dest.c_str(), 30); r.destination[30] = '\0';
    strncpy(r.flightNum, flight.c_str(), 15); r.flightNum[15] = '\0';
    strncpy(r.passenger, pass.c_str(), 30); r.passenger[30] = '\0';
    r.date = d;
    return r;
}

string Request::toString() const {
    ostringstream oss;
    oss << "ID: " << id << ", Пункт назначения: " << destination << ", Рейс: " << flightNum
        << ", Пассажир: " << passenger << ", Дата: " << date.toString();
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