#include "List.h"
#include <iostream>



double get_cell(List<BaseObject>* test2_list, int col, int row) {
	auto type = typeid(int).hash_code(); // ������������ �� ���� ����������� �������

	double result;

	if (type == typeid(int).hash_code()) {
		auto a = (((List<int>*)test2_list->get_elem(col)->get_obj())->get_elem(row)->get_obj());
		if (a) {
			int _result = *a;
			result = (double)_result;
		}

	}
	else if (type == typeid(double).hash_code()) {
		double _result = *(((List<double>*)test2_list->get_elem(col)->get_obj())->get_elem(row)->get_obj());
		result = (double)_result;
	}

	return &result?result:0.0;
}

int main() {
	using namespace std;

	List<BaseObject> test2_list;

	test2_list.append(new List<BaseObject>(new List<int>(typeid(int).hash_code()))); // �������� �������� "int"-��

	

	auto added_int = new int(5);

	
	((List<int>*) test2_list.get_elem(0)->get_obj())->append(added_int); // ������ � ������ �������
	
	// ��� ��� ����������
	{
		// ���������� "5"
		/*
		{
			auto step_0 = test2_list.get_elem(0);
			auto step_1 = step_0->get_obj();			// ������� ��������� �� ������ int-��.
			auto step_2 = (List<int>*)step_1;	// ������� ��������� � ������� ����.
			step_2->append(added_int);			// ���������� "5" � ������ ������
		}
		*/

		// �������� "5"
		/*
		{
			auto __step_1 = test2_list.get_elem(0); // �������� ��������� �� ������ ������� ������ ��������
			auto __step_2 = __step_1->get_obj();			  // ������� ��������� �� ������ int-��.
			auto __step_3 = (List<int>*)__step_2;	  // ������� ��������� � ������� ����.
			auto __step_4 = __step_3->get_elem(0);  // �������� ��������� �� ������ ������� ������ "int"-��
			auto __step_5 = *(__step_4->get_obj());		  // �������� ������, �������� � ������ �������.

			cout << __step_5 << "\n";; // ������� "5"
		}
		*/
	}
	
	cout << get_cell(&test2_list, 0, 0);

	return 0;
}