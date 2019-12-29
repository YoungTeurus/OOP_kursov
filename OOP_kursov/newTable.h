#pragma once
#include "newList.h"

namespace nTable {
	using namespace nList;
	class Table {
	
			List		_list_of_lists;								// Список списков для хранения данных
			List		_list_of_names;								// Список имён столбиков
			int			_num_of_columns;							// Количество столбцов
	public:
						Table();									// Конструктор пустой строки

			void		UI();										// Запускает интерфейс для работы с пользователем через командную строку

			bool		add_column(int type_id);					// Добавляет столбик в таблицу
			bool		add_column(int type_id, std::string col_name); // Добавляет столбик с названием в таблицу
			bool		append_in_column(BaseType* elem,int col);	// Добавляет ячейку в выбранный столбик
			List*		get_cell(int col, int row);					// Возвращает указатель на ячейку
			void		edit_cell(int col, int row, std::string new_data); // Редактирование ячейки
			void		clear_cell(int col, int row);				// Очищает ячейку, сбрасывая _data в nullptr
			void		delete_column(int col);						// Удаляет колонку таблицы
			void		delete_cell(int col, int row);				// Удаляет ячейку таблицы
			void		delete_table();								// Удаляет всю таблицу

			void		swap_rows(int row1, int row2);				// Меняет местами две строки
			void		sort_by_column(int col);						// Сортировка таблицы по столбцу

			void		print();									// Выводит таблицу
			std::string	get_string();								// Получить строку для записи в текстовый файл
			int			write_in_file(std::string file_name);		// Запись в текстовый файл
			int			read_from_file(std::string file_name);		// Чтение из текстового файла

		friend std::ostream& operator<<(std::ostream&, Table&); // Вывод в поток
		friend std::istream& operator>>(std::istream&, Table&); // Ввод из потока
	public:
	//private:
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
		static		void			inputString_from_cin(std::string* str) {
			using namespace std;
			char temp_string[128];
			cin >> temp_string;
			while (getchar() != '\n') continue;
			*str = *(new std::string(temp_string));
		}
	};

	inline std::ostream& operator<<(std::ostream& out, Table& tbl) {
		out << tbl.get_string();
		return out;
	}
	inline std::istream& operator>>(std::istream& in, Table& tbl)
	{
		char test_char;
		in.get(test_char); // Считываем первый char
		if (test_char != '>') { // Если первый символ в файле не ">", то это не наш файл.
			return in; // Ошибка, не смогли считать файл
		}
		// Это будет в цикле до конца файла
		int current_column = 0;
		while (true)
		{
			// Считываем название столбца
			char name_char;
			std::string name_of_col;
			in.get(name_char);
			if (name_char == '<') // Дошли до конца файла
				break;
			while (name_char != '|') {
				name_of_col += name_char;
				in.get(name_char);
			}
			// Считываем тип хранимых элементов
			char type_char;
			in.get(type_char);
			std::string type_of_col; // Строка для записи числа - номера типа
			while (type_char != '|') {
				type_of_col += type_char;
				in.get(type_char);
			}
			int type;
			try {
				type = std::stoi(type_of_col);
			}
			catch (std::invalid_argument) { // Если в строке не int
				return in; // Ошибка, сохранённый в файле тип - не int
			}
			if (type < 0 || type > NUMBER_OF_TYPES - 1) {
				return in; // Ошибка, сохранённый в файле тип не определён
			}
			tbl.add_column(type, name_of_col); // Добавляем столбик нужного типа
			while (true) {
				char read_char;
				in.get(read_char);
				if (read_char == '#') { // Как встретили '#', так сразу вышли
					break;
				}
				std::string read_BasicType_str; // Строка для записи числа - номера типа
				while (read_char != '|') {
					read_BasicType_str += read_char;
					in.get(read_char);
				}
				switch (type)
				{
				case 0: {
					Int* elem = new Int();
					elem->put(read_BasicType_str);
					tbl.append_in_column(elem, current_column);
					break;
				}
				case 1: {
					Double* elem = new Double();
					elem->put(read_BasicType_str);
					tbl.append_in_column(elem, current_column);
					break;
				}
				case 2: {
					String* elem = new String();
					elem->put(read_BasicType_str);
					tbl.append_in_column(elem, current_column);
					break;
				}
				}
			}
			current_column++;
		}
		return in;
	}
}