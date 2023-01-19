

#ifndef DATE_H
#define DATE_H
#define maximum_year_value 2030
#define current_year 2020
#include "Status.h"
namespace sdds 

{


	class Date
	{
		int year;
		int month;
		int day;
		sdds::Status date_state;
		 bool Formatted={true};




	public:
		Date();
		Date(const int, const int, const int);
		 Date& formatted(bool x= true);
		bool operator==(const Date&ri);
		bool operator!=(const Date&ri);
		bool operator>(const Date&ri);
		bool operator<(const Date&ri);
		bool operator<=(const Date&ri);
		bool operator>=(const Date&ri);
		const sdds::Status& state()const;
		operator bool()const;
		bool validate();
		int unique_date(const Date&da);
		std::ostream& write(std::ostream& os) const;
		std::istream& read(std::istream& istr) ;

		~Date();



	};

	

	







	std::ostream& operator<<(std::ostream& ostr, const Date& right);
	std::istream& operator>>(std::istream& istr,  Date& right);

	int max_day(int month, int year);
}









#endif // !DATE_H
