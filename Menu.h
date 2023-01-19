

#ifndef MENU_H
#define MENU_H


namespace sdds 
{
#define MAX_MENU 15
	class Menu
	{
		char* menu;
		unsigned  int num;



	public:
		Menu();
		Menu(const unsigned int,const char *);
		void set_menu(const unsigned int, const char*);
		//void print_menu()const;
		unsigned  int run()const;
		~Menu();

	private:

	};

	







}





























#endif // DEBUG