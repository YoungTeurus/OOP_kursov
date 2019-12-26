#pragma once

class BaseObject {
public:
	virtual		int				type() = 0;				// Возвращение уникального типа объекта
	virtual		const char*		name() = 0;				// Возвращение имя типа объекта
	virtual		unsigned int	get_type() = 0;			// Возвращает хеш-сумму типа элементов, хранимых в списке
};