#pragma once
#include "List.h"
#include <sstream>
#include <iostream>

#define TYPE_0 int
#define TYPE_1 double
#define TYPE_2 std::string

class Table
{
public:
											Table();					// ����������� ������ �������
				bool 						add_column(int id);			// ��������� ������� � ��������� ����� �������� ���������
				bool 						add_column(int id, std::string name);// ��������� ������� � ��������� ����� �������� ���������
template<typename T>
				bool						append_in_column(T* element, int num_of_column);// ��������� ������ � ��������� �������
				std::string					get_cell(int col, int row);	// ���������� ��������� ������ ������ ��� ������ �� �����
				void						print();					// ����� ������� � �������
				void						beauty_print();				// �������� ����� ������� � �������

				// ��������������� ������� �������� ����� � std::string
				static		std::string					convertInt(int number)
				{
					std::stringstream ss;
					ss << number;
					return ss.str();
				}
				static		std::string					convertDouble(double number)
				{
					std::stringstream ss;
					ss << number;
					return ss.str();
				}
private:
				List<std::string>			list_of_names;				// ������ �������� ��������
				List<BaseObject>*			list_of_lists;				// ������ ������ �������� ������
				int							num_of_columns;				// ���������� �������� (��� ������)
};

template<typename T>
inline bool Table::append_in_column(T* element, int num_of_column)
{
	auto always_get = list_of_lists->get_elem(num_of_column)->get_obj(); // ������ �������� ����� ������ �������. ���� ��� ��� - ������� nullptr
	if (always_get) {
		if (always_get->get_type() == typeid(*element).hash_code()) { // ���� ��� ������ �������� ��������� � ������������
			((List<T>*)always_get)->append(element); // ������ � ���� �������
			return true;
		}
	}
	std::cout << "Was not able to find column [" << num_of_column << "]!\n";
	return false;
}
