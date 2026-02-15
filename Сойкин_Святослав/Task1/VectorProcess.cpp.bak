#include "pch.h"
#include "Utils.h"
#include "VectorProcess.h"

VectorProcess::VectorProcess():VectorProcess(initialize(getRand(23, 30))) {

} // VectorProcess::VectorProcess


VectorProcess::VectorProcess(const vector<float> data) {
	data_ = data;
} // VectorProcess::VectorProcess


// геттер для вывода вектора
const vector<float>& VectorProcess::data() {
	return data_;
} // VectorProcess::data


// Генерация вектора заданного размера
vector<float> VectorProcess::initialize(int n, float lo, float hi) {
	vector<float> data(n);

	generate(data.begin(), data.end(), [lo, hi]() { return getRand(lo, hi); });
	return data;
} // VectorProcess::initialize


// Количество отрицательных элементов вектора
int VectorProcess::numberNegatives() {
	return count_if(data_.begin(), data_.end(), 
		[](float item) { return item < 0; });
} // VectorProcess::numberNegatives


// Количество элементов вектора, не попадающих в интервал [a, b], введенный с клавиатуры
int VectorProcess::numberNotInRange(float a, float b) {
	return count_if(data_.begin(), data_.end(), 
		[a, b](float item) { return a > item or item > b; });
} // VectorProcess::numberNotInRange


// Сумма элементов вектора, расположенных перед первым минимальным элементом
float VectorProcess::sumBeforeFirstMin() {
	auto itFirstMin = min_element(data_.begin(), data_.end());

	return accumulate(data_.begin(), itFirstMin, 0.f);
} // VectorProcess::sumBeforeFirstMin


// Сумма элементов вектора, расположенных между первым минимальным и первым максимальным элементами
float VectorProcess::sumBetweenFirstMinFirstMax() {
	auto itFirst = min_element(data_.begin(), data_.end());
	auto itSecond = max_element(data_.begin(), data_.end());

	if (itFirst > itSecond) {
		swap(itFirst, itSecond);
	} // if

	return accumulate(itFirst + 1, itSecond, 0.f);
} // VectorProcess::sumBetweenFirstMinFirstMax


// Выборка в другой вектор отрицательных элементов
vector<float> VectorProcess::fihdNegatives() {
	vector <float> selected;

	copy_if(data_.begin(), data_.end(), back_inserter(selected),
		[](float item) { return item < 0.f; });

	return selected;
} // VectorProcess::fihdNegatives


// Выбрка в другой вектор элементов, не попадающих в интервал [a, b]
vector<float> VectorProcess::fihdNotInRange(float a, float b) {
	vector <float> selected;

	copy_if(data_.begin(), data_.end(), back_inserter(selected),
		[a, b](float item) { return a > item || item > b; });

	return selected;
} // VectorProcess::fihdNotInRange


// Упорядочить элементы вектора по убыванию
void VectorProcess::orderByDesc() {
	sort(data_.begin(), data_.end(), greater<float>());
} // VectorProcess::orderByDesc


// Упорядочить вектор по возрастанию модулей элементов
void VectorProcess::orderByAbs() {
	sort(data_.begin(), data_.end(), [](float x, float y) {
		return abs(x) < abs(y);
	});
} // VectorProcess::orderByAbs


// Упорядочить вектор по правилу – элементы, не попадающие в интервал 
// значений [a, b] в конец вектора
void VectorProcess::orderByNotInRangeLast(float a, float b) {
	sort(data_.begin(), data_.end(), [a, b](float x, float y) {
		return a <= x && x <= b and (a > y or y > b);
	});
} // VectorProcess::orderByNotInRangeLast


// Запись вектора в бинарный файл
void VectorProcess::saveToBinary(const string &fileName) {
	fstream fs(fileName, ios::out | ios::binary);

	if (!fs.is_open()) {
		throw exception(("VectorProcess: Ошибка открытия файла " + fileName + " для записи").c_str());
	} // if

	for (auto datum : data_) {
		fs.write((char*)&datum, sizeof(datum));
	} // for datum

	fs.close();
} // VectorProcess::saveToBinary


// Чтение вектора из бинарного файла
void VectorProcess::loadFromBinary(const string& fileName) {
	fstream fs(fileName, ios::in | ios::binary);

	if (!fs.is_open()) {
		throw exception(("VectorProcess: Ошибка открытия файла " + fileName + " для чтения").c_str());
	} // if

	for (data_.clear(); !fs.eof(); fs.peek()) {
		float datum;
		fs.read((char*)&datum, sizeof(datum));
		data_.emplace_back(datum);
	} // for datum

	fs.close();
} // VectorProcess::loadFromFile
