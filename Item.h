
#ifndef ITEM_H
#define ITEM_H
#include "Status.h"
#include "iProduct.h"
namespace sdds


{
	//iProduct{};
	class Item:public iProduct
	{
		double price;
		int quant;
		int n_quant;
		char* des;
		bool flag;

	protected:
		Status s;
		int sku;
		bool linear()const { return flag; };



	public:
		Item();
		void reset();
		Item(const Item&);
		Item& operator=(const Item&);
		int qtyNeeded()const;
		int qty()const;
		operator double()const;
		operator bool()const;
		int readSku(std::istream& istr);
		int operator-=(int qty);
		int operator+=(int qty);
		void linear(bool isLinear);
		void clear();
		 std::ofstream& save(std::ofstream& ofstr)const;
		 std::ifstream& load(std::ifstream& ifstr);
		std::ostream& display(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	    bool operator==(int sku)const;
		bool operator==(const char* description)const;




		~Item();

	

	};

	






}















#endif // !STATUS_H
