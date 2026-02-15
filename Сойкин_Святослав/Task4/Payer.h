#pragma once
#include "pch.h"
#include "Object.h"
#include "Date.h"

class Payer : public Object {
private:
    int id_;
    string name_;
    string phone_;
    double tariff_;
    int discount_;
    int timeMin_;
    Date date_;

public:
    static Payer createFactory(int id);

    int getId() const { return id_; }
    string getName() const { return name_; }
    string getPhone() const { return phone_; }
    double getTariff() const { return tariff_; }
    int getDiscount() const { return discount_; }
    int getTimeMin() const { return timeMin_; }
    Date getDate() const { return date_; }

    double calculateSum() const { return timeMin_ * tariff_ * (1 - discount_ / 100.0); }

    void setId(int id) { id_ = id; }
    void setName(const string& name) { name_ = name; }
    void setPhone(const string& phone) { phone_ = phone; }
    void setTariff(double tariff) { tariff_ = tariff; }
    void setDiscount(int discount) { discount_ = discount; }
    void setTimeMin(int timeMin) { timeMin_ = timeMin; }
    void setDate(short d, short m, short y) { date_.setDate(d, m, y); }

    string toString() const override;
};