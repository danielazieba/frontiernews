#include "date.hpp"
#include <sstream>

Date::Date() {
    month = 1;
    day = 1;
    year = 2018;
}

Date::Date(string date) {
    month = 0;
    day = 0;
    year = 0;
    
    vector<string> temp_values;
    temp_values.resize(3);

    vector<int> divisors = getCharIndex(date, '/');
    temp_values.resize(3);

    for (int index = 0; index < date.size(); index++) {
        if (index < divisors[0]) {
            temp_values[0] += date[index];
        }

        if (index > divisors[0] && index < divisors[1]) {
            temp_values[1] += date[index];
        }

        if (index > divisors[1]) {
            temp_values[2] += date[index];
        }
    }

    stringstream month_str(temp_values[0]);
    stringstream day_str(temp_values[1]);
    stringstream year_str(temp_values[2]);

    month_str >> month;
    day_str >> day;
    year_str >> year;
}

Date::Date(int new_month, int new_day, int new_year) {
    month = new_month;
    day = new_day;
    year = new_year;
}

int Date::getMonth() {
    return month;
}

void Date::setMonth(int new_month) {
    month = new_month;
}

int Date::getDay(){
    return day;
}

void Date::setDay(int new_day){
    day = new_day;
}

int Date::getYear(){
    return year;
}

void Date::setYear(int new_year){
    year = new_year;
}

bool Date::valid(){
    switch(month) {
        case 1:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        case 2:
            if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
                if (day >= 1 && day <= 29) {
                    return true;
                } else {
                    return false;
                }
            } else if (day >= 1 && day <= 28) {
                return true;
            } else {
                return false;
            }
            break;
        case 3:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        case 4:
            if (day >= 1 && day <= 30) {
                return true;
            } else {
                return false;
            }
            break;
        case 5:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        case 6:
            if (day >= 1 && day <= 30) {
                return true;
            } else {
                return false;
            }
            break;
        case 7:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        case 8:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        case 9:
            if (day >= 1 && day <= 30) {
                return true;
            } else {
                return false;
            }
            break;
        case 10:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        case 11:
            if (day >= 1 && day <= 30) {
                return true;
            } else {
                return false;
            }
            break;
        case 12:
            if (day >= 1 && day <= 31) {
                return true;
            } else {
                return false;
            }
            break;
        default:
            return false;
    }
}

string Date::toString(){
    return to_string(month) + "/" + to_string(day) + "/" + to_string(year);
}

int Date::compareDate(Date comparison){
/*
return 0 if this > comparison
-1 if this = comparison
1 if this < comparison
    int

*/
    // check for equal
    if (day == comparison.getDay() && month == comparison.getMonth() && year == comparison.getYear()) {
        return -1;
    }

    if (year > comparison.getYear()){
        return 0;
    }
    
    if (month > comparison.getMonth()) {
        return 0;
    }
    
    if ((day > comparison.getDay()) && (month == comparison.getMonth()) && (year == comparison.getYear())){
        return 0;
    }

    return 1;

}

vector<int> Date::getCharIndex(string str, char ch) {
    vector<int> occurences;

    for (int index = 0; index < str.size(); index++) {
        if (str[index] == ch) {
            occurences.push_back(index);
        }
    }

    return occurences;
}
