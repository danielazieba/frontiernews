#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>

using namespace std;

class Date 
{
    private:
        int month;
        int day;
        int year;

    public:
        Date();
        Date(int new_month, int new_day, int new_year);
        Date(string date);

        int getMonth();
        void setMonth(int new_month);

        int getDay();
        void setDay(int new_day);

        int getYear();
        void setYear(int new_year);

        bool valid();
        int compareDate(Date comparison); // return 0 if this > comparison, 1 if this < comparison, -1 if this = comparison
        string toString(); 
        vector<int> getCharIndex(string str, char ch);
};

#endif