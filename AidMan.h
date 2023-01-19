

#ifndef AIDMAN_H
#define AIDMAN_H
#include "Menu.h"
#include "iProduct.h"
namespace sdds
{
const int sdds_max_num_items = 100;

	class AidMan
	{
		char* filename;
		Menu M;
		iProduct* arrays[sdds_max_num_items];
		int nu_array;


	public:
		AidMan();

		AidMan(const AidMan&);
		AidMan& operator=(const AidMan&);
		~AidMan();
		void run();
		void deallocate();
		bool load();
		void save();
		int list(const char* sub_desc = nullptr);
		int search(int sku) const;
		void remove(int index);
		void sort();
	private:
		unsigned int menu();
	};

	


	int getFileLength(std::istream& is);



}




#endif // !AIDMAN_H
