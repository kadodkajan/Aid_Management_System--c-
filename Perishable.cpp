

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>

#include <ctime>
//#include "iProduct.h"
//#include "Item.h"
#include "Perishable.h"
#include "Utils.h"
using namespace std;
namespace sdds 
{
	Utils h;

	Perishable::Perishable()
	{
		instruct = nullptr;

	}
	Perishable::Perishable(const Perishable&src)
	{
		this->instruct = nullptr;
		*this = src;

	
	};
	Perishable& Perishable:: operator=(const Perishable&src)
	{
		if (this != &src)
		{

			h.alocpy(instruct, src.instruct);


		}
		return *this;
	
	
	
	};
	const Date& Perishable::expiry()const
	{

		return exp;
	};
	int Perishable::readSku(std::istream& istr)
	{

		cout << "SKU: ";
		sku = h.getInt(10000, 39999, "sd");


		return sku;
	};
	std::ofstream& Perishable::save(std::ofstream& ofstr)const
	{
		Item::save(ofstr);

		ofstr << '\t';
		if (instruct!=nullptr &&exp)
		{
			ofstr << instruct ;

		}
		ofstr<< '\t';
		const_cast <Perishable*>(this)->exp.formatted(false);
		ofstr << exp;
		const_cast <Perishable*>(this)->exp.formatted(true);

		return ofstr;
	};
	std::ifstream& Perishable::load(std::ifstream& ifstr)
	{
		Item::load(ifstr);
		std::string temp;
		getline(ifstr, temp, '\t');
		//ifstr.ignore(10, '\t');
		exp.read(ifstr);
		ifstr.ignore();
		if (ifstr.fail())
		{
			s = "Input file stream read (perishable) failed!";
		}
		h.alocpy(instruct, temp.c_str());
		return ifstr;
	};
	Perishable::~Perishable()
	{
		delete[]instruct;
		instruct = nullptr;
	}

	std::ostream& Perishable::display(std::ostream& ostr)const
	{
		if (!s)
		{
			ostr << s;
		}
		else if(linear())
		{
			Item::display(ostr);
			if (instruct!=nullptr && strlen(instruct)>0)
			{
				ostr << '*';
			}
			else
			{
				ostr << ' ';
			}
			ostr << exp;
		}
		else
		{
			ostr << "Perishable ";
			Item::display(ostr);
			ostr << "Expiry date: ";
			ostr << exp<<endl;
			if (instruct != nullptr && strlen(instruct) > 0)
			{
				ostr << "Handling Instructions: "<<instruct<<endl;
			}

		}


		return ostr;

	};
	std::istream& Perishable::read(std::istream& istr)
	{
	
		Item::read(istr);
		std::string temp;
		if (instruct!=nullptr)
		{
			delete[]instruct;
			instruct = nullptr;
		}
		cout << "Expiry date (YYMMDD): ";
		istr >> exp;
		istr.ignore();
		cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek()!='\n')
		{
			getline(istr, temp, '\n');
			h.alocpy(instruct, temp.c_str());
			instruct[temp.length()] = '\0';
		}
		if (istr.fail())
		{
			s = "Perishable console date entry failed!";
		}
		return istr;
	};






}