
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <iomanip>

#include"Status.h"
#include"AidMan.h"
#include "Date.h"
#include "Utils.h"
//#include "iProduct.h"
#include"Item.h"
#include "Perishable.h"
using namespace std;


namespace sdds {
	Date d;
	Utils he;

	AidMan::AidMan()
	{

		filename = nullptr;
		M.set_menu(7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n");
	}


	AidMan::~AidMan()
	{
		delete[]filename;
		for (int i = 0; i < nu_array; i++)
		{
			delete arrays[i];

		}
	}

	unsigned int AidMan::menu()
	{
		int selection;

		cout << "Aid Management System\n";
		d.formatted(true);
		cout << "Date: " << d;
		cout << "\nData file: ";
		if (filename != nullptr)
		{
			cout << filename;
		}
		else
		{
			cout << "No file";
		}
		cout << "\n---------------------------------\n";

		selection = M.run();
		return selection;
	}
	AidMan::AidMan(const AidMan& src)
	{
		filename = nullptr;
		*this = src;

	};
	AidMan& AidMan::operator=(const AidMan& src)
	{
		if (this != &src)
		{
			he.alocpy(filename, src.filename);
			M = src.M;
		}

		return *this;
	};

	void AidMan::run()
	{
		bool menu_option = true;
		string emp;
		char* des = nullptr;
		ofstream out("shippingOrder.txt");
		int sk ;
		int retu;
		int  i;
		int count = 0;

		do
		{
			int selec = menu();
			if (filename == nullptr && selec != 7)
			{
				selec = 7;
			}

			switch (selec)
			{
			case 1:
				cout << "\n****List Items****\n";
				if (nu_array > 0)
				{
					char row;
					int row_num;
					list();
					cout << "Enter row number to display details or <ENTER> to continue:\n> ";
					if (cin.peek() == '\n')
					{
						cin.ignore();
					}
					cin.get(row);
					row_num = ((int)row - 48) - 1;
					if (row == '\n')
					{
						cout << "\n";
					}
					else if (row_num < nu_array && row_num >= 0)
					{
						arrays[row_num]->linear(false);

						cout << *arrays[row_num] << "\n\n";
					}
				}
				else
				{
					cout << "The list is emtpy!";
				}

				break;
			case 2:
				cout << "\n****Add Item****\n";
				if (nu_array==sdds_max_num_items)
				{
					cout << "Database full!";						
				}
				else
				{
					
					cout << "1- Perishable\n" << "2- Non-Perishable\n" << "-----------------\n" << "0- Exit\n> ";
						int menu_ = he.getInt(0, 3, "gh");
						if (menu_==1)
						{
							arrays[nu_array] = new Perishable;
						} 
						else if (menu_ == 2)
						{
							arrays[nu_array] = new Item;
						}
						else if(menu_ == 0)
						{
							cout << "Aborted\n";
						}
						if (menu_ == 2|| menu_ == 1)
						{
							 sk =arrays[nu_array]->readSku(cin);
							 retu = search(sk);
							if (retu==-3)
							{
								arrays[nu_array]->read(cin);
								cout << "\n";
								nu_array++;
							}
							else
							{
								cout << "Sku: " << sk << " is already in the system, try updating quantity instead.\n\n";
								delete arrays[nu_array];
							}

						}

						save();

					
				}

				break;

			case 3:
				cout << "\n****Remove Item****\n";
				cout << "Item description: ";
				cin >> emp;
				list(emp.c_str());
				cout << "Enter SKU: ";
				cin >> sk;
				retu = search(sk);
				if (retu==-3)
				{
					cout << "SKU not found!\n";
				}
				else
				{
					cout << "Following item will be removed: \n";
					arrays[retu]->linear(false);
					cout << *arrays[retu]<<endl<<"Are you sure?\n"<<"1- Yes!\n"<<"0- Exit\n"<<"> ";
					sk= he.getInt(0, 1, "gh");

					if (sk==1)
					{
						cout << "Item removed!\n\n";

						delete arrays[retu];
						if (retu!=nu_array)
						{
						for (  i = retu; i < nu_array-1; i++)
						{
							
							arrays[i] = arrays[i + 1];

						}
						//delete arrays[nu_array];
						nu_array--;
						}




					}
					else if (sk == 0)
					{

					}

				}
				save();


				break;
			case 4:
				cout << "\n****Update Quantity****\n";
				cout << "Item description: ";
				cin >>emp;
				he.alocpy(des, emp.c_str());

				retu=list(des);
				if (retu==-3)
				{
					cout << "No matches found!\n";
				}
				else 
				{
					cout << "Enter SKU: ";
					cin >> sk;
					retu = search(sk);
					if ( retu!=-3)
					{
						cout<<"1- Add\n" << "2- Reduce\n" << "0- Exit\n" << "> ";
					int selection= he.getInt(0, 2, "gh");

					if (selection==1)
					{
						if (arrays[retu]->qtyNeeded() != arrays[retu]->qty())
						{
						cout << "Quantity to add: " ;
						int add = he.getInt(1, arrays[retu]->qtyNeeded()- arrays[retu]->qty(), "gh");
						
						*arrays[retu] += add;
						cout << add << " items added!\n\n";
						}
						else
						{
							cout << "Quantity Needed already fulfilled!\n\n";
						}
					}
					else if (selection == 2)
					{
						if (arrays[retu]->qty()!=0)
						{
						cout << "Quantity to reduce: ";
						int redu = he.getInt(1, arrays[retu]->qty(), "gh");

						*arrays[retu] -= redu;
						cout << redu << " items removed!\n\n";

						}
						else
						{
							cout << "Quaintity on hand is zero!\n\n";
						}
					}
					else if (selection == 0)
					{
						cout << "Aborted!\n\n";
					}

					}
					else
					{
						cout << "SKU not found!\n\n";

					}
					delete[]des;
					des = nullptr;
					save();

				}


				break;
			case 5:
				cout << "\n****Sort****\n";
				sort();
				save();
				cout << "Sort completed!\n\n";

				break;
			case 6:
				cout << "\n****Ship Items****\n";

				
				out << "Shipping Order, Date: "<<d<<endl;
				out << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
				out << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
				for ( int j = 0; j < nu_array; j++)
				{
					if (arrays[j]->qty()== arrays[j]->qtyNeeded())
					{
						arrays[j]->linear(true);
						out << std::setfill(' ') << setw(4) << count + 1 << " | ";
						count++;

						out << *arrays[j]<<endl;
					delete arrays[j];
					if (j != nu_array)
					{
						for (i = j; i < nu_array - 1; i++)
						{

							arrays[i] = arrays[i + 1];

						}
						//delete arrays[nu_array];
						nu_array--;
					}


					}


				}
					out << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
					cout<<"Shipping Order for "<<count<<" times saved!\n\n";

					save();
				break;
			case 7:
				cout << "\n****New/Open Aid Database****\n";
				save();
				load();
				break;
			case 0:
				cout << "Exiting Program!\n";
				menu_option = false;
				break;

			}





		} while (menu_option);



	};

	void AidMan::remove(int index) 
	{
		

	}
	void AidMan::save()
	{
		if (filename != nullptr)
		{
			std::ofstream file(filename);

			for (int i = 0; i < nu_array; i++)
			{
				arrays[i]->save(file);
				file << '\n';
			}
			//deallocate();

		}


	}

	void AidMan::sort() 
	{
		for (int step = 0; step < nu_array; ++step) {

			// loop to compare array elements
			for (int i = 0; i < nu_array - step; ++i) {

				if (i<nu_array-1)
				{
				int A = arrays[i]->qtyNeeded() - arrays[i]->qty();
				int B = arrays[i + 1]->qtyNeeded() - arrays[i + 1]->qty();

				
				if (B>A) {

					// swapping elements if elements
					// are not in the intended order
					iProduct *temp = arrays[i];
					arrays[i] = arrays[i + 1];
					arrays[i + 1] = temp;
				}
				}
			}
		}


	};






	bool AidMan::load()
	{
		std::string name;
		int ind = 0;
		cout << "Enter file name: ";
		cin >> name;
		std::ifstream ope(name);
		if (!ope.is_open())
		{
			int num;
			cout << "Failed to open FN for reading!\n";
			cout << "Would you like to create a new data file?\n" << "1- Yes!\n" << "0- Exit\n" << '<';
			cin >> num;
			if (num == 1)
			{
				std::ofstream create(name);
			}

		}
		else
		{
			while (!ope.eof())
			{
				int  x = (int)ope.peek();
				if (x < 52 && x>48)
				{
					arrays[ind] = new Perishable;
					arrays[ind]->load(ope);

				}
				else if (x < 57 && x >= 52)
				{
					arrays[ind] = new Item;
					arrays[ind]->load(ope);
				}
				else
				{
					//std::ios_base::failure;
				}

				ind++;




			}





		he.alocpy(filename, name.c_str());
		nu_array = ind - 1;
		cout << nu_array << " records loaded!\n\n";
		}



		return true;

	};

	void AidMan::deallocate()
	{
		delete* arrays;
		delete[]filename;
		nu_array = 0;


	};
	int AidMan::list(const char* sub_desc)
	{
		int i = 1;
		int x = 0;

		if (nu_array != 0)
		{


			if (sub_desc == nullptr)
			{
				cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";

				for (i = 0; i < nu_array; i++)
				{
					cout << std::setfill(' ') << setw(4) << i + 1 << " | ";
					arrays[i]->linear(true);
					cout << *arrays[i];
					cout << endl;
				}

				cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";


			}
			else
			{
				x = 0;
				
				for (i = 0; i < nu_array; i++)
				{
					if (*arrays[i] == sub_desc)
					{
						if (x==0)
						{
							cout << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry\n";
							cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
							x++;
						}
						cout << std::setfill(' ') << setw(4) << i + 1 << " | ";

						arrays[i]->linear(true);
						cout << *arrays[i];
						cout << endl;

					}
				};
				if (x>0)
				{
				cout << "-----+-------+-------------------------------------+------+------+---------+-----------\n";
				i = x;
				}


			}
		}
		else
		{
			cout << "The list is emtpy!";
		}

		return i;


	};


	int  AidMan::search(int sku) const 
	{
		int i;
		int retur=-3;
		for (i = 0; i < nu_array; i++)
		{
			if (*arrays[i]==sku)
			{
				
				retur = i;
				i = nu_array;
			}
		}


		
		return retur;
	}





	int getFileLength(std::istream& is) {
		int len{};
		if (is) {
			// save the current read position
			std::streampos cur = is.tellg();
			// go to the end
			is.seekg(0, ios::end);
			// let what is the positions (end position = size)
			len = is.tellg();
			// now go back to where you were.
			is.seekg(cur);
		}
		return len;
	}









}