#include "Table.h"
#include <vector> // Вспомогательный vector используется лишь в выводе. Без него можно обойтись, но так удобнее.
#include <fstream>

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

bool Table::edit_cell(int col, int row, int type, void* new_obj)
{
	//0) Определить тип и длинну столбца
	//1) Получить ячейку
	// 1.1) Если требуемой ячейки нет - создать новую
	// 1.2) Если перед требуемой ячейкой нет других - создать новые, пустые
	//2) Получить новое значение _obj
	//3) Заменить _obj
	switch (type)
	{
		case 0: {
			auto list_to_work = (List<TYPE_0>*)get_column(col)->get_obj();
			auto len_of_column = list_to_work->len();
			while (len_of_column < row + 1) { // Если текущей ячейки нет
				list_to_work->append(new TYPE_0()); // Заполняем место до ячейки пустыми элементами
				len_of_column++;
			}
			auto elem_to_work = list_to_work->get_elem(row); // Получаем элемент, с кот-ым будем работать
			elem_to_work->set_obj((TYPE_0*)new_obj);
			return true;
		}
		case 1: {
			auto list_to_work = (List<TYPE_1>*)get_column(col)->get_obj();
			auto len_of_column = list_to_work->len();
			while (len_of_column < row + 1) { // Если текущей ячейки нет
				list_to_work->append(new TYPE_1()); // Заполняем место до ячейки пустыми элементами
				len_of_column++;
			}
			auto elem_to_work = list_to_work->get_elem(row); // Получаем элемент, с кот-ым будем работать
			elem_to_work->set_obj((TYPE_1*)new_obj);
			return true;
		}
		case 2: {
			auto list_to_work = (List<TYPE_2>*)get_column(col)->get_obj();
			auto len_of_column = list_to_work->len();
			while (len_of_column < row + 1) { // Если текущей ячейки нет
				list_to_work->append(new TYPE_2()); // Заполняем место до ячейки пустыми элементами
				len_of_column++;
			}
			auto elem_to_work = list_to_work->get_elem(row); // Получаем элемент, с кот-ым будем работать
			elem_to_work->set_obj((TYPE_2*)new_obj);
			return true;
		}
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
	auto hash_of_type_of_element_to_clear = ((List<int>*)get_column(col)->get_obj())->get_type();
	// Необходимо сделать корректное приведение типов, чтобы правильно удалить _obj
	if (hash_of_type_of_element_to_clear == typeid(TYPE_0).hash_code()) {
		((List<TYPE_0>*)cell_to_empty)->set_obj(nullptr);
	}
	else if (hash_of_type_of_element_to_clear == typeid(TYPE_1).hash_code()) {
		((List<TYPE_1>*)cell_to_empty)->set_obj(nullptr);
	}
	else if (hash_of_type_of_element_to_clear == typeid(TYPE_2).hash_code()) {
		((List<TYPE_2>*)cell_to_empty)->set_obj(nullptr);
	}
}

std::string* Table::get_string()
{
	auto string_to_return = new std::string();
	*string_to_return += ">"; // Символ начала вывода таблицы

	auto num_of_col = list_of_lists->len();
	for (int col = 0; col < num_of_col; col++) {
		*string_to_return += *(list_of_names.get_elem(col)->get_obj()); // Название столбца
		*string_to_return += "|"; // Разделитель
		auto hash_of_type_of_element_to_write = ((List<int>*)get_column(col)->get_obj())->get_type(); // Тип записываемого элемента
		if (hash_of_type_of_element_to_write == typeid(TYPE_0).hash_code()) {
			auto list_to_work = (List<TYPE_0>*)get_column(col)->get_obj();
			*string_to_return += "0"; // Запись типа
			*string_to_return += "|";
			auto len_of_list = list_to_work->len();
			for (int i = 0; i < len_of_list; i++) {
				// Запись элементов
				auto element_to_add = *list_to_work->get_elem(i)->get_obj();
				*string_to_return += convertInt(element_to_add);
				// Добавление разделителя
				*string_to_return += "|";
			}
			*string_to_return += "#"; // Разделитель столбцов
		}
		else if (hash_of_type_of_element_to_write == typeid(TYPE_1).hash_code()) {
			auto list_to_work = (List<TYPE_1>*)get_column(col)->get_obj();
			*string_to_return += "1"; // Запись типа
			*string_to_return += "|";
			auto len_of_list = list_to_work->len();
			for (int i = 0; i < len_of_list; i++) {
				// Запись элементов
				auto element_to_add = *list_to_work->get_elem(i)->get_obj();
				*string_to_return += convertDouble(element_to_add);
				// Добавление разделителя
				*string_to_return += "|";
			}
			*string_to_return += "#"; // Разделитель столбцов
		}
		else if (hash_of_type_of_element_to_write == typeid(TYPE_2).hash_code()) {
			auto list_to_work = (List<TYPE_2>*)get_column(col)->get_obj();
			*string_to_return += "2"; // Запись типа
			*string_to_return += "|";
			auto len_of_list = list_to_work->len();
			for (int i = 0; i < len_of_list; i++) {
				// Запись элементов
				auto element_to_add = *list_to_work->get_elem(i)->get_obj();
				*string_to_return += element_to_add;
				// Добавление разделителя
				*string_to_return += "|";
			}
			*string_to_return += "#"; // Разделитель столбцов
		}
	}
	*string_to_return += "<";
	return string_to_return;
}

void Table::write_into_txt_file()
{
	std::ofstream output_file;
	output_file.open("out.txt", std::ios::out);
	auto string_to_write = get_string();
	output_file << *string_to_write;
	delete string_to_write;
	output_file.close();
}

int Table::load_from_txt_file()
{
	// Загружать таблицу можно только тогда, когда она пуста
	if (list_of_lists->len() != 0)
		return -665; // Ошибка, таблица не пуста

	std::ifstream input_file;
	input_file.open("out.txt", std::ios::in);
	if (!input_file) {
		return -1; // Ошибка, не смогли открыть файл
	}

	char test_char;
	input_file.get(test_char); // Считываем первый char
	if (test_char != '>') { // Если первый символ в файле не ">", то это не наш файл.
		input_file.close();
		return -2; // Ошибка, не смогли считать файл
	}
	// Это будет в цикле до конца файла
	int current_column = 0;
	while(true)
	{
		// Считываем название столбца
		char name_char;
		std::string name_of_col;
		input_file.get(name_char);
		if (name_char == '<') // Дошли до конца файла
			break;
		while (name_char != '|') {
			name_of_col += name_char;
			input_file.get(name_char);
		}
		// Считываем тип хранимых элементов
		char type_char;
		input_file.get(type_char);
		std::string type_of_col; // Строка для записи числа - номера типа
		while (type_char != '|') {
			type_of_col += type_char;
			input_file.get(type_char);
		}
		int type;
		try {
			type = std::stoi(type_of_col);
		}
		catch (std::invalid_argument){ // Если в строке не int
			input_file.close();
			return -3; // Ошибка, сохранённый в файле тип - не int
		}
		if (type < 0 || type > 2) {
			input_file.close();
			return -4; // Ошибка, сохранённый в файле тип не определён
		}
		add_column(type, name_of_col); // Добавляем столбик нужного типа
		switch (type)
		{
			case 0: {
				while(true){
					// Считываем int
					char int_char;
					input_file.get(int_char);
					if (int_char == '#') { // Как встретили '#', так сразу вышли
						break;
					}
					std::string read_int; // Строка для записи числа - номера типа
					while (int_char != '|') {
						read_int += int_char;
						input_file.get(int_char);
					}
					auto read_int_int = new int();
					try {
						*read_int_int = std::stoi(read_int);
					}
					catch (std::invalid_argument) { // Если в строке не int
						input_file.close();
						return -5; // Ошибка, сохранённый в файле элемент не совпадает с типом, указанным ранее
					}
					append_in_column(read_int_int, current_column); // Добавили элемент в конец
				}
				break;
			}
			case 1: {
				while (true) {
					// Считываем int
					char double_char;
					input_file.get(double_char);
					if (double_char == '#') { // Как встретили '#', так сразу вышли
						break;
					}
					std::string read_double; // Строка для записи числа - номера типа
					while (double_char != '|') {
						read_double += double_char;
						input_file.get(double_char);
					}
					auto read_double_double = new double();
					try {
						*read_double_double = std::stod(read_double);
					}
					catch (std::invalid_argument) { // Если в строке не int
						input_file.close();
						return -5; // Ошибка, сохранённый в файле элемент не совпадает с типом, указанным ранее
					}
					append_in_column(read_double_double, current_column); // Добавили элемент в конец
				}
				break;
			}
			case 2: {
				while (true) {
					// Считываем int
					char char_char;
					input_file.get(char_char);
					if (char_char == '#') { // Как встретили '#', так сразу вышли
						break;
					}
					auto read_char = new std::string();
					//std::string read_char; // Строка для записи числа - номера типа
					while (char_char != '|') {
						*read_char += char_char;
						input_file.get(char_char);
					}
					append_in_column(read_char, current_column); // Добавили элемент в конец
				}
				break;
			}
		}
		current_column++;
	}

	input_file.close();
	return 0;
}
