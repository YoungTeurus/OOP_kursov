#include "newTable.h"
#include "BaseTypes.h"

using namespace nTable;

Table::Table() {
	_list_of_lists = *(new List(typeid(List).hash_code())); // Список, хранящий только списки
	_list_of_names = *(new List(typeid(String).hash_code())); // Список, хранящий только String
	_num_of_columns = 0;
}

void nTable::Table::UI()
{
	
	using namespace std;
	bool UI_running = true;
	std::string last_msg = ""; // Сообщение, которое будет выводиться перед таблицей
	while (UI_running) {
		system("cls");
		cout << last_msg << "\n";
		print();
		cout << "What to do?\n";
		cout << "0. Close UI\n";
		cout << "1. Add new column\n";
		cout << "2. Add new cell in column\n";
		cout << "3. Edit cell in column\n";
		cout << "4. Clear cell\n";
		cout << "5. Delete cell\n";
		cout << "6. Delete column\n";
		cout << "7. Write into file\n";
		cout << "8. Load from file\n";
		cout << "Additional:\n";
		cout << "9. Swap columns\n";
		cout << "10. Edit (or add) row\n";
		cout << "11. Delete row\n";
		cout << "12. Sort column\n";
		int choise;
		cout << ">"; cin >> choise;
		switch (choise)
		{
		case 0:{
			UI_running = false;
			break;
		}
		// Добавление столбца
		case 1: { 
			cout << "Enter the type of new column:\n";
			cout << "1. int\n";
			cout << "2. double\n";
			cout << "3. std::string\n";
			int choise;
			cout << ">"; cin >> choise;
			cout << "Enter the name of new column:\n";
			std::string name;
			cout << ">"; Table::inputString_from_cin(&name);
			if (choise >= 1 && choise <= 3) {
				if (add_column(choise - 1, name)) {
					last_msg = "Column \"" + name + "\" was added!";
				}
				else {
					last_msg = "Column \"" + name + "\" was not added! Check inputs!";
				}
			}
			else
				cout << "You selected wrong type! Try again.\n";
			break;
		}
		// Добавление ячейки в столбец
		case 2: {
			cout << "Write the number of column to add cell: ";
			int column;
			cout << ">"; cin >> column;
			std::string st;
			cout << "Write the data for new cell: ";
			cout << ">"; inputString_from_cin(&st);
			edit_cell(column, ((List*)_list_of_lists[column]->data())->len(), st);
			last_msg = "Cell was added in " + convertInt(column) + " column!";
			break;
		}
		// Редактирование ячейки
		case 3: {
			cout << "Write the number of column to edit cell: ";
			int column;
			cout << ">"; cin >> column;
			cout << "Write the number of row to edit cell: ";
			int row;
			cout << ">"; cin >> row;
			std::string st;
			cout << "Write the data for new cell: ";
			cout << ">"; inputString_from_cin(&st);
			edit_cell(column, row, st);
			last_msg = "Cell ["+ convertInt(column) +"," + convertInt(row) +"] was edited!";
			break;
		}
		// Очищение ячейки
		case 4: {
			cout << "Write the number of column to edit cell: ";
			int column;
			cout << ">"; cin >> column;
			cout << "Write the number of row to edit cell: ";
			int row;
			cout << ">"; cin >> row;
			clear_cell(column, row);
			last_msg = "Cell [" + convertInt(column) + "," + convertInt(row) + "] was cleared!";
			break;
		}
		// Удаление ячейки
		case 5: {
			cout << "Write the number of column to delete cell: ";
			int column;
			cout << ">"; cin >> column;
			cout << "Write the number of row to delete cell: ";
			int row;
			cout << ">"; cin >> row;
			delete_cell(column, row);
			last_msg = "Cell [" + convertInt(column) + "," + convertInt(row) + "] was deleted!";
			break;
		}
		// Удаление столбца
		case 6: {
			cout << "Write the number of column to delete: ";
			int column;
			cout << ">"; cin >> column;
			delete_column(column);
			last_msg = "Column [" + convertInt(column) + "] was deleted!";
			break;
		}
		// Запись в файл
		case 7: {
			cout << "Enter the name of the file:\n";
			std::string name;
			cout << ">"; Table::inputString_from_cin(&name);
			if (write_in_file(name) == 0)
				last_msg = "Table was saved in file \"" + name + "\"!";
			else
				last_msg = "Table was NOT saved in file \"" + name + "\"! Check inputs!";
			break;
		}
		// Загрузка из файла
		case 8: {
			cout << "Enter the name of the file:\n";
			std::string name;
			cout << ">"; Table::inputString_from_cin(&name);
			int error_code = read_from_file(name);
			if (error_code == -665){
				cout << "You tryed to load the table but it is not empty.\n";
				cout << "Do you want to clear the table and try again? 1 - yes, 0 - no: ";
				int choice;
				cout << ">"; cin >> choice;
				if (choice == 1) {
					delete_table();
					read_from_file(name);
					last_msg = "Table was loaded from file \"" + name + "\"!";
				}
			}
			else if (error_code == -1){
				last_msg = "Table was NOT loaded from file \"" + name + "\"! Check if file exist!";
			}
			break;
		}
		// Поменять местами две колонки
		case 9: {
			cout << "Write the number of first column to swap: ";
			int column1;
			cout << ">"; cin >> column1;
			cout << "Write the number of second column to swap: ";
			int column2;
			cout << ">"; cin >> column2;
			if (_list_of_lists.swap_elements(column1, column2)) {
				_list_of_names.swap_elements(column1, column2);
				last_msg = "Columns [" + convertInt(column1) + "] and [" + convertInt(column2) + "] was swapped!";
			}
			else
				last_msg = "Columns [" + convertInt(column1) + "] and [" + convertInt(column2) + "] was NOT swapped! Check inputs!";
			break;
		}
		// Изменить целую строчку
		case 10: {
			cout << "Write the number of row to edit: ";
			int row;
			cout << ">"; cin >> row;
			for (int i = 0; i < _num_of_columns; i++) {
				cout << "Write the input for column[" + convertInt(i) +"]: ";
				std::string input;
				cout << ">"; inputString_from_cin(&input);
				edit_cell(i, row, input);
			}
			last_msg = "Row [" + convertInt(row) + "] was edited!";
			break;
		}
		// Стереть целую строчку
		case 11: {
			cout << "Write the number of row to delete: ";
			int row;
			cout << ">"; cin >> row;
			for (int i = 0; i < _num_of_columns; i++) {
				delete_cell(i, row);
			}
			break;
		}
		// Отсортировать таблицу по столбику
		case 12: {
			/*
			cout << "Write the number of first column to swap: ";
			int column1;
			cout << ">"; cin >> column1;
			cout << "Write the number of second column to swap: ";
			int column2;
			cout << ">"; cin >> column2;
			swap_rows(column1, column2);
			break;
			*/
			cout << "Write the number of column to sort: ";
			int column;
			cout << ">"; cin >> column;
			sort_by_column(column);
		}
		default:
			break;
		}
	}
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

void nTable::Table::edit_cell(int col, int row, std::string new_data)
{
	auto list_to_work = (List*)_list_of_lists[col]->data();
	auto len_of_this_list = list_to_work->len();
	// Иммем список с типом в _type
	if (len_of_this_list < row + 1) { // Если он короче, чем нужно
		while (len_of_this_list < row + 1) {
			list_to_work->append_empty();
			len_of_this_list++;
		}
		/*
		switch (list_to_work->get_type())
		{
		case 0: {
			while (len_of_this_list < row + 1) {
				list_to_work->append(new Int());
				len_of_this_list++;
			}
			break;
			}
		case 1: {
			while (len_of_this_list < row + 1) {
				list_to_work->append(new Double());
				len_of_this_list++;
			}
			break;
			}
		case 2: {
			while (len_of_this_list < row + 1) {
				list_to_work->append(new String());
				len_of_this_list++;
			}
			break;
			}
		}
		*/
	}
	(*list_to_work)[row]->data()->put(new_data);
}

void nTable::Table::clear_cell(int col, int row)
{
	auto cell_to_clear = get_cell(col, row);
	if (cell_to_clear) {
		edit_cell(col, row, "");
	}
}

void nTable::Table::delete_column(int col)
{
	_list_of_lists.remove_elem(col);
	_list_of_names.remove_elem(col);
	_num_of_columns--;
}

void nTable::Table::delete_cell(int col, int row)
{
	auto column_where_cell_to_delete_is = _list_of_lists[col];
	auto list_where_cell_to_delete_is = (List*)column_where_cell_to_delete_is->data();
	list_where_cell_to_delete_is->remove_elem(row);
}

void nTable::Table::delete_table()
{
	int num_of_cols = _num_of_columns;
	for (auto i = 0; i < num_of_cols; i++) {
		delete_column(0);
	}
}

void nTable::Table::swap_rows(int row1, int row2)
{
	auto max_row = row1 > row2 ? row1 : row2; // Максимум из номеров рядов
	for (auto i = 0; i < _num_of_columns; i++) {
		if (((List*)_list_of_lists[i]->data())->len() < max_row) { // Если в столбике нет элемента такого ряда
			edit_cell(i, max_row, ""); // Дополняем эти колонки
		}
	}
	//auto len_of_shotest_col = INT32_MAX; // Самая короткая колонка
	//for (auto i = 0; i < _num_of_columns; i++) {
	//	auto len_of_col = ((List*)_list_of_lists[i]->data())->len();
	//	if (len_of_col < len_of_shotest_col)
	//		len_of_shotest_col = len_of_col;
	//}
	//// Если длина одного из столбцов меньше запрашиваемого ряда, нужно дополнить эту колонку пустыми элементами
	//if (row1 > len_of_shotest_col || row2 > len_of_shotest_col) {
	//	auto max_row = row1 > row2 ? row1 : row2; // Максимум из номеров рядов
	//}
	for (auto i = 0; i < _num_of_columns; i++) {
		((List*)_list_of_lists[i]->data())->swap_elements(row1, row2);
	}
}

void nTable::Table::sort_by_column(int col)
{
	List* list_to_work = (List*)(_list_of_lists[col]->data());
	if (list_to_work) {
		auto len_of_list = list_to_work->len();
		// Простейшая сортировка пузырьком
		for (int i = 0; i < len_of_list; i++) {
			bool flag = true;
			for (int j = 0; j < len_of_list - (i + 1); j++) {
				if (*(*list_to_work)[j]->data() > *(*list_to_work)[j+1]->data()) {
					flag = false;
					swap_rows(j, j + 1);
				}
			}
			if (flag) {
				break;
			}
		}
	}
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

int nTable::Table::write_in_file(std::string file_name)
{
	std::ofstream output_file;
	output_file.open(file_name, std::ios::out);
	if (!output_file) {
		return -1; // Ошибка, не смогли открыть файл
	}
	output_file << *this;
	output_file.close();
	return 0;
}

int nTable::Table::read_from_file(std::string file_name)
{
	// Загружать таблицу можно только тогда, когда она пуста
	if (_list_of_lists.len() != 0)
		return -665; // Ошибка, таблица не пуста

	std::ifstream input_file;
	input_file.open(file_name, std::ios::in);
	if (!input_file) {
		return -1; // Ошибка, не смогли открыть файл
	}
	input_file >> *this;
	return 0;
}
