#pragma once
#include <iostream>
#include <sstream>

#define Int_TYPE typeid(Int).hash_code()
#define Double_TYPE typeid(Double).hash_code()
#define String_TYPE typeid(String).hash_code()

#define NUMBER_OF_TYPES 3 // Количество типов

class BaseType {
public:
	virtual		std::string		get() = 0;					// Возвращает строку - значение переменной
	inline 		void			put(const char mas[]);
	virtual		void			put(std::string) = 0;		// Записывает значение в переменную из строки
	virtual		size_t			hash_code() { return typeid(BaseType).hash_code(); }// Возвращает хеш код типа
	virtual						~BaseType() {}
};

void BaseType::put(const char mas[])
{
	std::string temp(mas);
	put(temp);
}

// Класс int-чисел
class Int : public BaseType {
				int*			_int;
public:
								Int();						// Пустой конструктор
								Int(int);
				std::string		get();						// Возвращает строку - значение переменной
				void			put(std::string str);		// Записывает значение в переменную из строки
				size_t			hash_code();				// Возвращает хеш код типа
								~Int();
};

// Класс double-чисел
class Double : public BaseType {
				double*			_double;
public:
								Double();					// Пустой конструктор
								Double(double);
				std::string		get();						// Возвращает строку - значение переменной
				void			put(std::string str);		// Записывает значение в переменную из строки
				size_t			hash_code();				// Возвращает хеш код типа
								~Double();
};

// Класс string
class String :public BaseType {
				std::string*	_string;
public:
								String();				   // Пустой конструктор
								String(std::string);
				std::string		get();					   // Возвращает строку - значение переменной
				void			put(std::string str);	   // Записывает значение в переменную из строки
				size_t			hash_code();				// Возвращает хеш код типа
								~String();
};

class Empty :public BaseType {
public:
				std::string		get();					   // Возвращает строку - значение переменной
				void			put(std::string str) {}		// Записывает значение в переменную из строки
				size_t			hash_code() { return 0; }	// Возвращает хеш код типа
};

// Определение функций классов Int, Double, String

inline Int::Int()
{
	_int = new int();
}

inline Int::Int(int in_int)
{
	_int = new int(in_int);
}

inline std::string Int::get()
{
	std::stringstream ss;
	ss << *_int;
	//auto str = new std::string();
	//*str = ss.str();
	//return str;
	return ss.str();
}

inline void Int::put(std::string str)
{
	try {
		*_int = std::stoi(str);  // Переводим строку в int
	}
	catch (std::invalid_argument) {
		*_int = 0;
	}
}

inline size_t Int::hash_code()
{
	return typeid(Int).hash_code();
}

inline Int::~Int()
{
	delete _int;
}

inline Double::Double()
{
	_double = new double();
}

inline Double::Double(double in_double)
{
	_double = new double(in_double);
}

inline std::string Double::get()
{
	std::stringstream ss;
	ss << *_double;
	//auto str = new std::string();
	//*str = ss.str();
	//return str;
	return ss.str();
}

inline void Double::put(std::string str)
{
	try {
		*_double = std::stod(str);  // Переводим строку в int
	}
	catch (std::invalid_argument) {
		*_double = 0;
	}
}

inline size_t Double::hash_code()
{
	return typeid(Double).hash_code();
}

inline Double::~Double()
{
	delete _double;
}

inline String::String()
{
	_string = new std::string();
}

inline String::String(std::string in_string)
{
	_string = new std::string(in_string);
}

inline std::string String::get()
{
	return _string?*_string:"N/A";
}

inline void String::put(std::string str)
{
	delete _string;
	auto new_string = new std::string(str);
	_string = new_string;
}

inline size_t String::hash_code()
{
	return typeid(String).hash_code();
}

inline String::~String()
{
	delete _string;
}

inline std::string Empty::get()
{
	return "N/A";
}


// Оператор вывода
inline std::ostream& operator<<(std::ostream& out, BaseType& var) {
	out << var.get();
	return out;
}
// Оператор ввода
inline std::istream& operator>>(std::istream& in, BaseType& var) {
	std::string temp;
	in >> temp;
	var.put(temp);
	return in;
}

