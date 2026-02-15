#pragma once
#include "pch.h"

// Базовый класс для организации вывода 
// всех производных классов 
class Object
{
public:
	Object() = default;
	virtual ~Object() = default;

	// все потомки класса умеют строить свое строковое представление
	virtual string toString() const = 0;  // Добавлен const

	// обычная практика - сравнение объектов
	// virtual bool equals(Object &other) = 0;
};