
#ifndef PERISHABLE_H
#define PERISHABLE_H
//#include "iProduct.h"
#include "Item.h"
#include "Date.h"

namespace sdds 
{

	class Perishable :public Item

	{
		Date exp;
		char* instruct;
	public:
		Perishable();
		Perishable(const Perishable&);
		Perishable& operator=(const Perishable&);
		const Date& expiry()const;
		int readSku(std::istream& istr);
		std::ofstream& save(std::ofstream& ofstr)const;
		std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);

		~Perishable();

	private:

	};

	



}

#endif // !PERISHABLE_H
