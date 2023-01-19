
#ifndef STATUS_H
#define STATUS_H


namespace sdds 


{


	class Status
	{
		char* description;
		int code;

	public:
		Status();

		Status(int x,char *des = nullptr);

		Status(const Status&);

		Status& operator=(const Status&);
		Status operator=(const int);
		Status operator=(const char*);
		 operator bool()const;
		 operator char *()const;
		 operator int ()const;
		 void alocpy(char*& destination, const char* source);
		 Status& clear();
		 std::ostream& print(std::ostream& os) const;





		~Status();


	};

	std::ostream& operator<<(std::ostream& ostr, const Status& right);
	std::istream& operator>>(std::istream& istr, const Status& right);




}















#endif // !STATUS_H
