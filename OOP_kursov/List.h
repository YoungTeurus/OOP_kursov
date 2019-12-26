#pragma once
#include <iostream>
#include "BaseObject.h"
template<typename T>
class List : public BaseObject {
public:
	// ������ ��� �������� ������
	int				type();
	const char*		name();
public:
				List();				// ����������� ������� ������
				List(unsigned int type_hash);// ����������� ������� ������ � ������������ ���� �������� ���������
				List(T*);			// ����������� ������ � �������
				~List();			// ���������� ������
	void		append(T* elem);	// ���������� �������� � ����� ������
	void		append(List<T>* list); // ���������� ������ � ����� ������
	int			len();				// ����� ������
	List<T>*	get_elem(const int index); // �������� index-���� ������� ������
	List<T>*	operator[](const int index);

	T*			get_obj();
	unsigned int get_type(); // �������� ���-����� ���� ���������, �������� � ������
//template < typename T>
//friend 		std::ostream& operator<<(std::ostream& out, const List<T>& list); // ���������� << ��� ������ � std::cout
//template < typename T>
//friend 		std::istream& operator>>(std::istream& in, List<T>& list); // ���������� >> ��� ����� � std::cin
private:
	T*			_obj;				// ��������� �� �������� ������
	List<T>*	_next;				// ��������� �� ��������� �������
	unsigned int _stored_items_type_hash; // ���-����� ���� ���������, �������� � ������
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
	if (!_next) { // ���� ��� ��� ���������� ��������
		_next = new List(elem);
		return;
	}
	_next->append(elem);
}

template<typename T>
inline void List<T>::append(List<T>* list)
{
	if (!_next) { // ���� ��� ��� ���������� ��������
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
	if (_obj == nullptr && _next) { // ����� �������� ������ ��� ������ ������ � ������ ���� � �� ���� _next
		auto elem = _next;
		auto _index = index;
		while (elem && _index > 0) {
			elem = elem->_next;
			_index--;
		}
		return elem;
	}
	//else if (_next) { // ���� �� �� ������, � ���� _next

	//}
	return nullptr;
}

template<typename T>
inline List<T>* List<T>::operator[](const int index)
{
	if (_obj == nullptr && _next) { // ����� �������� ������ ��� ������ ������ � ������ ���� � �� ���� _next
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
	if (_obj == nullptr) { // ���� ���������� � ������ ������, �������� ��������, �� �������� index
		if (_next) // ���� ������ �� ������
			return _next->operator[](index);
		return nullptr; // ���� ������ ������
	}
	if (index == 0) // ���� index ����� 0, ���������� ������� ������
		return _obj;
	if (_next) // ���� index �� ����� 0 � ���� ��������� �������
		return _next->operator[](index - 1); // ��������� ��������, �������� index
	// ���� ���������� �������� ���
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
		out << *list[len_of_list - 1]; // ����� ���������� �������� ��� "->"
	return out;
}
