#include "List.h"
#include <iostream>

#define TYPE_0 int
#define TYPE_1 double

bool add_column(List<BaseObject>* list, int id) {
	if (id == 0) {
		list->append(new List<BaseObject>(new List<TYPE_0>(typeid(TYPE_0).hash_code()))); // Создание столбика int-ов
	}
	else if (id == 1) {
		list->append(new List<BaseObject>(new List<TYPE_1>(typeid(TYPE_1).hash_code()))); // Создание столбика double-ов
	}
	else {
		std::cout << "The type of created column is not defined!" << "\n";
		return false;
	}
	return true;
}

double get_cell(List<BaseObject>* list, int col, int row) {
	auto type = typeid(int).hash_code(); // Определяется из типа создаваемой колонки

	double result;
	bool was_result_get = false; // Был ли получен результат?

	auto always_get = list->get_elem(col)->get_obj(); // Всегда пытаемся найти нужный столбик. Если его нет - получим nullptr

	if (type == typeid(TYPE_0).hash_code()) {
		auto a = (((List<TYPE_0>*)list->get_elem(col)->get_obj())->get_elem(row)->get_obj());
		if (a) {
			TYPE_0 _result = *a;
			result = (double)_result;
			was_result_get = true;
		}

	}
	else if (type == typeid(TYPE_1).hash_code()) {
		auto a = (((List<TYPE_1>*)list->get_elem(col)->get_obj())->get_elem(row)->get_obj());
		if (a) {
			TYPE_1 _result = *a;
			result = (double)_result;
			was_result_get = true;
		}
	}
	else {
		std::cout << "The type of cell [" << col << ";" << row << "] is not defined!" << "\n";
		return 0.0;
	}

	if (!was_result_get)
		std::cout << "The cell[" << col << ";" << row << "] is empty!" << "\n";

	return &result?result:0.0;
}

int main() {
	using namespace std;

	List<BaseObject> test2_list;

	add_column(&test2_list, 0);

	auto added_int = new int(5);

	
	((List<int>*) test2_list.get_elem(0)->get_obj())->append(added_int); // Запись в первый столбик
	
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
	
	cout << get_cell(&test2_list, 0, 0);

	return 0;
}