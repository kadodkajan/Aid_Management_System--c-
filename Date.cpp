



#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cstring>
#include <ctime>
#include <iomanip>
#include "Utils.h"
#include "Date.h"


using namespace std;
namespace sdds 
{
	Date::Date()
	{

			int _year;
			int _month;
			int _day;
			bool y = true;
			Utils x;
			x.testMode(y);
			x.getSystemDate(&_year, &_month, &_day);
					
			year = _year;
			month = _month;
			day = _day;

	};
	bool Date:: operator==(const Date& ri)
	{
		if (unique_date(*this)== unique_date(ri))
		{
			return true;
		}
	
		return false;
	};
	bool Date::operator!=(const Date& ri)
	{
		if (unique_date(*this) != unique_date(ri))
		{
			return true;
		}

		return false;
	
	};
	bool Date::operator>(const Date& ri)
	{
		if (unique_date(*this) >unique_date(ri))
		{
			return true;
		}

		return false;
	};
	bool Date:: operator<(const Date& ri)
	{
		if (unique_date(*this) < unique_date(ri))
		{
			return true;
		}

		return false;
	
	};
	bool Date::operator<=(const Date& ri)
	{
		if (unique_date(*this) <= unique_date(ri))
		{
			return true;
		}

		return false;
	
	};
	bool Date::operator>=(const Date& ri)
	{

		if (unique_date(*this) >= unique_date(ri))
		{
			return true;
		}

		return false;
	
	};
	Date::operator bool()const
	{

		return date_state;

	};


	Date::Date(const int year_, const int month_, const int day_)
	{
		year = year_;
		month = month_;
		day = day_;
		validate();

	};
	 Date& Date::formatted(bool x)
	{
		if (x)
		{
		Formatted = x;

		}
		else
		{
			Formatted = false;


		}
		return *this;
	};


	const sdds::Status& Date::state()const
	{

		return date_state;
	};







	int  Date::unique_date(const Date& da) {

		return	da.year * 365 + da.month * 31 + da.day;

	};

	bool Date::validate() 
	
	{
		if (year>maximum_year_value||year<current_year)
		{
			date_state = "Invalid year in date";
			date_state = 1;
			return false;
		}
		else if(month>12||month<1)
		{
			date_state = "Invalid month in date";
			date_state = 2;
			return false;
		}
		else if (day<1|| day>max_day(month, year))
		{
			date_state = "Invalid day in date";
			date_state = 3;
			return false;
		}

		return true;
	};



	Date::~Date()
	{


	};


	int max_day(int month, int year)
	{
		int max_date;
		bool Leap_Year = false;

		if (year%4==0)
		{
			Leap_Year = true;
		}

		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) { max_date = 31; }
		else if (month == 2 && Leap_Year) { max_date = 29;
		}
		else if (month == 2 && !Leap_Year) {		

			max_date = 28;
		}
		else{max_date = 30;}


		return max_date;

	};
	std::ostream& Date::write(std::ostream& os) const
	{
		if (Formatted)
		{
			os<<year<<"/"<< std::setfill('0') << std::setw(2) <<month<<"/"<< std::setfill('0') << std::setw(2)<<day;

		}
		else
		{
			os << std::setfill('0') << std::setw(2) << year-2000  << std::setfill('0') << std::setw(2) << month<< std::setfill('0') << std::setw(2) << day;

		}

		return os;


	};
	


	std::istream& Date::read(std::istream& istr) 
	{
		int input;
		
		istr >> input;
		if (istr.fail())
		{
			date_state = "Invalid date value";
			date_state = 0;

		}
		else
		{

		if (input/10000==0)
		{

			time_t ttime = time(0);
			tm* local_time = localtime(&ttime);
			year = 1900 + local_time->tm_year;
			month = input / 100;
			day = input - (month * 100);

		}
		else
		{
			year = 2000+(input / 10000);
			month = (input - ((input / 10000) * 10000)) / 100;
			day = input - (((input / 10000) * 10000) + (month * 100));

		}
		}
		this->validate();

		if (!this->validate())
		{
			istr.setstate(ios::badbit);
		}

		
		return istr;

	};

	std::istream& operator>>(std::istream& istr,  Date& right)
	{

		return right.read(istr);
	};


	std::ostream& operator<<(std::ostream& ostr, const Date& right)
	{

		return right.write(ostr);

	};













 }