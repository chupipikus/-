/*
 * ������ 1.
 *
 * ������ 9 ��������, ���������� ��� ��������:
 *     1) ���������� ������������� ���������
 *     2) ���������� ���, ���������� ��� [a, b]
 *     3) ����� ��� ������ ����������� ���
 *     4) ����� ��� ����� min � max
 *     5) ������ ������������� ���
 *     6) ������ ���, ���������� ��� [a, b]
 *     7) ���� ����� ���
 *     8) ���� ����� ���, ��� ������ |x|
 *     9) ������ ��, ���������� ��� [a, b], ��-36
 *
*/

#include "pch.h"
#include "Utils.h"
#include "App.h"

int main() try {

	init(L"������ 1. ���-36");
	App app;

	app.run();

	getKey("\n\n");
} // try
catch (exception &ex) {
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
	return 1;
}
