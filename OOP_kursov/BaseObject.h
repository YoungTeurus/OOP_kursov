#pragma once

class BaseObject {
public:
	virtual		int				type() = 0;				// Возвращение уникального типа объекта
	virtual		const char*		name() = 0;				// Возвращение имя типа объекта
	//virtual		void			append(BaseObject* elem) = 0;
};