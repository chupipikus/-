#include "Payer.h"
#include "Utils.h"
#include <sstream>

Payer Payer::createFactory(int id) {
    Payer p;
    p.setId(id);
    p.setName("Абонент" + to_string(getRand(1, 20)));
    p.setPhone("062-" + to_string(getRand(121, 333)));
    p.setTariff(getRand(1.0, 5.0));
    p.setDiscount(getRand(0, 20));
    p.setTimeMin(getRand(10, 200));
    p.setDate(getRand(1, 28), getRand(1, 12), getRand(2025, 2027));
    return p;
}

string Payer::toString() const {
    ostringstream oss;
    oss << "ID: " << getId() << ", ФИО: " << getName() << ", Телефон: " << getPhone()
        << ", Тариф: " << fixed << setprecision(2) << getTariff() << ", Скидка: " << getDiscount()
        << ", Минуты: " << getTimeMin() << ", Дата: " << getDate().toString() << ", Сумма: " << calculateSum();
    return oss.str();
}