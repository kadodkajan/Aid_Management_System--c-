
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include"Status.h"
#include "Utils.h"
#include "Menu.h"


using namespace std;

namespace sdds
{

	Utils hel;
	Menu::Menu()
	{
		menu = nullptr;
		num = 0;
	}



	Menu::Menu(const unsigned int num_, const char* src)
	{
		if (src != nullptr && num < MAX_MENU)
		{
			hel.alocpy(menu, src);

			num = num_;
		}
		else
		{
			menu = nullptr;
			num = 0;
		}

	}
	void Menu::set_menu(const unsigned int num_, const char* src)
	{
		if (src != nullptr && num_ < MAX_MENU)
		{
			menu = nullptr;
			hel.alocpy(menu, src);

			num = num_;
		}
		else
		{
			menu = nullptr;
			num = 0;
		}

	};

	unsigned  int Menu::run()const
	{
		cout << menu;
		cout << "0- Exit\n" << "> ";

		return hel.getInt(0, num, menu);

	};


	Menu::~Menu()
	{

		delete[]menu;
		menu = nullptr;
	}





}