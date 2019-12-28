#include "newTable.h"
#include "BaseTypes.h"

#define Int_TYPE typeid(Int).hash_code()
#define Double_TYPE typeid(Double).hash_code()
#define String_TYPE typeid(String).hash_code()

#define NUMBER_OF_TYPES 3 // Количество типов


using namespace nTable;

Table::Table() {
	_list_of_lists = *(new List(typeid(List).hash_code())); // Список, хранящий только списки
	_list_of_names = *(new List(typeid(String).hash_code())); // Список, хранящий только String
	_num_of_columns = 0;
}

bool Table::add_column(int type_id) {
	std::string temp_name = "Column ";
	temp_name += convertInt(_num_of_columns);
	return add_column(type_id, temp_name);
}

bool Table::add_column(int type_id, std::string col_name) {
	auto temp_String = new String(col_name);
	_list_of_names.append(temp_String);
	switch (type_id)
	{
	case 0:
		_list_of_lists.append(new List(new List(Int_TYPE)));
		break;
	case 1:
		_list_of_lists.append(new List(new List(Double_TYPE)));
		break;
	case 2:
		_list_of_lists.append(new List(new List(String_TYPE)));
		break;
	default:
		std::cout << "The type of created column is not defined!" << "\n";
		return false;
	}

	// Хеш типа добавленного столбика равен хешу исходного элемента
	_list_of_lists[_num_of_columns]->set_type_hash(_list_of_lists.hash_code());
	((List*)(_list_of_lists[_num_of_columns])->data())->set_type(type_id);
	_num_of_columns++;
	return true;
}

bool nTable::Table::append_in_column(BaseType* elem, int col)
{
	return ((List*)_list_of_lists[col]->data())->append(elem);
}

List* nTable::Table::get_cell(int col, int row)
{
	//auto step_1 = (*_list_of_lists)[col]; // Получить элемент, хранящий столбец
	//auto step_2 = step_1->data(); // Получить столбец
	//auto step_3 = (List*)step_2; // Приводим столбец к типу столбца
	//auto step_4 = (*step_3)[row]; // Получаем элемент, хранящий ячейку
	return (*((List*)_list_of_lists[col]->data()))[row];
}

#include <vector> // Вспомогательный vector используется лишь в выводе. Без него можно обойтись, но так удобнее.
void nTable::Table::print()
{
	int max_rows = 0; // Максимальное число заполненных строк
	for (int i = 0; i < _num_of_columns; i++) {
		auto len_of_col = ((List*)_list_of_lists[i]->data())->len();
		if (len_of_col > max_rows)
			max_rows = len_of_col;
	}

	// Печатаем по столбику
	std::vector<std::vector<std::string>*> strings; // Вектор список для вывода
	std::vector<size_t> max_elem_len; // Вектор максимальных длин элементов столбца
	for (int col = 0; col < _num_of_columns; col++) {
		std::vector<std::string>* col_strings = new std::vector<std::string>;

		for (int row = 0; row < max_rows; row++) {
			std::string string_to_add;
			auto data_of_cell = get_cell(col, row)->data();
			if (data_of_cell)
				string_to_add += data_of_cell->get();
			else
				string_to_add += "N/A";
			string_to_add += " | ";
			col_strings->push_back(string_to_add);
		}
		size_t max_len = 0;
		for (int row = 0; row < max_rows; row++) {
			auto len_of_current_str = (*col_strings)[row].length();
			if (len_of_current_str > max_len) {
				max_len = len_of_current_str;
			}
		}
		// Учитываем название столбика при подсчёте длины
		auto len_of_name = (_list_of_names[col]->data())->get().length() + 2;
		if (len_of_name > max_len) {
			max_len = len_of_name;
		}
		max_elem_len.push_back(max_len);
		// Теперь знаем максимальную длину строки в столбце
		for (int row = 0; row < max_rows; row++) {
			auto len_of_current_str = (*col_strings)[row].length();
			if (len_of_current_str < max_len) {
				for (int i = 0; i < max_len - len_of_current_str; i++)
					(*col_strings)[row] = " " + (*col_strings)[row];
			}
		}
		strings.push_back(col_strings);
		//strings_.append(col_strings);
	}
	// Вывод навзаний столбиков
	for (int col = 0; col < _num_of_columns; col++) {
		auto name_len = (_list_of_names[col]->data())->get().length() + 2;
		if (name_len < max_elem_len[col]) {
			for (int i = 0; i < max_elem_len[col] - name_len; i++)
				std::cout << " ";
		}
		std::cout << (_list_of_names[col]->data())->get() << "| ";
	}
	std::cout << "\n";
	for (int col = 0; col < _num_of_columns; col++) {
		for (int i = 0; i < max_elem_len[col]; i++)
			std::cout << "-";
	}
	std::cout << "\n";
	// Вывод столбцов
	for (int row = 0; row < max_rows; row++) {
		for (int col = 0; col < _num_of_columns; col++) {
			std::cout << (*strings[col])[row];
		}
		std::cout << "\n";
		for (int col = 0; col < _num_of_columns; col++) {
			for (int i = 0; i < max_elem_len[col]; i++)
				std::cout << "-";
		}
		std::cout << "\n";
	}
	
}

