#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "Time.h"
using namespace std;

bool getTimeFromUser(Time &time) //passes time struct by reference, modifies it$
{

        string input; //variable to store string to be checked
        getline(cin, input); //includes symbols ":"

        bool isValid = true; //to determine if the inputted string only contain$

        for(int i = 0; i < input.length(); i++)
        {
                //if anything is found that is NOT in between 0 and 9 or equal $
                if(!((input[i] >= '0' && input[i] <= '9') || (input[i] == ':')))
                {
                        isValid = false;
                        break;
                }
        }

        if(isValid == true)
        {

                //indexes of semicolons in int variables

                int semi1 = input.find(":", 0); //represents index of first colon
                int semi2 = input.find(":", semi1 + 1); //to find the second colon

                //strings that contain hour, seconds, and minutes extracted fro$

                //to get substring from index x to index y, substr(x, y - x)

                string strhour = input.substr(0, semi1);
                string strminutes = input.substr(semi1 + 1, semi2 - semi1 + 1);
                string strseconds = input.substr(semi2 + 1, input.length() - semi2 + 1);

                //we start from index semi1 + 1 since we don't want to reinclude the colon.

                //converting hour, seconds, and minutes to integers.

                int hour = atoi(strhour.c_str());
                int minutes = atoi(strminutes.c_str());
		int seconds = atoi(strseconds.c_str());

                //checking if hour, minutes, and seconds are valid

                if ((hour >= 0 && hour <= 23) && (minutes >= 0 && minutes <= 59))
                {
                        time.setHour(hour);        //sets member values and returns true if valid
                        time.setMinutes(minutes);
                        time.setSeconds(seconds);

                        return true;
                }

        }

        return false; //returns false if not valid

}

void print24Hour(Time &time) //prints time out
{

        //setfill(0) << setw(2) puts 2 spaces filled with '0'. When you input t$

        cout << setfill('0') << setw(2) << time.getHour() << ":"; // hour, followed by semicolon
        cout << setfill('0') << setw(2) << time.getMinutes() << ":"; // minutes followed by semi
        cout << setfill('0') << setw(2) << time.getSeconds();  //seconds followed by semi
}

int main()
{
	//creating objects

	Time start;
	Time end;

		cout << "Enter the start time for the lecture (format is HH:MM:SS): ";

	        bool startCheck = getTimeFromUser(start);

        if(startCheck == true) //if start time is valid, asks for end time
        {
                cout << "Enter the end time for the lecture (format is HH:MM:SS): ";
                bool endCheck = getTimeFromUser(end);

                if(endCheck == true) //if end time is valid, prints out lecture info
                {
                        cout << "The lecture starts at ";
                        print24Hour(start);

                        cout << " and ends at ";
                        print24Hour(end);
                        cout << endl;

                }
                else
                {
                        cout << "The end time is invalid!" << endl;
                }
        }
        else
        {
                cout << "The start time is invalid!" << endl;
        }


return 0;
}
