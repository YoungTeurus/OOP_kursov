#include "Table.h"
#include <vector>

Table::Table()
{
	list_of_lists = new List<BaseObject>();
	num_of_columns = 0;
}

bool Table::add_column(int id)
{
	std::string temp_name = "Column ";
	temp_name += convertInt(num_of_columns);
	return add_column(id, temp_name);
}

bool Table::add_column(int id, std::string name)
{
	list_of_names.append(new std::string(name));
	if (id == 0) {
		list_of_lists->append(new List<BaseObject>(new List<TYPE_0>(typeid(TYPE_0).hash_code()))); // Создание столбика int-ов
	}
	else if (id == 1) {
		list_of_lists->append(new List<BaseObject>(new List<TYPE_1>(typeid(TYPE_1).hash_code()))); // Создание столбика double-ов
	}
	else if (id == 2) {
		list_of_lists->append(new List<BaseObject>(new List<TYPE_2>(typeid(TYPE_2).hash_code()))); // Создание столбика string-ов
	}
	else {
		std::cout << "The type of created column is not defined!" << "\n";
		return false;
	}
	num_of_columns++;
	return true;
}

std::string Table::get_cell(int col, int row)
{
	auto type = typeid(int).hash_code(); // Определяется из типа создаваемой колонки

	std::string result;
	bool was_result_get = false; // Был ли получен результат?

	auto always_get = list_of_lists->get_elem(col)->get_obj(); // Всегда пытаемся найти нужный столбик. Если его нет - получим nullptr

	if (always_get) { // Не нужно ничего проверять, если такого столбика нет
		if (always_get->get_type() == typeid(TYPE_0).hash_code()) {
			auto a = (((List<TYPE_0>*)always_get)->get_elem(row)->get_obj());
			if (a) {
				TYPE_0 _result = *a;
				result += convertInt(_result);
				was_result_get = true;
			}

		}
		else if (always_get->get_type() == typeid(TYPE_1).hash_code()) {
			auto a = (((List<TYPE_1>*)always_get)->get_elem(row)->get_obj());
			if (a) {
				TYPE_1 _result = *a;
				result += convertDouble(_result);
				was_result_get = true;
			}
		}
		else if (always_get->get_type() == typeid(TYPE_2).hash_code()) {
			auto a = (((List<TYPE_2>*)always_get)->get_elem(row)->get_obj());
			if (a) {
				TYPE_2 _result = *a;
				result += _result;
				was_result_get = true;
			}
		}
		else {
			std::cout << "The type of cell [" << col << ";" << row << "] is not defined!" << "\n";
			return "N\\A";
		}
	}

	if (!was_result_get) {
		//std::cout << "The cell[" << col << ";" << row << "] is empty!" << "\n";
		return "N\\A";
	}

	return result;
}

void Table::print()
{
	//List<std::string> strings_to_print;
	for (int row = 0; row < 10; row++) {
		std::string string_to_add;
		for (int col = 0; col < num_of_columns; col++) {
			string_to_add += get_cell(col, row);
			string_to_add += " | ";
		}
		std::cout << string_to_add << "\n";
	}
}

void Table::beauty_print()
{
	const int num_of_rows = 10;

	// Печатаем по столбику
	List < std::vector < std::string >> strings_;
	std::vector<int> max_lens;
	for (int col = 0; col < num_of_columns; col++) {
		std::vector<std::string>* col_strings = new std::vector<std::string>;
		
		for (int row = 0; row < num_of_rows; row++) {
			std::string string_to_add;
			string_to_add += get_cell(col, row);
			string_to_add += " | ";
			col_strings->push_back(string_to_add);
		}
		size_t max_len = 0;
		for (int row = 0; row < num_of_rows; row++) {
			auto len_of_current_str = (*col_strings)[row].length();
			if (len_of_current_str > max_len) {
				max_len = len_of_current_str;
			}
		}
		// Учитываем название столбика при подсчёте длины
		auto len_of_name = (*list_of_names.get_elem(col)->get_obj()).length() + 2;
		if (len_of_name > max_len) {
			max_len = len_of_name;
		}
		max_lens.push_back(max_len);
		// Теперь знаем максимальную длину строки в столбце
		for (int row = 0; row < num_of_rows; row++) {
			auto len_of_current_str = (*col_strings)[row].length();
			if (len_of_current_str < max_len) {
				for (int i = 0; i < max_len - len_of_current_str; i++)
					(*col_strings)[row] = " " + (*col_strings)[row];
			}
		}
		strings_.append(col_strings);
	}
	// Вывод навзаний столбиков
	for (int col = 0; col < num_of_columns; col++) {
		auto name_len = (*list_of_names.get_elem(col)->get_obj()).length() + 2;
		if (name_len < max_lens[col]) {
			for (int i = 0; i < max_lens[col] - name_len; i++)
				std::cout << " ";
		}
		std::cout << *list_of_names.get_elem(col)->get_obj() << "| ";
	}
	std::cout << "\n";
	for (int col = 0; col < num_of_columns; col++) {
		for (int i = 0; i < max_lens[col]; i++)
			std::cout << "-";
	}
	std::cout << "\n";
	// Вывод столбцов
	for (int row = 0; row < num_of_rows; row++) {
		for (int col = 0; col < num_of_columns; col++) {
			std::cout << (*strings_.get_elem(col)->get_obj())[row];
		}
		std::cout << "\n";
		for (int col = 0; col < num_of_columns; col++) {
			for (int i = 0; i < max_lens[col]; i++)
				std::cout << "-";
		}
		std::cout << "\n";
	}
}
