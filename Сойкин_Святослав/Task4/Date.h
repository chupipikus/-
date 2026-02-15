#pragma once
#include "pch.h"
#include "Object.h"

//  ласс, описывающий дату: день, мес€ц, год. 
class Date : public Object
{
    short day_;   // день
    short month_; // мес€ц
    short year_;  // год

    static bool  dateValid(short day, short month, short year);
    static short daysInMonth(short month, short year);
    static bool  isLeapYear(short year);

    int  toJulianDays() const;
    void toGrigorian(int julianDays);

public:
    // ансамбль конструкторов
    Date() : day_(1), month_(1), year_(1970) {}
    Date(short day, short month, short year) {
        setDate(day, month, year);
    } // Date

    Date(const Date& date) = default;
    virtual ~Date() = default;

    // геттеры и сеттер
    short getDay()   const { return day_; }
    short getMonth() const { return month_; }
    short getYear()  const { return year_; }

    void setDate(short day, short month, short year);

    // реализаци€ виртуального метода
    virtual string toString() const override;

    // перегруженные оператор
    // ќперации <, == дл€ добавлени€ в map, multimap, set, multiset 
    bool operator <(const Date& date) const;
    bool operator==(const Date& date) const;

    friend ostream& operator<<(ostream& os, const Date& date);
    friend istream& operator>>(istream& is, Date& date);
};