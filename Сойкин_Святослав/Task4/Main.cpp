#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"

int main() try {
    init(L"Task4: Абоненты ГАТС");

    App app;

    // Commands
    enum Commands : int {
        CMD_ADD = 1001,
        CMD_REMOVE,
        CMD_FILTER_TARIFF,
        CMD_FILTER_DISCOUNT,
        CMD_FILTER_SUM_RANGE,
        CMD_SORT_ID,
        CMD_SORT_NAME,
        CMD_SORT_SUM_DESC,
        CMD_CHANGE,
        CMD_SAVE,
        CMD_LOAD
    };

    vector<MenuItem> items = {
        MenuItem(CMD_ADD, "Добавить абонента"),
        MenuItem(CMD_REMOVE, "Удалить по ID"),
        MenuItem(CMD_FILTER_TARIFF, "Отбор по тарифу"),
        MenuItem(CMD_FILTER_DISCOUNT, "Отбор по скидке"),
        MenuItem(CMD_FILTER_SUM_RANGE, "Отбор по сумме в диапазоне"),
        MenuItem(CMD_SORT_ID, "Сорт по ID"),
        MenuItem(CMD_SORT_NAME, "Сорт по ФИО"),
        MenuItem(CMD_SORT_SUM_DESC, "Сорт по сумме убыв."),
        MenuItem(CMD_CHANGE, "Изменить абонента"),
        MenuItem(CMD_SAVE, "Save CSV"),
        MenuItem(CMD_LOAD, "Load CSV"),
        MenuItem(Menu::CMD_QUIT, "Выход")
    };

    Menu menu(COORD{ 5, 5 }, items, mainColor, infoColor);

    while (true) {
        cls();
        showNavBarMessage(hintColor, "Task4: Абоненты");

        int cmd = menu.navigate();
        if (cmd == Menu::CMD_QUIT) break;

        switch (cmd) {
        case CMD_ADD: app.doAddPayer(); break;
        case CMD_REMOVE: app.doDeleteById(); break;
        case CMD_FILTER_TARIFF: app.doSelectByTariff(); break;
        case CMD_FILTER_DISCOUNT: app.doSelectByDiscount(); break;
        case CMD_FILTER_SUM_RANGE: app.doSelectBySumRange(); break;
        case CMD_SORT_ID: app.doSortById(); break;
        case CMD_SORT_NAME: app.doSortByName(); break;
        case CMD_SORT_SUM_DESC: app.doSortBySumDescending(); break;
        case CMD_CHANGE: app.doChangePayer(); break;
        case CMD_SAVE: app.doSaveToCSV(); break;
        case CMD_LOAD: app.doLoadFromCSV(); break;
        }

        getKey("\nНажмите для продолжения...");
    }

    cls();
    return 0;
}
catch (exception& ex) {
    int x = 12, y = 8;
    cout << color(errColor)
        << pos(x, y) << setw(W) << " "
        << pos(x, y + 1) << setw(W) << " "
        << pos(x, y + 2) << setw(W) << left << "    [Ошибка]"
        << pos(x, y + 3) << setw(W) << " "
        << pos(x, y + 4) << setw(W) << ("    "s + ex.what())
        << pos(x, y + 5) << setw(W) << " "
        << pos(x, y + 6) << setw(W) << " "
        << pos(0, 20) << right << color(mainColor);
    getKey("");
}