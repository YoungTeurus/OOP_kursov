#pragma once
#include "List.h"
#include <sstream>
#include <iostream>

#define TYPE_0 int
#define TYPE_1 double
#define TYPE_2 std::string

class Table
{
				List<std::string>			list_of_names;				// ������ �������� ��������
				List<BaseObject>*			list_of_lists;				// ������ ������ �������� ������
				int							num_of_columns;				// ���������� �������� (��� ������)
public:
											Table();					// ����������� ������ �������
				bool 						add_column(int id);			// ��������� ������� � ��������� ����� �������� ���������
				bool 						add_column(int id, std::string name);// ��������� ������� � ��������� ����� �������� ���������
template<typename T> bool					append_in_column(T* element, int num_of_column);// ��������� ������ � ��������� �������
				bool						get_in_column(int num_of_column); // ��������� ������ � ��������� �������, ���������� ���� � ������������
				void						beauty_print();				// �������� ����� ������� � �������
				void						edit_cell(int col, int row);// ��������� �������� ������
				void						delete_column(int col);		// �������� �������
				void						delete_cell(int col, int row);// �������� ������
				
				void						empty_cell(int col, int row);// �������� ������,�.�. �������� ��� _obj

				//void						print();					// ����� ������� � �������
				// ��������������� ������� �������� ����� � std::string
				static		std::string		convertInt(int number)
				{
					std::stringstream ss;
					ss << number;
					return ss.str();
				}
				static		std::string		convertDouble(double number)
				{
					std::stringstream ss;
					ss << number;
					return ss.str();
				}
				// ��������� std::string �� cin
				static		void			inputString_from_cin(std::string* str) {
					using namespace std;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, *str);
				}
private:
				std::string					get_cell_to_string(int col, int row);	// ���������� ��������� ������ ������ ��� ������ �� �����
public:
				List<BaseObject>*			get_column(int col);		// ��������� ��������� �� �������
				void*						get_cell(int col, int row);	// ��������� ��������� �� ������
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
