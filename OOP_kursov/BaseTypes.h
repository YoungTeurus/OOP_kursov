#pragma once
#include <iostream>
#include <sstream>

#define Int_TYPE typeid(Int).hash_code()
#define Double_TYPE typeid(Double).hash_code()
#define String_TYPE typeid(String).hash_code()

#define NUMBER_OF_TYPES 3 // Количество типов

class BaseType {
public:
	virtual		std::string*	type() = 0;						// Возвращает строку - название класса
	virtual		std::string		get() = 0;						// Возвращает строку - значение переменной
	inline 		void			put(const char mas[]);
	virtual		void			put(std::string) = 0;			// Записывает значение в переменную из строки
	virtual		size_t			hash_code() { return typeid(BaseType).hash_code(); }// Возвращает хеш код типа
	virtual						~BaseType() {}

	virtual		int				compare(BaseType*) = 0;			// Сравнение объектов
	virtual		void			add(BaseType*) = 0;				// Сложение объектов
	virtual		BaseType*		copy() = 0;						// Копия объекта

	inline		void			write_binary(std::ostream& os);	// Запись в бинарный файл
	inline		void			read_binary(std::istream& is);	// Чтение из бинарного файла

	inline		bool			operator==(BaseType& other);	//Переопределение оператора сравнения
	inline		bool			operator!=(BaseType& other);	//Переопределение оператора сравнения
	inline		bool			operator<(BaseType& other);		//Переопределение оператора сравнения
	inline		bool			operator>(BaseType& other);		//Переопределение оператора сравнения
	inline		bool			operator<=(BaseType& other);	//Переопределение оператора сравнения
	inline		bool			operator>=(BaseType& other);	//Переопределение оператора сравнения
};

void BaseType::put(const char mas[])
{
	std::string temp(mas);
	put(temp);
}

inline void BaseType::write_binary(std::ostream& os)
{
	auto str = get();
	long int len = str.length();
	os.write((const char*)&len, sizeof len);
	os.write(str.c_str(), len);
}

inline void BaseType::read_binary(std::istream& is)
{
	std::string str_to_put;
	long int len;
	is.read((char*)&len, sizeof len);
	str_to_put.resize(len);
	is.read(&str_to_put[0], len);
}

inline bool BaseType::operator==(BaseType& other)
{
	return compare(&other) == 0;
}

inline bool BaseType::operator!=(BaseType& other)
{
	return compare(&other) != 0;
}

inline bool BaseType::operator<(BaseType& other)
{
	return compare(&other) < 0;
}

inline bool BaseType::operator>(BaseType& other)
{
	return compare(&other) > 0;
}

inline bool BaseType::operator<=(BaseType& other)
{
	return compare(&other) <= 0;
}

inline bool BaseType::operator>=(BaseType& other)
{
	return compare(&other) >= 0;
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

				std::string*	type();						// Возвращает строку - название класса
				int				compare(BaseType*);			// Сравнение объектов
				void			add(BaseType*);				// Сложение объектов
				BaseType*		copy();						// Копия объекта
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

				std::string*	type();						// Возвращает строку - название класса
				int				compare(BaseType*);			// Сравнение объектов
				void			add(BaseType*);				// Сложение объектов
				BaseType*		copy();						// Копия объекта
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

				std::string*	type();						// Возвращает строку - название класса
				int				compare(BaseType*);			// Сравнение объектов
				void			add(BaseType*);				// Сложение объектов
				BaseType*		copy();						// Копия объекта
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

inline std::string* Int::type()
{
	return new std::string(typeid(Int).name());
}

inline int Int::compare(BaseType* other)
{
	if (other->hash_code() == hash_code()) {
		auto temp_Int = new Int(*_int * -1);
		temp_Int->add(other);
		auto result = *(temp_Int->_int);
		delete temp_Int;
		if (result == 0)
			return 0;
		if (result < 0)
			return 1;
		return -1;
	}
	return -100;
}

inline void Int::add(BaseType* other)
{
	if (other->hash_code() == hash_code()) {
		(*_int) += *(((Int*)other)->_int);
	}
}

inline BaseType* Int::copy()
{
	return new Int(*this);
}

inline Double::Double()
{
	_double = new double();
}

inline Double::Double(double dbl)
{
	_double = new double(dbl);
}

inline std::string Double::get()
{
	std::stringstream ss;
	ss << *_double;
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

inline std::string* Double::type()
{
	return new std::string(typeid(Double).name());
}

inline int Double::compare(BaseType* other)
{
	if (other->hash_code() == hash_code()) {
		auto temp_Int = new Double(*_double * -1);
		temp_Int->add(other); //
		auto result = *(temp_Int->_double);
		delete temp_Int;
		if (result == 0)
			return 0;
		if (result < 0)
			return 1;
		return -1;
	}
	return -100;
}

inline void Double::add(BaseType* other)
{
	if (other->hash_code() == hash_code()) {
		(*_double) += *(((Double*)other)->_double);
	}
}

inline BaseType* Double::copy()
{
	return new Double(*this);
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

inline std::string* String::type()
{
	return new std::string(typeid(String).name());
}

inline int String::compare(BaseType* other)
{
	if (other->hash_code() == hash_code()) {
		return strcmp((*this)._string->c_str(), (*(String*)other)._string->c_str());
	}
	return -100;
}

inline void String::add(BaseType* other)
{
	*(*this)._string += *(*(String*)other)._string;
}

inline BaseType* String::copy()
{
	return new String(*this);
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

