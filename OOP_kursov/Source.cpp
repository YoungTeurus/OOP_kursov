#include "Table.h"
#include <iostream>
#include <stdlib.h>


/*
std::string convertInt(int number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}
std::string convertDouble(double number)
{
	std::stringstream ss;
	ss << number;
	return ss.str();
}

bool add_column(List<BaseObject>* list, int id) {
	if (id == 0) {
		list->append(new List<BaseObject>(new List<TYPE_0>(typeid(TYPE_0).hash_code()))); // Создание столбика int-ов
	}
	else if (id == 1) {
		list->append(new List<BaseObject>(new List<TYPE_1>(typeid(TYPE_1).hash_code()))); // Создание столбика double-ов
	}
	else if (id == 2) {
		list->append(new List<BaseObject>(new List<TYPE_2>(typeid(TYPE_2).hash_code()))); // Создание столбика string-ов
	}
	else {
		std::cout << "The type of created column is not defined!" << "\n";
		return false;
	}
	return true;
}

template<typename T>
bool append_in_column(List<BaseObject>* list, T* element, int num_of_column) {

	auto always_get = list->get_elem(num_of_column)->get_obj(); // Всегда пытаемся найти нужный столбик. Если его нет - получим nullptr
	if (always_get) {
		if (always_get->get_type() == typeid(*element).hash_code()) { // Если тип храним объектов совпадает с передаваемым
			((List<T>*)always_get)->append(element); // Запись в этот столбик
			return true;
		}
	}
	std::cout << "Was not able to find column [" << num_of_column << "]!\n";
	return false;
}

std::string get_cell(List<BaseObject>* list, int col, int row) {
	auto type = typeid(int).hash_code(); // Определяется из типа создаваемой колонки

	std::string result;
	bool was_result_get = false; // Был ли получен результат?

	auto always_get = list->get_elem(col)->get_obj(); // Всегда пытаемся найти нужный столбик. Если его нет - получим nullptr

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

	if (!was_result_get)
		std::cout << "The cell[" << col << ";" << row << "] is empty!" << "\n";

	return result;
}
*/

int main() {
	using namespace std;
	srand(12341241);

	Table tbl;

	tbl.add_column(0, "Index");
	tbl.add_column(0, "Int");
	tbl.add_column(1, "Double");
	tbl.add_column(2, "Std::string");
	for (int i = 0; i < 5; i++) {
		tbl.append_in_column(new int(i),0);
		tbl.append_in_column(new int(rand()%10001 - 5000), 1); // Запись числа "i" в первый столбик
		tbl.append_in_column(new double(rand() % 10001 - 5000 + 3.5), 2);
		tbl.append_in_column(new std::string("Wow it is " + Table::convertInt(i) + " element!"), 3);
	}
	tbl.beauty_print();

	while (true) {
		cout << "What to do?\n";
		cout << "1. Add new column\n";
		cout << "2. Add new cell in column\n";
		cout << "3. Edit cell in column\n";
		cout << "4. Print whole table\n";
		int choise;
		cin >> choise;
		switch (choise)
		{
		case 1: { // Добавление столбца
			cout << "Enter the type of new column:\n";
			cout << "1. int\n";
			cout << "2. double\n";
			cout << "3. std::string\n";
			int choise;
			cin >> choise;
			cout << "Enter the name of new column:\n";
			std::string name;
			std::getline(std::cin, name);
			if (choise >= 1 && choise <= 3) {
				tbl.add_column(choise-1, name);
			}
			else
				cout << "You selected wrong type! Try again.\n";
			break;
		}
		case 2: {
			cout << "Write the number of column to add cell: ";
			int column;
			cin >> column;
			tbl.get_in_column(column);
			break;
		}
		case 4: {
			tbl.beauty_print();
			break;
		}
		default:
			cout << "You selected wrong task! Try again.\n";
			break;
		}
	}

	/*
	List<BaseObject> test2_list;

	add_column(&test2_list, 0); // Столбик 0 - int-ы
	add_column(&test2_list, 1); // Столбик 1 - double-ы
	add_column(&test2_list, 2); // Столбик 2 - std::string-и

	for (int i = 0; i < 10; i++) {
		append_in_column(&test2_list, new int(i), 0); // Запись числа "i" в первый столбик
		append_in_column(&test2_list, new double(i+3.5), 1);
		append_in_column(&test2_list, new std::string("Wow it is " + convertInt(i)), 2);
	}

	for (int i = 0; i < 10; i++) {
		cout << get_cell(&test2_list, 0, i) <<"  "
			 << get_cell(&test2_list, 1, i) <<"  " 
			 << get_cell(&test2_list, 2, i) << "\n"; // Вывод первой ячейки первого столбика
	}
	*/
	
	// Код для объяснений
	{
		// Записываем "5"
		/*
		{
			auto step_0 = test2_list.get_elem(0);
			auto step_1 = step_0->get_obj();			// Достали указатель на список int-ов.
			auto step_2 = (List<int>*)step_1;	// Привели указатель к нужному виду.
			step_2->append(added_int);			// Записываем "5" в данный список
		}
		*/

		// Получаем "5"
		/*
		{
			auto __step_1 = test2_list.get_elem(0); // Получили указатель на первый элемент списка столбцов
			auto __step_2 = __step_1->get_obj();			  // Достали указатель на список int-ов.
			auto __step_3 = (List<int>*)__step_2;	  // Привели указатель к нужному виду.
			auto __step_4 = __step_3->get_elem(0);  // Получили указатель на первый элемент списка "int"-ов
			auto __step_5 = *(__step_4->get_obj());		  // Получили объект, хранимый в первом объекте.

			cout << __step_5 << "\n";; // Выводим "5"
		}
		*/
	}
	
	

	return 0;
}