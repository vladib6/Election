#pragma once
#include<iostream>
#include <ctype.h>
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>

const size_t MAXSIZE = 50;

class STRING
{
public:
	//CTORS AND DTORS
	STRING();
	STRING(std::istream& in);
	STRING(const char* string);
	STRING(const STRING& rhs);
	~STRING();

	//GETTER FUNCTION
	char* getString()const { return string; }

	//SETTER FUNCTIONS
	void setString(char* str);
	void setString(STRING& str);
	void getStrInput();
	//INFO RETRIEVAL
	int strCmp(const STRING& rhs)const;

	//TEXT MANIPULATION
	bool convertToUpper();
	bool convertToLower();
	void strCpy(char* dest, const char* source);
	char* dupString(const char* str);
	//CLASS OPERATORS
	STRING& operator+(const STRING&);
	STRING& operator+(const char*);
	STRING& operator+(const char);
	STRING& operator+=(const STRING&);
	STRING& operator+=(const char*);
	STRING& operator+=(const char);
	bool operator==(const STRING& rhs)const { return !strCmp(rhs); }
	bool operator==(const char* rhs) const{ return !strcmp(this->string, rhs); }
	STRING& operator=(const STRING&);
	STRING& operator=(const char*);
	char& operator*() { return *string; }
	char& operator[](int index) { return string[index]; }
	friend std::ostream& operator<<(std::ostream& os, const STRING& string);
	void save(std::ostream& _out)const;
	void load(std::istream& _in);//to be done

private:
	char* string;
	size_t size;
	size_t phySize;

};

