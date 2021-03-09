#include "Date.h"

std::ostream& operator<<(std::ostream& os, const Date& cit)
{
	os << "Date: "<<cit.day << "/" << static_cast<int>(cit.month) << "/" << cit.year;

	return os;
}



Date::Date(std::istream& in)
{
	in.read(rcastc(&day), sizeof(day));
	in.read(rcastc(&month), sizeof(month));
	in.read(rcastc(&year), sizeof(year));
}

Date::Date(size_t month, size_t day, size_t year) :month(static_cast<Month>(month)), day(day), year(year) {}

void Date::load(std::istream& in)
{
	in.read(rcastc(&day), sizeof(day));
	in.read(rcastc(&month), sizeof(month));
	in.read(rcastc(&year), sizeof(year));

}

void Date::save(std::ostream& out)const
{
	out.write(rcastcc(&day), sizeof(day));
	out.write(rcastcc(&month), sizeof(month));
	out.write(rcastcc(&year), sizeof(year));
}