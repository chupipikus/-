#pragma once
class VectorProcess
{
	vector<float> data_;

public:
	VectorProcess();
	VectorProcess(const vector<float> data);

	// геттер для вывода вектора
    const vector<float>& data();

	// генрация вектора заданного размера, с заданным жиапазоном значений
	static vector<float> initialize(int n, float lo = -50.f, float hi = 50.f);


    // обработки по заданию
    
	// Количество отрицательных элементов вектора
    int numberNegatives();

    // Количество элементов вектора, не попадающих в интервал [a, b], введенный с клавиатуры
    int numberNotInRange(float a, float b);

    // Сумма элементов вектора, расположенных перед первым минимальным элементом
    float sumBeforeFirstMin();
     
    // Сумма элементов вектора, расположенных между первым минимальным и первым максимальным элементами
    float sumBetweenFirstMinFirstMax();
    
    // Выборка в другой вектор отрицательных элементов
    vector<float> fihdNegatives();
    
    // Выбрка в другой вектор элементов, не попадающих в интервал [a, b]
    vector<float> fihdNotInRange(float a, float b);

    // Упорядочить элементы вектора по убыванию
    void orderByDesc();
     
    // Упорядочить вектор по возрастанию модулей элементов
    void orderByAbs();

    // Упорядочить вектор по правилу – элементы, не попадающие в интервал 
    // значений [a, b] в конец вектора
    void orderByNotInRangeLast(float a, float b);

    // Запись вектора в бинарный файл
    void saveToBinary(const string& fileName);

    // Чтение вектора из бинарного файла
    void loadFromBinary(const string& fileName);
};

