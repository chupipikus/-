#include "pch.h"
#include "Utils.h"
#include "MenuItem.h"
#include "Menu.h"
#include "App.h"

int main() {
    init(L"Task3: Flight Ticket Requests Management");

    App app;

    // Commands
    enum Commands : int {
        CMD_ADD = 1001,
        CMD_REMOVE,
        CMD_FILTER_FLIGHT,
        CMD_FILTER_DATE,
        CMD_FILTER_PASS,
        CMD_SORT_ID,
        CMD_SORT_DATE,
        CMD_SORT_DEST,
        CMD_CHANGE,
        CMD_SAVE,
        CMD_LOAD,
        CMD_SWAP_FIRST_LAST,
        CMD_SWAP_EARLY_LATEST
    };

    vector<MenuItem> items = {
        MenuItem(CMD_ADD, "Add new request"),
        MenuItem(CMD_REMOVE, "Delete by ID"),
        MenuItem(CMD_FILTER_FLIGHT, "Filter by flight"),
        MenuItem(CMD_FILTER_DATE, "Filter by date"),
        MenuItem(CMD_FILTER_PASS, "Filter by passenger"),
        MenuItem(CMD_SORT_ID, "Sort by ID"),
        MenuItem(CMD_SORT_DATE, "Sort by date"),
        MenuItem(CMD_SORT_DEST, "Sort by destination"),
        MenuItem(CMD_CHANGE, "Modify request"),
        MenuItem(CMD_SAVE, "Save to binary"),
        MenuItem(CMD_LOAD, "Load from binary"),
        MenuItem(CMD_SWAP_FIRST_LAST, "Swap first/last in file"),
        MenuItem(CMD_SWAP_EARLY_LATEST, "Swap earliest/latest in file"),
        MenuItem(Menu::CMD_QUIT, "Exit")
    };

    Menu menu(COORD{ 5, 5 }, items, mainColor, infoColor);

    while (true) {
        try {
            cls();
            showNavBarMessage(hintColor, "Task3: Flight Ticket Requests");

            int cmd = menu.navigate();
            if (cmd == Menu::CMD_QUIT) break;

            switch (cmd) {
            case CMD_ADD: app.doAddRequest(); break;
            case CMD_REMOVE: app.doDeleteById(); break;
            case CMD_FILTER_FLIGHT: app.doSelectByFlight(); break;
            case CMD_FILTER_DATE: app.doSelectByDate(); break;
            case CMD_FILTER_PASS: app.doSelectByPassenger(); break;
            case CMD_SORT_ID: app.doSortById(); break;
            case CMD_SORT_DATE: app.doSortByDate(); break;
            case CMD_SORT_DEST: app.doSortByDestination(); break;
            case CMD_CHANGE: app.doChangeRequest(); break;
            case CMD_SAVE: app.doSaveToBinaryFixed(); break;
            case CMD_LOAD: app.doLoadFromBinaryFixed(); break;
            case CMD_SWAP_FIRST_LAST: app.doSwapFirstLastInFile(); break;
            case CMD_SWAP_EARLY_LATEST: app.doSwapEarliestLatestInFile(); break;
            }

            getKey("");
        }
        catch (exception& ex) {
            int x = 12, y = 8;
            cout << color(errColor)
                << pos(x, y) << setw(W) << " "
                << pos(x, y + 1) << setw(W) << " "
                << pos(x, y + 2) << setw(W) << left << "    [ERROR]"
                << pos(x, y + 3) << setw(W) << " "
                << pos(x, y + 4) << setw(W) << ("    "s + ex.what())
                << pos(x, y + 5) << setw(W) << " "
                << pos(x, y + 6) << setw(W) << " "
                << pos(0, 20) << right << color(mainColor);
            getKey("");
        }
    }

    cls();
    return 0;
}
