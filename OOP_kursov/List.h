#pragma once
#include <iostream>
#include "BaseObject.h"
template<typename T>
class List : public BaseObject {
public:
	// ������ ��� �������� ������
	size_t			type();
	const char*		name();
	size_t			get_type();		// �������� ���-����� ���� ���������, �������� � ������
public:
				List();				// ����������� ������� ������
				List(size_t type_hash);// ����������� ������� ������ � ������������ ���� �������� ���������
				List(T*);			// ����������� ������ � �������
				~List();			// ���������� ������
	void		append(T* elem);	// ���������� �������� � ����� ������
	void		append(List<T>* list); // ���������� ������ � ����� ������
	int			len();				// ����� ������

	List<T>*	get_elem(const int index); // �������� index-���� ������� ������
	T*			get_obj();			// �������� _obj �������� ������

	void		set_obj(T* new_obj); // ���������� ����� _obj ��� �������� ������
	
private:
	T*			_obj;				// ��������� �� �������� ������
	List<T>*	_next;				// ��������� �� ��������� �������
	size_t		_stored_items_type_hash = 0; // ���-����� ���� ���������, �������� � ������
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
		out << *list[len_of_list - 1]; // ����� ���������� �������� ��� "->"
	return out;
}
