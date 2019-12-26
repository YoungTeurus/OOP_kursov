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
											Table();					// Конструктор пустой таблицы
				bool 						add_column(int id);			// Добавляет столбик с выбранным типом хранимых элементов
				bool 						add_column(int id, std::string name);// Добавляет столбик с выбранным типом хранимых элементов
template<typename T>
				bool						append_in_column(T* element, int num_of_column);// Добавляет ячейку в выбранный столбик
				std::string					get_cell(int col, int row);	// Возвращает строковую запись ячейки для вывода на экран
				void						print();					// Вывод таблицы в консоль
				void						beauty_print();				// Красивый вывод таблицы в консоль

				// Вспомогательные функции перевода чисел в std::string
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
				List<std::string>			list_of_names;				// Список названий столбцов
				List<BaseObject>*			list_of_lists;				// Голова самого главного списка
				int							num_of_columns;				// Количество столбцов (для вывода)
};

template<typename T>
inline bool Table::append_in_column(T* element, int num_of_column)
{
	auto always_get = list_of_lists->get_elem(num_of_column)->get_obj(); // Всегда пытаемся найти нужный столбик. Если его нет - получим nullptr
	if (always_get) {
		if (always_get->get_type() == typeid(*element).hash_code()) { // Если тип храним объектов совпадает с передаваемым
			((List<T>*)always_get)->append(element); // Запись в этот столбик
			return true;
		}
	}
	std::cout << "Was not able to find column [" << num_of_column << "]!\n";
	return false;
}
