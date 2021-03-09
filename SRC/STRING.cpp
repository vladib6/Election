#include "STRING.h"

STRING::~STRING() {
	if (string)
		delete[](string);
}

void STRING::strCpy(char* dest, const char* source) {
	for (size_t i = 0; i <=strlen(source); i++) {
		dest[i] = source[i];
	}

}
char* STRING::dupString(const char* str) {
	phySize = strlen(str) + 1;
	char* result = new char[phySize];

	strCpy(result, str);

	return result;
}

STRING::STRING() :size(0),phySize(0), string(nullptr) {
}
STRING::STRING(const STRING& rhs) : STRING(rhs.string) {

}

STRING::STRING(const char* string) {
	if (string) {
		this->string = dupString(string);
		this->size = strlen(string);
	}
}

std::ostream& operator<<(std::ostream& os, const STRING& rhs) {
	os << rhs.string;
	return os;
}

STRING& STRING::operator+(const STRING& rhs) {
	*this = *this + rhs.string;
	return *this;
}
STRING& STRING::operator+(const char* rhs) {
	size_t argSize = strlen(rhs);
	char* result = new char[this->size + argSize + 1];
	size_t i{};
	for (i = 0; i < this->size; i++) {
		result[i] = this->string[i];
	}
	for (size_t j = 0; j <= argSize; i++, j++) {
		result[i] = rhs[j];
	}

	delete[](string);
	string = result;
	size = strlen(result);

	return *this;
}


STRING& STRING::operator+(const char rhs) {
	char* result = new char[(++size) + 1];
	strCpy(result, string);
	result[size] = '\0';
	result[size - 1] = rhs;

	delete[](string);
	string = result;
	return *this;

}

int STRING::strCmp(const STRING& rhs)const {
	return strcmp(this->string, rhs.string);
}

STRING& STRING::operator+=(const STRING& rhs) {
	*this = *this + rhs;
	return *this;
}
STRING& STRING::operator+=(const char* rhs) {
	*this = *this + rhs;
	return *this;
}
STRING& STRING::operator+=(const char rhs) {
	*this = *this + rhs;
	return *this;
}

STRING& STRING::operator=(const STRING& rhs) {
	*this = rhs.string;
	return *this;
}
STRING& STRING::operator=(const char* rhs) {
	size = strlen(rhs);
	char* result = dupString(rhs);
	if (string)
		delete[](string);
	string = result;
	return *this;

}


bool STRING::convertToLower() {
	bool converted = true;
	for (int i = 0; i < this->size; i++) {
		if (isupper(string[i])) {
			string[i] += ('a' - 'A');
			converted = islower(string[i] -= ('a' - 'A'));
			if (!converted)
				return converted;
		}
	}
	return converted;
}

bool STRING::convertToUpper() {
	bool converted = true;
	for (int i = 0; i < this->size; i++) {
		if (islower(string[i])) {
			converted = isupper(string[i] -= static_cast<char>('a' - 'A'));
			if (!converted)
				return converted;
		}
	}

	return true;
}

void STRING::setString(char * str)
{
	if(string)
	     delete[] string;

	string = dupString(str);
	size = strlen(string);
}

void STRING::setString(STRING & str)
{
	if (string)
		delete[] string;
	string = dupString(str.getString());
	size = strlen(string);
}

void STRING::getStrInput() { string = new char[MAXSIZE+1]; std::cin.getline(string, MAXSIZE); phySize = MAXSIZE; }

void STRING::save(std::ostream& out)const {
	out.write(rcastcc(&size), sizeof(size));
	out.write(string, sizeof(char) * (size + 1));
}
void STRING::load(std::istream& _in) {
	_in.read(rcastc(&size), sizeof(size_t));
	string = new char[(size + 1) * 2];
	_in.read(string, sizeof(char) * (size+1));
}
STRING::STRING(std::istream& _in) {
	this->load(_in);
}
