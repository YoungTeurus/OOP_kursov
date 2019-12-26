#pragma once
#include <iostream>
#include "BaseObject.h"
template<typename T>
class List : public BaseObject {
public:
	// Методы для базового класса
	int				type();
	const char*		name();
public:
				List();				// Конструктор пустого списка
				List(unsigned int type_hash);// Конструктор пустого списка с определением типа хранимых элементов
				List(T*);			// Конструктор списка с данными
				~List();			// Деструктор списка
	void		append(T* elem);	// Добавление элемента в конец списка
	void		append(List<T>* list); // Добавление списка в конец списка
	int			len();				// Длина списка
	List<T>*	get_elem(const int index); // Получить index-овый элемент списка
	List<T>*	operator[](const int index);

	T*			get_obj();
	unsigned int get_type(); // Получить хеш-сумму типа элементов, хранимых в списке
//template < typename T>
//friend 		std::ostream& operator<<(std::ostream& out, const List<T>& list); // Перегрузка << для вывода в std::cout
//template < typename T>
//friend 		std::istream& operator>>(std::istream& in, List<T>& list); // Перегрузка >> для ввода в std::cin
private:
	T*			_obj;				// Указатель на хранимый объект
	List<T>*	_next;				// Указатель на следующий элемент
	unsigned int _stored_items_type_hash; // Хэш-сумма типа элементов, хранимых в списке
};

template<typename T>
inline int List<T>::type()
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
inline List<T>::List(unsigned int type_hash)
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
inline List<T>* List<T>::operator[](const int index)
{
	if (_obj == nullptr && _next) { // Такое работает только для головы списка и только если у неё есть _next
		auto elem = _next;
		auto _index = index;
		while (elem && _index > 0) {
			elem = elem->_next;
			_index--;
		}
		return elem;
	}
	return nullptr;
	/*
	if (_obj == nullptr) { // Если обращаемся к голове списка, вызываем рекурсию, не уменьшая index
		if (_next) // Если список не пустой
			return _next->operator[](index);
		return nullptr; // Если список пустой
	}
	if (index == 0) // Если index равен 0, возвращаем текущий объект
		return _obj;
	if (_next) // Если index не равен 0 и есть следующий элемент
		return _next->operator[](index - 1); // Запускаем рекурсию, уменьшая index
	// Если следующего элемента нет
	return nullptr;
	*/
}

template<typename T>
inline T* List<T>::get_obj()
{
	if (!this)
		return nullptr;
	return _obj;
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
