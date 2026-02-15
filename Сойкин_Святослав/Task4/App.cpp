#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Payer>& lst, const string& title) const {

    const int consoleWidth = static_cast<int>(getConsoleSize().X);
    const int totalWidth = max(40, consoleWidth - 16);

    // fixed column sizes
    const int colRow = 4;   // index
    const int colId = 4;
    const int colPhone = 12;
    const int colTariff = 8;
    const int colDisc = 4;
    const int colMin = 5;
    const int colDate = 10;
    const int colSum = 10;

    int fixedCols = colRow + colId + colPhone + colTariff + colDisc + colMin + colDate + colSum + 9; // separators
    int nameCol = max(6, totalWidth - fixedCols);

    auto fit = [](const string& s, int maxLen) {
        if (maxLen <= 0) return string();
        if ((int)s.size() <= maxLen) return s;
        if (maxLen <= 3) return string(maxLen, '.');
        return s.substr(0, maxLen - 3) + "...";
    };

    cout << "     " << title << "\n"

    // header
         << " "
         << left << setw(colRow - 1) << "#" << " | "
         << left << setw(colId) << "ID" << " | "
         << left << setw(nameCol) << "Имя" << " | "
         << left << setw(colPhone) << "Телефон" << " | "
         << right << setw(colTariff) << "Tariff" << " | "
         << right << setw(colDisc) << "Disc" << " | "
         << right << setw(colMin) << "Min" << " | "
         << left << setw(colDate) << "Date" << " | "
         << right << setw(colSum) << "Sum" << "\n"

         << string(totalWidth + 16, '-') << "\n";

    int row = 1;
    for (const auto& p : lst) {
        cout << " "
             << left << setw(colRow - 1) << row++ << " | "
             << left << setw(colId) << p.getId() << " | "
             << left << setw(nameCol) << fit(p.getName(), nameCol) << " | "
             << left << setw(colPhone) << fit(p.getPhone(), colPhone) << " | ";

        ostringstream ssum;
        ssum << fixed << setprecision(2) << p.calculateSum();

        cout << right << setw(colTariff) << fixed << setprecision(2) << p.getTariff() << " | "
             << right << setw(colDisc) << p.getDiscount() << " | "
             << right << setw(colMin) << p.getTimeMin() << " | "
             << left << setw(colDate) << p.getDate().toString() << " | "
             << right << setw(colSum) << ssum.str() << "\n";
    }

    cout << string(totalWidth + 16, '-') << "\n";
}

void App::doAddPayer() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    payers_.addPayer();
    cout << "Готово\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doDeleteById() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int id = it->getId();
    payers_.deleteById(id);
    cout << color(errColor) << "Удалён плательщик ID: " << id << color(mainColor) << "\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doSelectByTariff() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    double tariff = it->getTariff();
    cout << "Выбранный тариф: " << tariff << "\n";
    auto res = payers_.selectByTariff(tariff);
    printList(res, "Плательщики по тарифу");
}

void App::doSelectByDiscount() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int discount = it->getDiscount();
    cout << "Выбранная скидка: " << discount << "\n";
    auto res = payers_.selectByDiscount(discount);
    printList(res, "Плательщики по скидке");
}

void App::doSelectBySumRange() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    if (payers_.getList().empty()) throw exception("Список пуст");

    double low = getRand(10.0, 100.0);
    double high = low + getRand(50.0, 200.0);
    cout << "Диапазон сумм: " << low << " - " << high << "\n";
    auto res = payers_.selectBySumRange(low, high);
    printList(res, "Плательщики по сумме (в диапазоне)");
}

void App::doSortById() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    payers_.sortById();
    cout << "Отсортировано по ID\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doSortByName() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    payers_.sortByName();
    cout << "Отсортировано по имени\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doSortBySumDescending() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    payers_.sortBySumDescending();
    cout << "Отсортировано по сумме (убывание)\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doChangePayer() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    if (payers_.getList().empty()) throw exception("Список пуст");

    auto it = payers_.getList().begin();
    advance(it, getRand(0, payers_.getList().size() - 1));
    int id = it->getId();
    payers_.changePayer(id);
    cout << "Изменён плательщик ID: " << id << "\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doSaveToCSV() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    payers_.saveToCSV(csvFile_);
    cout << "Готово\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}

void App::doLoadFromCSV() {
    cls();
    printList(payers_.getList(), "Список плательщиков");
    getKey("\nНажмите любую клавишу для продолжения");

    payers_.loadFromCSV(csvFile_);
    cout << "Готово\n";

    cls();
    printList(payers_.getList(), "Список плательщиков");
}