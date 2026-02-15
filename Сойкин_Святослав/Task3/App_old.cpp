#include "App.h"
#include "Utils.h"

App::App() {}

void App::printList(const list<Request>& lst, const string& title) const {
    cout << "     " << title << "\n"
        << "     +" << setfill('-') << setw(112) << "-" << "+"
        << setfill(' ') << "\n";

    int row = 1;
    for (const auto& r : lst) {
        cout << " " << setfill('0') << setw(3) << row++ << setfill(' ')
            << " | ID: " << setw(2) << r.id
            << " | Пункт назначения: " << setw(19) << r.destination
            << " | Рейс: " << setw(8) << r.flightNum
            << " | Пассажир: " << setw(15) << r.passenger
            << " | Дата: " << r.date.toString() << " |\n";
    }
    cout << "     +" << setfill('-') << setw(112) << "-" << "+"
        << setfill(' ') << "\n";
}

void App::doAddRequest() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.addRequest();
    cout << "Добавлено\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doDeleteById() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    if (getRequests().empty()) throw exception("Список пуст");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    int id = it->getId();
    requests_.deleteById(id);
    cout << color(errColor) << "Удалена заявка ID: " << id << color(mainColor) << "\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doSelectByFlight() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    if (getRequests().empty()) throw exception("Список пуст");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    string flight = it->getFlightNum();
    cout << "Рейс: " << flight << "\n";
    auto res = requests_.selectByFlight(flight);
    printList(res, "Заявки по рейсу");
}

void App::doSelectByDate() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    if (getRequests().empty()) throw exception("Список пуст");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    Date date = it->getDate();
    cout << "Дата: " << date.toString() << "\n";
    auto res = requests_.selectByDate(date);
    printList(res, "Заявки по дате");
}

void App::doSelectByPassenger() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    if (getRequests().empty()) throw exception("Список пуст");

    const auto& all = requests_.getList();
    auto it = all.begin();
    advance(it, getRand(0, static_cast<int>(all.size()) - 1));
    string pass = it->getPassenger();
    cout << "Пассажир: " << pass << "\n";
    auto res = requests_.selectByPassenger(pass);
    printList(res, "Заявки по пассажиру");
}

void App::doSortById() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.sortById();
    cout << "Отсортировано по ID\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doSortByDate() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.sortByDate();
    cout << "Отсортировано по дате\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doSortByDestination() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.sortByDestination();
    cout << "Отсортировано по пункту назначения\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doChangeRequest() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    if (getRequests().empty()) throw exception("Список пуст");

    auto it = getRequests().begin();
    advance(it, getRand(0, getRequests().size() - 1));
    int id = it->id;
    requests_.changeRequest(id);
    cout << "Изменена заявка ID: " << id << "\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doSaveToBinaryFixed() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.saveToBinaryFixed(binFile_);
    cout << "Сохранено\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doLoadFromBinaryFixed() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.loadFromBinaryFixed(binFile_);
    cout << "Загружено\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doSwapFirstLastInFile() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.swapFirstLastInFile(binFile_);
    cout << "Первая/последняя запись поменяны местами\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}

void App::doSwapEarliestLatestInFile() {
    cls();
    printList(getRequests(), "Список заявок");
    getKey("\nНажмите любую клавишу для продолжения... \n\n");

    requests_.swapEarliestLatestInFile(binFile_);
    cout << "Самые ранние/поздние записи поменяны местами\n";

    cls();
    printList(getRequests(), "Текущий список заявок");
}