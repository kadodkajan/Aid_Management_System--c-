



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include"Status.h"
#include "Utils.h"



using namespace std;
namespace sdds 
{

	Status::Status()
	{
		description = nullptr;
		code = 0;
	};

	Status::Status(int x, char* des ) 	
	{

		if (des!=nullptr)
		{
			description = new char[strlen(des) + 1];
			strcpy(description, des);
			description[strlen(des)] = '\0';
			code = 0;

		}
		else
		{
			description = nullptr;
			code = 0;

		}
	};

	Status::Status(const Status& source)
	{

		if (this!=&source)
		{
	
		if (source.description!=nullptr)
		{
			description = nullptr;
			alocpy(description, source.description);

		}
		code = source.code;


		}

	
	};

	void Status::alocpy(char*& destination, const char* source) 
	{
		if (destination!=nullptr)//&& this->operator bool()!=NULL
		{
			delete[]destination;
			destination = nullptr;

		}
		if (source != nullptr)
		{
			destination = new char[strlen(source) + 1];
			strcpy(destination, source);
			destination[strlen(source)] = '\0';

		}



	};

	Status& Status::operator=(const Status&source)
	{

		if (this != &source)
		{

			if (source.description != nullptr)
			{
				alocpy(description, source.description);

			}
			code = source.code;


		}
		return *this;

	};



	Status::~Status()
	{
		delete[]description;
		description = nullptr;
	};


	Status Status::operator=(const int x)
	{
		code = x;
		return *this;
	};
	Status Status:: operator=(const char*src)
	{
		alocpy(description, src);
		return *this;
	};

	Status::operator bool()const
	{
		if (description==nullptr)
		{
			return true;
		}


		return false;

	};
	Status::operator char* ()const
	{
		return description;

	};

	Status::operator int ()const
	{
		return code;

	};

	Status& Status::clear()
	{
		if (this->operator bool())
		{
			delete[]description;
			description = nullptr;
			
		}

		code = 0;

		return *this;

	};
	std::ostream& Status::print(std::ostream& os) const 
	{
		if (code==0)
		{
		os << description;

		}
		else
		{
			os << "ERR#"<<code<<": "<<description;

		}

		return os;

	};


	std::ostream& operator<<(std::ostream& ostr, const Status& right) 
	{

	 return right.print(ostr);
		
	};





	

};
