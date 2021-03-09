#pragma once
#include <iostream>
#define rcastc reinterpret_cast<char*>
#define rcastcc reinterpret_cast<const char*>
class Date
{
public:
	enum class Month {
		JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6, JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12
	};
	Date(std::istream& in);
	Date() = default;
	Date(size_t month, size_t day, size_t year);
	Date(size_t year) :Date(1, 1, year) {}
	bool setYear(size_t year) { this->year = year; }
	void setMont(Month month) { this->month = month; }
	bool setDay(size_t day) { this->day = day; }
	friend std::ostream& operator<<(std::ostream& os, const Date& cit);

	Month getMonth()const { return month; }
	size_t getDay()const { return day; }
	size_t getYear() const{ return year; }

	void load(std::istream& in);
	void save(std::ostream& out)const;

private:
	Month month;
	size_t year;
	size_t day;
};