



#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include<iomanip>

#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds {
   Utils ut;
   void Utils::testMode(bool testmode) {
      m_testMode = testmode;
   }
   void Utils::getSystemDate(int* year, int* mon, int* day) {
      if (m_testMode) {
         if(day) *day = sdds_testDay;
         if(mon) *mon = sdds_testMon;
         if(year) *year = sdds_testYear;
      }
      else {
         time_t t = std::time(NULL);
         tm lt = *localtime(&t);
         if (day) *day = lt.tm_mday;
         if (mon) *mon = lt.tm_mon + 1;
         if (year) *year = lt.tm_year + 1900;
      }
   }
   int Utils::daysOfMon(int month, int year)const {
      int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
      int mon = (month >= 1 && month <= 12 ? month : 13)-1;
      return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
   }
   
   void Utils::alocpy(char*& destination, const char* source)
   {
       if (destination != nullptr )
       {
       delete[]destination;
       destination = nullptr;

       }
       if (source!=nullptr)
       {
           destination = new char[strlen(source) + 1];
           strcpy(destination, source);
           destination[strlen(source)] = '\0';

       }

   };
   int Utils::getint(const char* prompt)
   {
       bool flag = true;
       int integer = 0;
       if (prompt != nullptr)
       {
           //cout << prompt;

           do
           {
               cin >> integer;

               if (cin.fail() || cin.peek() == '.')
               {
                   cin.clear();
                   cin.ignore(100, '\n');
                   cout << "Invalid Integer, retry: ";
               }
               else
               {
                   flag = false;
               }

           } while (flag);

       }
       return integer;

   };
   int Utils::getInt(int min, int max, const char* prompt , const char* errMes )
   {
       int integer_=0;
       bool flag_ = true;
   
       if (prompt != nullptr)
       {
           do
           {
               integer_ = getint(prompt);

               if (integer_>=min&&integer_<=max)
               {
                   flag_ = false;
               }
               else
               {
                   if (errMes == nullptr)
                   {
                       cout << "Value out of range ["<<min<<"<=val<="<< max<<"]: ";
                   }
                   else
                   {

                       cout << errMes << ", retry : ";
                   }
               }




           } while (flag_);



       }
       return integer_;
   };
   double Utils::getDouble(double min, double max, const char* prompt , const char* errMes )
   {
       double dob;
       bool flag_ = true;
       bool flag = true;

       if (prompt != nullptr)
       {


           do
           {



               do
               {
                   cin >> dob;

                   if (cin.fail() || cin.peek() == '.')
                   {
                       cin.clear();
                       cin.ignore(100, '\n');
                       cout << "Invalid number, retry: ";
                   }
                   else
                   {
                       flag = false;
                   }

               } while (flag);

               if (dob >= min && dob <= max)
               {
                   flag_ = false;
               }
               else
               {
                   if (errMes == nullptr)
                   {
                       cout << "Value out of range [" <<std::fixed << std::setprecision(2) << min << "<=val<=" << std::fixed << std::setprecision(2) <<max << "]: ";
                   }
                   else
                   {

                       cout << errMes << ", retry : ";
                   }
               }




           } while (flag_);



       }
       return dob;



   };


}