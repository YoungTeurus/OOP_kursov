#include "List.h"
#include <sstream>
#include <iostream>

#define TYPE_0 int
#define TYPE_1 double
#define TYPE_2 std::string

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

int main() {
	using namespace std;

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