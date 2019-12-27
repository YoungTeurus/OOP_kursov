#pragma once

class BaseObject {
public:
	virtual		size_t			type() = 0;				// ����������� ����������� ���� �������
	virtual		const char*		name() = 0;				// ����������� ��� ���� �������
	virtual		size_t			get_type() = 0;			// ���������� ���-����� ���� ���������, �������� � ������
	virtual						~BaseObject() {};
};