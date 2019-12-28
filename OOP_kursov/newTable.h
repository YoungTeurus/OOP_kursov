#pragma once
#include "newList.h"
//#include <sstream>
//#include <iostream>

namespace nTable {
	using namespace nList;
	class Table {
	
		List _list_of_lists; // Список списков для хранения данных
		List _list_of_names; // Список имён столбиков
		int _num_of_columns; // Количество столбцов
	public:
		Table();
		bool add_column(int type_id); // Добавляет столбик в таблицу
		bool add_column(int type_id, std::string col_name); // Добавляет столбик с названием в таблицу
		bool append_in_column(BaseType* elem,int col); // Добавляет ячейку в выбранный столбик
		List* get_cell(int col, int row); // Возвращает указатель на ячейку

		void print(); // Выводит таблицу
		std::string get_string(); // Получить строку для записи в текстовый файл
		void write_in_file(); // Запись в текстовый файл
		int read_from_file(); // Чтение из текстового файла

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
	
		friend std::ostream& operator<<(std::ostream&, Table&); // Вывод в поток
		friend std::ostream& operator>>(std::ostream&, Table&); // Ввод из потока
	};

	inline std::ostream& operator<<(std::ostream& out, Table& tbl) {
		out << tbl.get_string();
		return out;
	}
}