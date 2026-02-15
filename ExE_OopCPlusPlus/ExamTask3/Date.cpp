#include "pch.h"
#include "Date.h"

// сеттер для даты
void Date::setDate(short day, short month, short year) {
    // если параметры не образуют корректную дату - выбрасываем исключение
    char buf[1024];
    if (!dateValid(day, month, year)) {
        sprintf(buf, "%02d/%02d%04d - некорректная дата", day, month, year);
        throw exception(buf);
    } // if

    // корректные данные - принимаем новые значения
    day_   = day;
    month_ = month;
    year_  = year;
} // Date::setDate


// вывод даты в строку
string Date::toString() {
	ostringstream oss;
	oss<< setfill('0') << setw(2) << day_ << "-" << setw(2) << month_
       << "-" << year_ << setfill(' ');
	return oss.str();
} // Date::toString


// проверка параметров на способность формирования корректной даты
bool Date::dateValid(short day, short month, short year) {
    if (month <= 1 or month > 12 or year <= 0) return false;

    // проверка дня
	if (day < 1 || day > daysInMonth(month, year)) return false;

    return true;
} // Date::dateValid


// возвращает количество дней в месяце
short Date::daysInMonth(short month, short year) {
    short daysInMonth[12] = {
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (isLeapYear(year)) daysInMonth[1]++;
    return daysInMonth[month - 1];
} // Date::daysInMonth


// проверка года на високосность
bool Date::isLeapYear(short year) {
    return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
} // Date::isLeapYear

// -------------------------------------------------------------------


bool Date::operator<(const Date &date) const {
    return toJulianDays() < date.toJulianDays();
} // Date::operator<


bool Date::operator>(const Date& date) const {
    return toJulianDays() > date.toJulianDays();
} // Date::operator>


bool Date::operator==(const Date &date) const {
    return toJulianDays() == date.toJulianDays();
} // Date::operator==


Date Date::operator+(int days) {
    return toDate(toJulianDays() + days);
} // Date::operator+


// -------------------------------------------------------------------

// возвращает количество юлианских дней в григорианской
// (т.е. обычной) дате
// https://ru.wikipedia.org/wiki/%D0%AE%D0%BB%D0%B8%D0%B0%D0%BD%D1%81%D0%BA%D0%B0%D1%8F_%D0%B4%D0%B0%D1%82%D0%B0#%D0%92%D1%8B%D1%87%D0%B8%D1%81%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5_%D0%BD%D0%BE%D0%BC%D0%B5%D1%80%D0%B0_%D1%8E%D0%BB%D0%B8%D0%B0%D0%BD%D1%81%D0%BA%D0%BE%D0%B3%D0%BE_%D0%B4%D0%BD%D1%8F_(JDN)_%D0%BF%D0%BE_%D0%B4%D0%B0%D1%82%D0%B5_%D0%B3%D1%80%D0%B8%D0%B3%D0%BE%D1%80%D0%B8%D0%B0%D0%BD%D1%81%D0%BA%D0%BE%D0%B3%D0%BE_%D0%BA%D0%B0%D0%BB%D0%B5%D0%BD%D0%B4%D0%B0%D1%80%D1%8F
int Date::toJulianDays() const {
    int a = (14 - month_) / 12;
    int y = year_ + 4800 - a;
    int m = month_ + 12 * a - 3;

    return day_ + (153 * m + 2)/5 + 365 * y + y/4 - y/100 + y/400 - 32045;
} // Date::toJulianDays


// получение полей даты из юлианского количества дней
void Date::toGrigorian(int julianDays) {
    *this = toDate(julianDays);
} // Date::toGrigorian


// получение даты из юлианского количества дней
Date Date::toDate(int julianDays) {
    int a = julianDays + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - 146097 * b / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - 1461 * d / 4;
    int m = (5 * e + 2) / 153;

    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = 100 * b + d - 4800 + m / 10;

    return Date(day, month, year);
} // Date::toGrigorian


// возвращает текущую дату
Date Date::now() {
    time_t t = time(nullptr);
    struct tm date = *localtime(&t);

    return Date(date.tm_mday + 1, date.tm_mon + 1, date.tm_year + 1900);
} // Date::now


ostream &operator<<(ostream &os, Date &date) {
    os << date.toString();
    return os;
} // operator<<


istream &operator>>(istream &is, Date &date) {
    short day, month, year;
    is >> day >> month >> year;

    date.setDate(day, month, year);
    return is;
} // operator>>
