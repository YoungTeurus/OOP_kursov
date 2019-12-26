#include "List.h"
#include <iostream>

#define ID0 int
#define ID1 double

double get(int col, int row) {
	int col = 0; // ��������� �������������
	int row = 0; // ��������� �������������
	auto type = typeid(ID0).hash_code(); // ������������ �� ���� ����������� �������

	double result;

	if (type == typeid(int).hash_code()) {
		int _result = *(((List<int>*)test2_list.get_elem(col)->_obj)->get_elem(row)->_obj);
		result = (double)_result;
	}
	else if (type == typeid(double).hash_code()) {
		double _result = *(((List<double>*)test2_list.get_elem(col)->_obj)->get_elem(row)->_obj);
		result = (double)_result;
	}
	if (result)
		cout << result;
}

int main() {
	using namespace std;

	List<BaseObject> test2_list;

	test2_list.append(new List<BaseObject>(new List<int>()));

	//auto col_1 = new List<BaseObject>(new List<int>);

	auto added_int = new int(5);

	// ���������� "5"
	/*
	{
		auto step_0 = test2_list.get_elem(0);
		auto step_1 = step_0->_obj;			// ������� ��������� �� ������ int-��.
		auto step_2 = (List<int>*)step_1;	// ������� ��������� � ������� ����.
		step_2->append(added_int);			// ���������� "5" � ������ ������
	}
	*/
	((List<int>*) test2_list.get_elem(0)->_obj)->append(added_int);
	

	// �������� "5"
	/*
	{
		auto _step_1 = col_1->_obj;				// ������� ��������� �� ������ int-��.
		auto _step_2 = (List<int>*)_step_1;		// ������� ��������� � ������� ����.
		auto _step_3 = _step_2->operator[](0);	// �������� ��������� �� ������ ������� ������ "int"-��
		auto _step_4 = *(_step_3->_obj);		// �������� ������, �������� � ������ �������.

		cout << _step_4 << "\n";					// ������� "5"
	}
	*/

	//test2_list.append(col_1); // ������� ������ ������� � ����� ������
	//test2_list._next = col_1;

	// �������� "5"
	/*
	{
		auto __step_1 = test2_list.get_elem(0); // �������� ��������� �� ������ ������� ������ ��������
		auto __step_2 = __step_1->_obj;			  // ������� ��������� �� ������ int-��.
		auto __step_3 = (List<int>*)__step_2;	  // ������� ��������� � ������� ����.
		auto __step_4 = __step_3->get_elem(0);  // �������� ��������� �� ������ ������� ������ "int"-��
		auto __step_5 = *(__step_4->_obj);		  // �������� ������, �������� � ������ �������.

		cout << __step_5 << "\n";; // ������� "5"
	}
	*/
	

	

	//cout << *(((List<int>*)test2_list.get_elem(col)->_obj)->get_elem(row)->_obj) << "\n";

	

	//cout << "Address of col_1: " << col_1 << "\n";

	//cout << "Address of added_int: " << added_int << "\n";

	return 0;
}









//auto step_1 = test2_list[0]; // �������� _obj ������� ��������
	//auto step_2 = (List<int>*)step_1; // ������� ���������� List � ������� ����
	//auto step_3 = step_2[0]; // �������� List<int> ������ �������� - ���, ��� �������� "5"
	//auto step_4 = step_3._obj; // �������� �������� ������
