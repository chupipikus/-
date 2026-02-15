#pragma once
#include "Colors.h"

// ÷ветовые палитры и смысловые обозначени€ цветов
enum Palette: int {
    mainColor = GRAY_ON_BLACK,     // ќсновной цвет текста
    infoColor = BLACK_ON_LTCYAN,   // ÷вет информационных сообщений
    acctColor = RED_ON_WHITE,      // ÷вет выделени€ (акцент)
    hintColor = BLACK_ON_WHITE,    // ÷вет подсказок и подсветки
    sumColor  = BLUE_ON_WHITE,     // ÷вет суммарных значений
    errColor  = WHITE_ON_RED,      // ÷вет ошибок
    resColor  = LTCYAN_ON_BLACK,   // ÷вет результатов/подсказок
    arrColor  = LTCYAN_ON_BLACK,   // ÷вет массивов/таблиц
    headerColor = WHITE_ON_BLACK   // ÷вет заголовков

};
