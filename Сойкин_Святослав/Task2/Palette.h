#pragma once
#include "Colors.h"

// Палитра цветов - набор констант для цветовой схемы интерфейса
enum Palette: int {
    mainColor = GRAY_ON_BLACK,     // основной цвет интерфейса
    infoColor = BLACK_ON_LTCYAN,   // цвет информационных строк
    acctColor = RED_ON_WHITE,      // цвет акцентов/выделения
    hintColor = BLACK_ON_WHITE,    // цвет подсказок/хинтов
    sumColor  = BLUE_ON_WHITE,     // цвет сумм/итогов
    errColor  = WHITE_ON_RED,      // цвет ошибок
    resColor  = LTCYAN_ON_BLACK,   // цвет результатов/подсветки
    arrColor  = LTCYAN_ON_BLACK,   // цвет массивов/таблиц
    headerColor = WHITE_ON_BLACK   // цвет заголовков

};
