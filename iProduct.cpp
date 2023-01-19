


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <ctime>
#include "iProduct.h"
//#include "Item.h"


#include "Utils.h"
using namespace std;
namespace sdds {

	std::ostream& operator<<(std::ostream& ostr, const iProduct& sh)
	{
		sh.display(ostr);
		return ostr;
	};

	std::istream& operator>>(std::istream& istr, iProduct& sh) {
		sh.read(istr);
		return istr;
	};









}