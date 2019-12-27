#pragma once
#include <iostream>
#include "BaseObject.h"
template<typename T>
class List : public BaseObject {
public:
	// Методы для базового класса
	size_t			type();
	const char*		name();
	size_t			get_type();		// Получить хеш-сумму типа элементов, хранимых в списке
public:
				List();				// Конструктор пустого списка
				List(size_t type_hash);// Конструктор пустого списка с определением типа хранимых элементов
				List(T*);			// Конструктор списка с данными
				~List();			// Деструктор списка
	void		append(T* elem);	// Добавление элемента в конец списка
	void		append(List<T>* list); // Добавление списка в конец списка
	int			len();				// Длина списка

	List<T>*	get_elem(const int index); // Получить index-овый элемент списка
	T*			get_obj();			// Получить _obj элемента списка

	void		set_obj(T* new_obj); // Установить новый _obj для элемента списка
	
private:
	T*			_obj;				// Указатель на хранимый объект
	List<T>*	_next;				// Указатель на следующий элемент
	size_t		_stored_items_type_hash = 0; // Хэш-сумма типа элементов, хранимых в списке
};

template<typename T>
inline size_t List<T>::type()
{
	return typeid(this).hash_code();
}

template<typename T>
inline const char* List<T>::name()
{
	return typeid(this).name();
}

template<typename T>
inline List<T>::List()
{
	_obj = nullptr;
	_next = nullptr;
}

template<typename T>
inline List<T>::List(size_t type_hash)
{
	_obj = nullptr;
	_next = nullptr;
	_stored_items_type_hash = type_hash;
}

template<typename T>
inline List<T>::List(T* obj)
{
	_obj = obj;
	_next = nullptr;
}

template<typename T>
inline List<T>::~List()
{
	delete _obj;
	delete _next;
}

template<typename T>
inline void List<T>::append(T* elem)
{
	if (!_next) { // Если ещё нет следующего элемента
		_next = new List(elem);
		return;
	}
	_next->append(elem);
}

template<typename T>
inline void List<T>::append(List<T>* list)
{
	if (!_next) { // Если ещё нет следующего элемента
		_next = list;
		return;
	}
	_next->append(list);
}

template<typename T>
inline int List<T>::len()
{
	int len = 0;
	auto elem_of_list = _next;
	while (elem_of_list) {
		len++;
		elem_of_list = elem_of_list->_next;
	}
	return len;
}

template<typename T>
inline List<T>* List<T>::get_elem(const int index)
{
	if (!this)
		return nullptr;
	if (_obj == nullptr && _next) { // Такое работает только для головы списка и только если у неё есть _next
		auto elem = _next;
		auto _index = index;
		while (elem && _index > 0) {
			elem = elem->_next;
			_index--;
		}
		return elem;
	}
	//else if (_next) { // Если не от головы, и есть _next

	//}
	return nullptr;
}

template<typename T>
inline T* List<T>::get_obj()
{
	if (!this)
		return nullptr;
	return _obj;
}

template<typename T>
inline void List<T>::set_obj(T* new_obj)
{
	delete _obj;
	_obj = new_obj;
}

template<typename T>
inline size_t List<T>::get_type()
{
	return _stored_items_type_hash;
}

template<typename T>
std::ostream& operator<<(std::ostream& out, List<T>& list)
{
	//for (int i = 0; i < list.len(); i++)
	//	out << *list[i] << "->";
	auto len_of_list = list.len();
	for (int i = 0; i < len_of_list - 1; i++) {
		out << *list[i] << "->";
	}
	if (len_of_list > 0)
		out << *list[len_of_list - 1]; // Вывод последнего элемента без "->"
	return out;
}
