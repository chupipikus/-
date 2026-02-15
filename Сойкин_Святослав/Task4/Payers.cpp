#include "Payers.h"
#include "Utils.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>  // for runtime_error

void checkInputFormat(istringstream& iss) {
    if (iss.fail()) throw runtime_error("CSV: неверный формат поля");
}

Payers::Payers() {
    for (int i = 0; i < 15; ++i) {
        list_.push_back(Payer::createFactory(nextId_++));
    }
}

void Payers::addPayer() {
    list_.push_back(Payer::createFactory(nextId_++));
}

void Payers::deleteById(int id) {
    list_.remove_if([id](const Payer& p) { return p.getId() == id; });
}

list<Payer> Payers::selectByTariff(double tariff) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [tariff](const Payer& p) {
        return eq(p.getTariff(), tariff);
        });
    return result;
}

list<Payer> Payers::selectByDiscount(int discount) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [discount](const Payer& p) {
        return p.getDiscount() == discount;
        });
    return result;
}

list<Payer> Payers::selectBySumRange(double low, double high) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [low, high](const Payer& p) {
        double sum = p.calculateSum();
        return sum >= low && sum <= high;
        });
    result.sort([](const Payer& a, const Payer& b) { return a.getPhone() < b.getPhone(); });
    return result;
}

list<Payer> Payers::selectByPhone(const string& phone) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [&phone](const Payer& p) {
        return p.getPhone() == phone;
    });
    return result;
}

list<Payer> Payers::selectByName(const string& name) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [&name](const Payer& p) {
        return p.getName() == name;
    });
    return result;
}

list<Payer> Payers::selectByDate(const Date& date) const {
    list<Payer> result;
    copy_if(list_.begin(), list_.end(), back_inserter(result), [&date](const Payer& p) {
        return p.getDate() == date;
    });
    return result;
}

double Payers::totalPayments() const {
    double sum = 0.0;
    for (const auto& p : list_) sum += p.calculateSum();
    return sum;
}

void Payers::sortByPhone() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getPhone() < b.getPhone(); });
}

void Payers::sortByTimeDescending() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getTimeMin() > b.getTimeMin(); });
}

void Payers::sortById() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getId() < b.getId(); });
}

void Payers::sortByName() {
    list_.sort([](const Payer& a, const Payer& b) { return a.getName() < b.getName(); });
}

void Payers::sortBySumDescending() {
    list_.sort([](const Payer& a, const Payer& b) { return a.calculateSum() > b.calculateSum(); });
}

void Payers::changePayer(int id) {
    for (auto& p : list_) {
        if (p.getId() == id) {
            p = Payer::createFactory(id);
            return;
        }
    }
    throw runtime_error("Плательщик не найден");
}

void Payers::saveToCSV(const string& fname) const {
    ofstream out(fname);
    if (!out.is_open()) throw runtime_error(("Не удалось открыть файл для записи: " + fname).c_str());

    out << "ID,ФИО,Телефон,Тариф,Скидка,Минуты,День,Месяц,Год\n";
    for (const auto& p : list_) {
        out << p.getId() << "," << p.getName() << "," << p.getPhone() << "," << p.getTariff() << "," << p.getDiscount()
            << "," << p.getTimeMin() << "," << p.getDate().getDay() << "," << p.getDate().getMonth() << "," << p.getDate().getYear() << "\n";
    }
}

void Payers::loadFromCSV(const string& fname) {
    if (fname.empty()) throw runtime_error("CSV: пустое имя файла.");

    ifstream in(fname);
    if (!in.is_open()) throw runtime_error(("CSV: не удалось открыть файл " + fname).c_str());

    string line;
    if (!getline(in, line)) throw runtime_error("CSV: ошибка чтения заголовка.");

    {
        istringstream iss(line);
        string token;
        if (!getline(iss, token, ',')) throw runtime_error("CSV: неверный заголовок.");
        if (token != "ID") throw runtime_error("CSV: неверный заголовок (ожидается ID).");
        // Заголовок корректен: далее ожидается набор полей в фиксированном порядке
    }

    list_.clear();
    while (getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        Payer p;
        int id, discount, timeMin, d, m, y;
        double tariff;
        string name, phone;

        iss >> id;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный разделитель (ожидается запятая после ID).");
        getline(iss, name, ',');
        getline(iss, phone, ',');
        iss >> tariff;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный разделитель (ожидается запятая после тарифа).");
        iss >> discount;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный разделитель (ожидается запятая после скидки).");
        iss >> timeMin;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный разделитель (ожидается запятая после минут).");
        iss >> d;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный разделитель (ожидается запятая после дня).");
        iss >> m;
        checkInputFormat(iss);
        if (iss.get() != ',') throw runtime_error("CSV: неверный разделитель (ожидается запятая после месяца).");
        iss >> y;
        checkInputFormat(iss);

        p.setId(id);
        p.setName(name);
        p.setPhone(phone);
        p.setTariff(tariff);
        p.setDiscount(discount);
        p.setTimeMin(timeMin);
        p.setDate(d, m, y);

        list_.push_back(p);
        nextId_ = max(nextId_, p.getId() + 1);
    }

    if (list_.empty()) throw runtime_error("CSV: в файле нет записей для загрузки.");
}