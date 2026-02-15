#include "pch.h"
#include "Date.h"

// Установка даты с проверкой корректности
void Date::setDate(short day, short month, short year) {
    // Проверяем корректность даты
    char buf[1024];
    if (!dateValid(day, month, year)) {
        sprintf(buf, "%02d/%02d/%04d - некорректная дата", day, month, year);
        throw exception(buf);
    } // if

    // Сохраняем значения
    day_ = day;
    month_ = month;
    year_ = year;
} // Date::setDate


// Преобразовать дату в строковый формат DD.MM.YYYY
string Date::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << day_ << "."
        << setw(2) << setfill('0') << month_ << "."
        << setw(4) << setfill('0') << year_;
    return oss.str();
} // Date::toString


bool Date::operator<(const Date& date) const {
    if (getYear() != date.getYear()) return getYear() < date.getYear();
    if (getMonth() != date.getMonth()) return getMonth() < date.getMonth();
    return getDay() < date.getDay();
} // operator<


bool Date::operator==(const Date& date) const {
    return getDay() == date.getDay() && getMonth() == date.getMonth() && getYear() == date.getYear();
} // operator==


int Date::toJulianDays() const {
    int a = (14 - getMonth()) / 12;
    int y = getYear() + 4800 - a;
    int m = getMonth() + 12 * a - 3;
    return getDay() + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;
} // Date::toJulianDays


void Date::toGrigorian(int julianDays) {
    int a = julianDays + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - 146097 * b / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - 1461 * d / 4;
    int m = (5 * e + 2) / 153;

    day_ = e - (153 * m + 2) / 5 + 1;
    month_ = m + 3 - 12 * (m / 10);
    year_ = 100 * b + d - 4800 + m / 10;
} // Date::toGrigorian


ostream& operator<<(ostream& os, const Date& date) {
    os << date.toString();
    return os;
} // operator<<


istream& operator>>(istream& is, Date& date) {
    short day, month, year;
    is >> day >> month >> year;

    date.setDate(day, month, year);
    return is;
} // operator>>


// Static methods definitions
bool Date::dateValid(short day, short month, short year) {
    if (year < 0) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(month, year)) return false;
    return true;
}

short Date::daysInMonth(short month, short year) {
    switch (month) {
    case 4:  case 6:  case 9:  case 11: return 30;
    case 2:  return isLeapYear(year) ? 29 : 28;
    default: return 31;
    } // switch
}

bool Date::isLeapYear(short year) {
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}