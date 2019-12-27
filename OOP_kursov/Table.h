#pragma once
#include "List.h"
#include <sstream>
#include <iostream>

#define TYPE_0 int
#define TYPE_1 double
#define TYPE_2 std::string

class Table
{
				List<std::string>			list_of_names;					// Список названий столбцов
				List<BaseObject>*			list_of_lists;					// Голова самого главного списка
				int							num_of_columns;					// Количество столбцов (для вывода)
public:
											Table();						// Конструктор пустой таблицы
				bool 						add_column(int id);				// Добавляет столбик с выбранным типом хранимых элементов
				bool 						add_column(int id, std::string name);// Добавляет столбик с выбранным типом хранимых элементов
template<typename T> bool					append_in_column(T* element, int num_of_column);// Добавляет ячейку в выбранный столбик
				bool						get_in_column(int num_of_column);// Добавляет ячейку в выбранный столбик, запрашивая ввод у пользователя
				void						beauty_print();					// Красивый вывод таблицы в консоль
				bool						edit_cell(int col, int row, int type, void* new_obj);// Изменение значения ячейки
				void						delete_column(int col);			// Удаление столбца
				void						delete_cell(int col, int row);	// Удаление строки
				
				void						empty_cell(int col, int row);	// Очищение ячейки,т.е. удаление его _obj

				std::string*				get_string();					// Возвращает строку - линейную запись таблицы
				void						write_into_txt_file();			// Запись в текстовый файл
				int						load_from_txt_file();			// Загрузка из текстового файла

				//void						print();						// Вывод таблицы в консоль
				// Вспомогательные функции перевода чисел в std::string
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
				// Получение std::string из cin
				static		void			inputString_from_cin(std::string* str) {
					using namespace std;
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin, *str);
				}
private:
				std::string					get_cell_to_string(int col, int row);	// Возвращает строковую запись ячейки для вывода на экран
//private:
public:
				List<BaseObject>*			get_column(int col);		// Получение указателя на столбец
				void*						get_cell(int col, int row);	// Получение указателя на ячейку
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
