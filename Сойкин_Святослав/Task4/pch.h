#pragma once

// дл€ использовани€ старых, небезопасных функций, например sprintf()
#define _CRT_SECURE_NO_WARNINGS

// использование математических констант, современный стиль
#include <corecrt_math_defines.h>

#include <iostream>  // этот файл делает доступными инженерные функции  
#include <iomanip>   // дл€ манипул€торов вывода setw(), setprecision()
#include <Windows.h> // дл€ использовани€ функций WinAPI
#include <conio.h>
#include <sstream>   // дл€ объекта ostringstream
#include <fstream>   // дл€ файловых потоков ввода/вывода

#include <vector>
#include <algorithm>
#include <numeric>

#include <locale> // чтоб не мучатьс€ с кодировками
#include <map>    // for freq dict
#include <list>

using namespace std;

// объ€вление символической константы - кодовой страницы (UTF-8)
constexpr auto CODE_PAGE = 1251;