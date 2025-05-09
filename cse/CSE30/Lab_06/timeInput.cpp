#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

struct Time //structure that stores hour, minutes, seconds
{

	int hour;
	int minutes;
	int seconds;

};

bool getTimeFromUser(Time &time) //passes time struct by reference, modifies it and returns boolean
{

	string input; //variable to store string to be checked
	getline(cin, input); //includes symbols ":"

	bool isValid = true; //to determine if the inputted string only contains digits or semicolons

	for(int i = 0; i < input.length(); i++)
	{
		//if anything is found that is NOT in between 0 and 9 or equal to ':'
		if(!((input[i] >= '0' && input[i] <= '9') || (input[i] == ':')))
		{
			isValid = false;
			break;
		}
	}

	if(isValid == true)
	{

		//indexes of semicolons in int variables

		int semi1 = input.find(":", 0); //represents index of first semicolon found starting from index 0
		int semi2 = input.find(":", semi1 + 1); //to find the second semicolon AFTER index "first", we start from first + 1
//		int semi3 = input.find(":", semi2 + 1); //finding semicolon occurence AFTER index second

		//strings that contain hour, seconds, and minutes extracted from user input

		//to get substring from index x to index y, substr(x, y - x)

		string strhour = input.substr(0, semi1); //hour is string from index 0 to the index BEFORE the semicolon.
		string strminutes = input.substr(semi1 + 1, semi2 - semi1 + 1); //minutes is between first semi and second semi
		string strseconds = input.substr(semi2 + 1, input.length() - semi2 + 1); //seconds is in between second semi and end of string

		//we start from index semi1 + 1 since we don't want to reinclude the semicolon. Then we go up a length of
		// semi2 - (semi1 + 1) in order to go from (semi1 + 1) to the index BEFORE semi2

		//converting hour, seconds, and minutes to integers.

		int hour = atoi(strhour.c_str());
		int minutes = atoi(strminutes.c_str());
		int seconds = atoi(strseconds.c_str());

		//checking if hour, minutes, and seconds are valid

		if ((hour >= 0 && hour <= 23) && (minutes >= 0 && minutes <= 59) && (seconds >= 0 && seconds <= 59))
		{
			time.hour = hour;        //sets structure values and returns true if valid
			time.minutes = minutes;
			time.seconds = seconds;

			return true;
		}

	}

	return false; //returns false if not valid

}

void print24Hour(Time &time) //prints time out
{

	//setfill(0) << setw(2) puts 2 spaces filled with '0'. When you input time, hour, and minutes, they fit into the spaces

	cout << setfill('0') << setw(2) << time.hour << ":"; // hour, followed by semicolon
	cout << setfill('0') << setw(2) << time.minutes << ":"; // minutes followed by semi
	cout << setfill('0') << setw(2) << time.seconds;  //seconds followed by semi

}

int main()
{

	//defining structures

	Time start; //starting and ending time
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
