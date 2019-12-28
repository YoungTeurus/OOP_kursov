﻿#pragma once
#include "BaseTypes.h"
/*
if (typeid(this).hash_code() == (typeid(TYPE_0).hash_code()))
*/

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

			//*** Особые методы ***//
							List();							// Пустой конструктор
							List(size_t type_hash);			// Конструктор списка определённых элементов
							List(BaseType* elem);			// Конструктор списка сразу с данными
			bool			append(BaseType* elem);			// Доабвление элемента к списку
			void			append(List* lst);				// Добавление целого списка в конец

			List*			operator[](const int index);	// Получение index-ого элемента списка
			BaseType*		data();							// Получение поля _data
			void			set_data(BaseType* new_data);	// Установка поля _data
			int				len();							// Получение длинны списка
			bool			remove_elem(const int index);	// Удаление элемента списка
			void			set_type(const int);					// Установка типа (только для ввода/вывода в файл)
			void			set_type_hash(size_t type_hash);// Установка хеша типа хранимых данных
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
		/*
		auto hash_of_type_of_element_to_write = ((List<int>*)get_column(col)->get_obj())->get_type(); // Тип записываемого элемента
		if (hash_of_type_of_element_to_write == typeid(TYPE_0).hash_code()) {
			auto list_to_work = (List<TYPE_0>*)get_column(col)->get_obj();
			*string_to_return += "0"; // Запись типа
			*string_to_return += "|";
			auto len_of_list = list_to_work->len();
			for (int i = 0; i < len_of_list; i++) {
				// Запись элементов
				auto element_to_add = *list_to_work->get_elem(i)->get_obj();
				*string_to_return += convertInt(element_to_add);
				// Добавление разделителя
				*string_to_return += "|";
			}
			*string_to_return += "#"; // Разделитель столбцов
		}
		else if (hash_of_type_of_element_to_write == typeid(TYPE_1).hash_code()) {
			auto list_to_work = (List<TYPE_1>*)get_column(col)->get_obj();
			*string_to_return += "1"; // Запись типа
			*string_to_return += "|";
			auto len_of_list = list_to_work->len();
			for (int i = 0; i < len_of_list; i++) {
				// Запись элементов
				auto element_to_add = *list_to_work->get_elem(i)->get_obj();
				*string_to_return += convertDouble(element_to_add);
				// Добавление разделителя
				*string_to_return += "|";
			}
			*string_to_return += "#"; // Разделитель столбцов
		}
		else if (hash_of_type_of_element_to_write == typeid(TYPE_2).hash_code()) {
			auto list_to_work = (List<TYPE_2>*)get_column(col)->get_obj();
			*string_to_return += "2"; // Запись типа
			*string_to_return += "|";
			auto len_of_list = list_to_work->len();
			for (int i = 0; i < len_of_list; i++) {
				// Запись элементов
				auto element_to_add = *list_to_work->get_elem(i)->get_obj();
				*string_to_return += element_to_add;
				// Добавление разделителя
				*string_to_return += "|";
			}
			*string_to_return += "#"; // Разделитель столбцов
		}
		*/


		return string_to_return;
	}
	inline void List::put(std::string str)
	{
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
	inline List* List::operator[](const int index)
	{
		if (!this) // Если обратились к пустому списку
			return nullptr;
		if (_data == nullptr && _next) { // Такое работает только для головы списка и только если у неё есть _next
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
	inline void List::set_type(const int type)
	{
		_type = type;
	}
	inline void List::set_type_hash(size_t type_hash)
	{
		_type_hash = type_hash;
	}
}