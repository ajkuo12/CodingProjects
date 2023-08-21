//
//  weekday.cpp
//
//
//  Created by Aaron Kuo on 1/19/21.
//

#include <iostream>
using namespace std;

int main()
{
    // Declaring variables
    string month, weekday;
    int day, year;
    int dayCode, monthCode, yearCode, centuryCode, centuryValue, leapValue;
    int leapYearValue4, leapYearValue100, leapYearValue400;
    
    // Initializing Variables
    monthCode = 0;
    centuryCode = 0;
    leapValue = 0;
    
    // Month Input and Code Assignment
    cout << "Provide a month: ";
    getline(cin, month);
    // Day Input
    cout << "Provide a day: ";
    cin >> day;
    // Year Input
    cout << "Provide a year: ";
    cin >> year;
    
    // Month Code Assignment
    if (month == "April" || month == "July")
        monthCode = 0;
    else if (month == "January" || month == "October")
        monthCode = 1;
    else if (month == "May")
        monthCode = 2;
    else if (month == "August")
        monthCode = 3;
    else if (month == "February" || month == "March"
                                 || month == "November")
        monthCode = 4;
    else if (month == "June")
        monthCode = 5;
    else if (month == "September" || month == "December")
        monthCode = 6;
    else
        {cout << "Invalid month!\n" << endl;
        return 1;}
    
    // Day Verification
    if (day < 1 || day > 31)
        {cout << "Invalid day!\n" << endl;
        return 1;}
    else {}
  
    // Year Verification
    if (year < 1 || year > 3000)
        {cout << "Invalid year!\n" << endl;
            return 1;}
    else {}
    
    // Century Value Assignment
    centuryValue = (year/100) % 4;
    if (centuryValue == 0)
        centuryCode = -2;
    else if (centuryValue == 1)
        centuryCode = 3;
    else if (centuryValue == 2)
        centuryCode = 1;
    else if (centuryValue == 3)
        centuryCode = -1;
    else {}
    
    // Leap Year Offset Calculation
    leapYearValue4   = year%4;
    leapYearValue100 = year%100;
    leapYearValue400 = year%400;
    if (leapYearValue4 == 0)
        leapValue = 1;
    else {}
    if (leapYearValue100 == 0)
        leapValue = 0;
    else{}
    if (leapYearValue400 == 0)
        leapValue = 1;
    else{}
    
    // Leap Year Offset Assignments
    if (month == "January" && leapValue == 1)
        monthCode = monthCode - 1;
    else{}
    if (month == "February" && leapValue == 1)
        monthCode = monthCode - 1;
    else{}
    
    // Calculations
    yearCode = ((year%100)/4) + (year%100);
    dayCode = (centuryCode + day +yearCode + monthCode)%7;
    
    // Weekday Assignment
    if (dayCode == 0)
        weekday = "Sunday";
    else if (dayCode == 1 || dayCode == -6)
        weekday = "Monday";
    else if (dayCode == 2 || dayCode == -5)
        weekday = "Tuesday";
    else if (dayCode == 3 || dayCode == -4)
        weekday = "Wednesday";
    else if (dayCode == 4 || dayCode == -3)
        weekday = "Thursday";
    else if (dayCode == 5 || dayCode == -2)
        weekday = "Friday";
    else if (dayCode == 6 || dayCode == -1)
        weekday = "Saturday";
    else{}
    
    if (dayCode >= 0 && dayCode <= 6)
    cout << month << " " << day << ", " << year << " was a " ;
    cout << weekday << "!";
    cout << "\n\n";
        
    
}
