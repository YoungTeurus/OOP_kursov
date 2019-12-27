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

bool Table::get_in_column(int num_of_column)
{
	auto always_get = list_of_lists->get_elem(num_of_column)->get_obj(); // Всегда пытаемся найти нужный столбик. Если его нет - получим nullptr
	if (always_get) {
		if (always_get->get_type() == typeid(TYPE_0).hash_code()) {
			TYPE_0* a = new TYPE_0();
			std::cin.clear();
			std::cin >> *a;
			append_in_column(a,num_of_column);
			return true;
		}
		if (always_get->get_type() == typeid(TYPE_1).hash_code()) {
			TYPE_1* a = new TYPE_1();
			std::cin.clear();
			std::cin >> *a;
			append_in_column(a, num_of_column);
			return true;
		}
		if (always_get->get_type() == typeid(TYPE_2).hash_code()) {
			TYPE_2* a = new TYPE_2();
			inputString_from_cin(a);
			append_in_column(a, num_of_column);
			return true;
		}
	}
	return false;
}

std::string Table::get_cell_to_string(int col, int row)
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

List<BaseObject>* Table::get_column(int col)
{
	return (List<BaseObject>*)list_of_lists->get_elem(col);
}

void* Table::get_cell(int col, int row)
{
	return ((List<void>*)get_column(col)->get_obj())->get_elem(row);
}

/*
void Table::print()
{
	//List<std::string> strings_to_print;
	for (int row = 0; row < 10; row++) {
		std::string string_to_add;
		for (int col = 0; col < num_of_columns; col++) {
			string_to_add += get_cell_to_string(col, row);
			string_to_add += " | ";
		}
		std::cout << string_to_add << "\n";
	}
}
*/

void Table::beauty_print()
{
	const int num_of_rows = 10;

	// Печатаем по столбику
	List < std::vector < std::string >> strings_;
	std::vector<size_t> max_lens;
	for (int col = 0; col < num_of_columns; col++) {
		std::vector<std::string>* col_strings = new std::vector<std::string>;
		
		for (int row = 0; row < num_of_rows; row++) {
			std::string string_to_add;
			string_to_add += get_cell_to_string(col, row);
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

void Table::delete_column(int col)
{
	// 1. Получить указатель на столбец
	// 2. Удалить столбец
	list_of_lists->remove_elem(col);
	list_of_names.remove_elem(col);
	num_of_columns--;
}

void Table::delete_cell(int col, int row)
{
	//auto cell_to_delete = get_cell(col, row);
	//auto int_hash = ((List<int>*)get_column(col)->get_obj())->get_type();
	//auto test_int_hash = typeid(int).hash_code();
	//auto test_int_hash_2 = typeid(int*).hash_code();
	//auto test_int_hash_3 = typeid(List<int>*).hash_code();

	auto column_where_cell_to_delete_is = get_column(col);
	auto list_where_cell_to_delete_is = (List<BaseObject>*)column_where_cell_to_delete_is->get_obj();
	list_where_cell_to_delete_is->remove_elem(row);
	
	//((List<BaseObject>*)cell_to_delete)->get_type();
}

void Table::empty_cell(int col, int row)
{
	auto cell_to_empty = get_cell(col, row);
	((List<BaseObject>*)cell_to_empty)->set_obj(nullptr);
}
