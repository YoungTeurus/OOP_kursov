#pragma once

class BaseObject {
public:
	virtual		int				type() = 0;				// ����������� ����������� ���� �������
	virtual		const char*		name() = 0;				// ����������� ��� ���� �������
	//virtual		void			append(BaseObject* elem) = 0;
};