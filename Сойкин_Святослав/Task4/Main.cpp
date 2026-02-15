#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"

int main() try {
    init(L"Task4: Payers management");

    App app;

    enum Commands : int {
        CMD_ADD = 1001,
        CMD_REMOVE,
        CMD_FILTER_PHONE,
        CMD_FILTER_NAME,
        CMD_FILTER_DATE,
        CMD_FILTER_SUM_RANGE,
        CMD_TOTAL,
        CMD_SORT_ID,
        CMD_SORT_PHONE,
        CMD_SORT_SUM_DESC,
        CMD_SORT_TIME_DESC,
        CMD_CHANGE,
        CMD_SAVE,
        CMD_LOAD
    };

    vector<MenuItem> items = {
        MenuItem(CMD_ADD, "Add payer"),
        MenuItem(CMD_REMOVE, "Delete by ID"),
        MenuItem(CMD_FILTER_PHONE, "Filter by phone"),
        MenuItem(CMD_FILTER_NAME, "Filter by name"),
        MenuItem(CMD_FILTER_DATE, "Filter by date"),
        MenuItem(CMD_FILTER_SUM_RANGE, "Filter by sum range"),
        MenuItem(CMD_TOTAL, "Total payments"),
        MenuItem(CMD_SORT_ID, "Sort by ID"),
        MenuItem(CMD_SORT_PHONE, "Sort by phone"),
        MenuItem(CMD_SORT_SUM_DESC, "Sort by sum (desc)"),
        MenuItem(CMD_SORT_TIME_DESC, "Sort by time (desc)"),
        MenuItem(CMD_CHANGE, "Modify payer"),
        MenuItem(CMD_SAVE, "Save CSV"),
        MenuItem(CMD_LOAD, "Load CSV"),
        MenuItem(Menu::CMD_QUIT, "Exit")
    };

    Menu menu(COORD{ 5, 5 }, items, mainColor, infoColor);

    while (true) {
        cls();
        showNavBarMessage(hintColor, "Task4: ��������");

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

        getKey("\n������� ��� �����������...");
    }

    cls();
    return 0;
}
catch (exception& ex) {
    int x = 12, y = 8;
    cout << color(errColor)
        << pos(x, y) << setw(W) << " "
        << pos(x, y + 1) << setw(W) << " "
        << pos(x, y + 2) << setw(W) << left << "    [������]"
        << pos(x, y + 3) << setw(W) << " "
        << pos(x, y + 4) << setw(W) << ("    "s + ex.what())
        << pos(x, y + 5) << setw(W) << " "
        << pos(x, y + 6) << setw(W) << " "
        << pos(0, 20) << right << color(mainColor);
    getKey("");
}