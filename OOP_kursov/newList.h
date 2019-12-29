#pragma once
#include "BaseTypes.h"

namespace nList {

	class List :public BaseType {
			BaseType*		_data;
			List*			_next;
			size_t			_type_hash;						// Хеш типа хранимых данных
			int				_type;							// Тип хранимых данных (только для ввода/вывода в файл)
	public:
			//*** Базовые методы ***//
			std::string		get();							// Возвращает строку - значение переменной
			void			put(std::string str);			// Записывает значение в переменную из строки
	static	size_t			hash_code();					// Возвращает хеш код типа
							~List();
			int				compare(BaseType*);				// Сравнение объектов
			void			add(BaseType*) {}				// Сложение объектов
			BaseType*		copy();							// Копия объекта

			//*** Особые методы ***//
							List();							// Пустой конструктор
							List(size_t type_hash);			// Конструктор списка определённых элементов
							List(BaseType* elem);			// Конструктор списка сразу с данными
			bool			append(BaseType* elem);			// Доабвление элемента к списку
			void			append(List* lst);				// Добавление целого списка в конец
			void			append_empty();					// Добавление в конец пустого элемента

			List*			operator[](const int index);	// Получение index-ого элемента списка
			BaseType*		data();							// Получение поля _data
			void			set_data(BaseType* new_data);	// Установка поля _data
			int				len();							// Получение длинны списка
			bool			remove_elem(const int index);	// Удаление элемента списка
			int				get_type();						// Возвращение типа
			void			sort();							// Сортировка списка
			void			set_type(const int);			// Установка типа (только для ввода/вывода в файл)
			void			set_type_hash(size_t type_hash);// Установка хеша типа хранимых данных
			bool			swap_elements(int a, int b);	// Изменение положения двух колонок
	};

	inline List::List()
	{
		_data = nullptr;
		_next = nullptr;
		_type_hash = 0;
		_type = -1;
	}
	inline List::List(size_t type_hash)
	{
		_data = nullptr;
		_next = nullptr;
		_type_hash = type_hash;
		_type = -1;
	}
	inline List::List(BaseType* elem)
	{
		_data = elem;
		_next = nullptr;
		_type_hash = 0;
		_type = -1;
	}
	inline std::string List::get()
	{
		std::string string_to_return;
		Int int_type(_type);
		string_to_return += int_type.get();
		string_to_return += "|";
		auto len_of_list = len();
		for (int i = 0; i < len_of_list; i++) {
			string_to_return += (*this)[i]->data()->get();
			string_to_return += "|";
		}
		return string_to_return;
	}
	inline void List::put(std::string str)
	{
		//TODO: Подумать, нужно ли тут будет писать что-то для практической пользы
	}
	inline size_t List::hash_code()
	{
		return typeid(List).hash_code();
	}
	inline List::~List()
	{
		// Если удаляется НЕ голова списка, то нельзя удалять _next
		if (!_data)
			delete _next;
		delete _data;
	}
	inline int List::compare(BaseType*)
	{
		//TODO: Подумать, нужно ли тут будет писать что-то для практической пользы
		return 0;
	}
	inline BaseType* List::copy()
	{
		//TODO: Подумать, нужно ли тут будет писать что-то для практической пользы

		//if (!_data) { // Копировать можно только с головы!
		//	auto elem_to_return = new List();
		//
		//	return elem_to_return;
		//}
		return nullptr;
	}
	inline bool List::append(BaseType* elem)
	{
		if (!elem)
			return false;
		if (elem->hash_code() == _type_hash || _type_hash == 0) { // Если типы совпадают
			if (!_next) { // Если ещё нет следующего элемента
				_next = new List(elem);
				return true;
			}
			_next->append(elem);
		}
		return false;
	}
	inline void List::append(List* lst)
	{
		// Нужно ли проверять типы?
		if (!_next) { // Если ещё нет следующего элемента
			_next = lst;
			return;
		}
		_next->append(lst);
	}
	inline void List::append_empty()
	{
		switch (get_type())
		{
		case 0: {
			append(new Int());
			break;
			}
		case 1: {
			append(new Double());
			break;
			}
		case 2: {
			append(new String());
			break;
			}
		}
	}
	inline List* List::operator[](const int index)
	{
		if (!this || index < -1) // Если обратились к пустому списку или несуществующему индексу
			return nullptr;
		if (index == -1 && !_data) { // Особый случай: -1 возвращает указатель на саму голову списка, если она действительно голова
			return this;
		}
		if (!_data && _next) { // Такое работает только для головы списка и только если у неё есть _next
			auto elem = _next;
			auto _index = index;
			while (elem && _index > 0) {
				elem = elem->_next;
				_index--;
			}
			return elem;
		}
		return nullptr; // Если обратились не от головы или у головы нет элементов
	}
	inline BaseType* List::data()
	{
		if (!this)
			return nullptr;
		//if (!_data) {
		//	return new Empty();
		//}
		return _data;
	}
	inline void List::set_data(BaseType* new_data)
	{
		if (new_data->hash_code() == _type_hash) { // Если типы совпадают
			delete _data;
			_data = new_data;
		}
	}
	inline int List::len()
	{
		int len = 0;
		auto elem_of_list = _next;
		while (elem_of_list) {
			len++;
			elem_of_list = elem_of_list->_next;
		}
		return len;
	}
	inline bool List::remove_elem(const int index)
	{
		auto elem_to_delete = (*this)[index]; // Получаем указатель на тот элемент, который необходимо удалить
		if (elem_to_delete) { // Если этот элемент найден
			if (index > 0) { // Если удаляем НЕ первый элемент списка
				auto elem_prev_to_delete = (*this)[index-1]; // Получаем указатель на тот элемент, который стоит перед тем, который необходимо удалить
				elem_prev_to_delete->_next = elem_to_delete->_next; // Прокидываем указатель на _next
				delete elem_to_delete;								// Удаляем элемент
			}
			else { // Если удаляем первый элемент списка
				_next = elem_to_delete->_next;	// Прокидываем указатель на _next
				delete elem_to_delete;			// Удаляем элемент
			}
			return true;
		}
		return false;
	}
	inline int List::get_type()
	{
		return _type;
	}
	inline void List::sort()
	{
	}
	inline void List::set_type(const int type)
	{
		_type = type;
	}
	inline void List::set_type_hash(size_t type_hash)
	{
		_type_hash = type_hash;
	}
	inline bool List::swap_elements(int a, int b)
	{
		if (a == b || a < 0 || b < 0)
			return false;
		// Пускай a всегда будет "левым" элементом. Т.к. передали копии, можно изменять эти значения
		if (a > b) {
			auto temp = a;
			a = b;
			b = temp;
		}
		auto col_a = (*this)[a];
		auto col_b = (*this)[b];
		if (!col_a || !col_b) // Если хотя бы одной колонки не существует
			return false;

		// Получаем адреса колонок перед необходимыми
		auto col_a_prev = (*this)[a - 1];
		auto col_b_prev = (*this)[b - 1];

		col_a_prev->_next = col_b;
		col_b_prev->_next = col_a;

		auto temp = col_a->_next;
		col_a->_next = col_b->_next;
		col_b->_next = temp;

		return true;
	}
}