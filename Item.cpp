



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include<iomanip>
#include <ctime>
#include "iProduct.h"
#include "Item.h"
#include "Utils.h"


using namespace std;
namespace sdds {
	Utils help;
	Item::Item()
	{	
		reset();
	}
	void Item::reset()
	{
		price = 0;
		quant = 0;
		n_quant = 0;
		des = nullptr;
		flag = false;
	};

	Item::Item(const Item& source)
	{
		*this = source;
		
		
	};

	Item& Item::operator=(const Item& source)
	{
		if (this != &source)
		{

			if (source.des != nullptr)
			{
				help.alocpy(des, source.des);

			}
			price = source.price;
			quant = source.quant;
			n_quant = source.n_quant;
			flag = source.flag;



		}
		return *this;

	};
	int Item::qtyNeeded()const
	{
		return n_quant;
	};
	int Item::qty()const
	{
		return quant;
	};
	Item::operator double()const {

		return price;
	};
	Item::operator bool()const {
		return flag;

	};
	int Item:: operator-=(int qty)
	{
		quant -= qty;
		return quant;
	};
	int Item::operator+=(int qty)
	{
		quant += qty;
		return quant;
	};
	void Item::linear(bool isLinear)
	{
		flag = isLinear;
	};
	void Item::clear() 
	{
		s.clear();
	};

	bool Item::operator==(int sku_)const
	{

		return sku == sku_;
	};
	bool Item::operator==(const char* description)const
	{
		if (strstr(des, description) != nullptr) {
			return true;
		}
		return false;
	};
	std::ofstream& Item::save(std::ofstream& ofstr)const
	{
		if (s)
		{
			ofstr << sku << "\t" << des << "\t" << quant << "\t" << n_quant << "\t" << price;

		}
		return ofstr;
	};
	std::ifstream& Item::load(std::ifstream& ifstr) 
	{
		if (des!=nullptr)
		{
			delete[]des;
			des = nullptr;
		}
		std::string temp;
		ifstr >> sku;
		ifstr.ignore(10, '\t');
		getline(ifstr, temp,'\t');
		ifstr >> quant;
		ifstr.ignore(10, '\t');
		ifstr >> n_quant;
		ifstr.ignore(10, '\t');
		ifstr >> price;
		ifstr.ignore();

		help.alocpy(des, temp.c_str());
		if (ifstr.fail())
		{
			s = "Input file stream read failed!";
		}


		return ifstr;
	};
	std::ostream& Item::display(std::ostream& ostr)const 
	{
		if (!s)
		{

			ostr << s;
		}
		else
		{
			char print[36];
			strncpy(print, des, 35);
			if (strlen(des)>35)
			{
				print[35] = '\0';

			}
			if (flag)
			{

			ostr<< sku<<std::setfill(' ') << " | " <<setw(35)<<left<< print << " | " << setw(4)<<right<< quant << " | " <<setw(4)<< n_quant << " | "  << setw(7) << std::fixed << std::setprecision(2)  << price<< " |";
			}
			else
			{
				ostr << "AMA Item:\n" << sku << ": " << des << "\n" << "Quantity Needed: " << n_quant << endl << "Quantity Available: " << quant << endl << "Unit Price: $" <<std::fixed << std::setprecision(2)<< price << endl <<
					"Needed Purchase Fund: $" <<std::fixed << std::setprecision(2) <<(n_quant - quant) * price << endl;
			}
		}

		return ostr;
	};







	int Item::readSku(std::istream& istr) 
	{

		cout << "SKU: ";
		sku = help.getInt(40000, 99999,"sd");


		return sku;
	};


	std::istream& Item::read(std::istream& istr)
	{
		delete[] des;
		std::string tem;
		des = nullptr;
		clear();
		cout << "AMA Item:\n";
		sku=readSku(istr);
		istr.ignore();
		cout << "Description: ";
		getline(istr, tem, '\n');
	//	istr >> tem;
		help.alocpy(des, tem.c_str());
		cout << "Quantity Needed: ";
		n_quant= help.getInt(1, 9999, "sd");
		cout << "Quantity On Hand: ";
		quant= help.getInt(0, n_quant, "sd");
		cout << "Unit Price: $";
		price= help.getDouble(0.00, 9999.00, "sd");











		if (istr.fail())
		{
			s = "Console entry failed!";
		}

		return istr;
	};
	

	Item::~Item()
	{
		delete[] des;
		des = nullptr;

	}








}