std::string nTable::Table::get_string()
{
	std::string string_to_return;
	string_to_return += ">";
	for (int i = 0; i < _num_of_columns; i++) {
		string_to_return += _list_of_names[i]->data()->get();
		string_to_return += "|";
		string_to_return += _list_of_lists[i]->data()->get();
		string_to_return += "#";
	}
	string_to_return += "<";
	return string_to_return;
}

#include <fstream> // Библиотека для вывода в файл

void nTable::Table::write_in_file()
{
	std::ofstream output_file;
	output_file.open("out.txt", std::ios::out);
	output_file << *this;
	output_file.close();
}

int nTable::Table::read_from_file()
{
	// Загружать таблицу можно только тогда, когда она пуста
	if (_list_of_lists.len() != 0)
		return -665; // Ошибка, таблица не пуста

	std::ifstream input_file;
	input_file.open("out.txt", std::ios::in);
	if (!input_file) {
		return -1; // Ошибка, не смогли открыть файл
	}
	input_file >> *this;
	/*
	char test_char;
	input_file.get(test_char); // Считываем первый char
	if (test_char != '>') { // Если первый символ в файле не ">", то это не наш файл.
		input_file.close();
		return -2; // Ошибка, не смогли считать файл
	}
	// Это будет в цикле до конца файла
	int current_column = 0;
	while (true)
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
		catch (std::invalid_argument) { // Если в строке не int
			input_file.close();
			return -3; // Ошибка, сохранённый в файле тип - не int
		}
		if (type < 0 || type > NUMBER_OF_TYPES - 1) {
			input_file.close();
			return -4; // Ошибка, сохранённый в файле тип не определён
		}
		add_column(type, name_of_col); // Добавляем столбик нужного типа
		while (true) {
			char read_char;
			input_file.get(read_char);
			if (read_char == '#') { // Как встретили '#', так сразу вышли
				break;
			}
			std::string read_BasicType_str; // Строка для записи числа - номера типа
			while (read_char != '|') {
				read_BasicType_str += read_char;
				input_file.get(read_char);
			}
			switch (type)
			{
			case 0: {
				Int* elem = new Int();
				elem->put(read_BasicType_str);
				append_in_column(elem, current_column);
				break;
				}
			case 1: {
				Double* elem = new Double();
				elem->put(read_BasicType_str);
				append_in_column(elem, current_column);
				break;
				}
			case 2: {
				String* elem = new String();
				elem->put(read_BasicType_str);
				append_in_column(elem, current_column);
				break;
				}
			}
		}
		current_column++;
	}

	input_file.close();
	*/
	return 0;
}
