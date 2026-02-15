#pragma once
#include "Colors.h"

// Описание палитры: смысловые названия цветов
enum Palette: int {
    mainColor = GRAY_ON_BLACK,     // Основной текст
    infoColor = BLACK_ON_LTCYAN,   // Информационные сообщения
    acctColor = RED_ON_WHITE,      // Акцент/ошибка
    hintColor = BLACK_ON_WHITE,    // Подсказки
    sumColor  = BLUE_ON_WHITE,     // Суммы
    errColor  = WHITE_ON_RED,      // Ошибки
    resColor  = LTCYAN_ON_BLACK,   // Результаты
    arrColor  = LTCYAN_ON_BLACK,   // Табличные элементы
    headerColor = WHITE_ON_BLACK   // Заголовки

};
