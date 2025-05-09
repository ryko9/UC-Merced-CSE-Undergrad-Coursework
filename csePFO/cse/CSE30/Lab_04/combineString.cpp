#include <iostream>
using namespace std;

string combineStr(string input, int numLines) //concatenates the input depending on number of times
{

	string result; //string to store final result

	for(int i = 0; i < numLines; i++) //loops based on number of times specified
	{
		result+= input; //concatenates input onto result each time
	}

	return result;
}

int main()
{

	string input;
	int numLines = 100; //if numLines is 0, loop will stop

	while(numLines != 0) //loops until user enters 0 for number of lines
	{
		cout << "Enter a string: ";
		cin >> input;
		cout << "Enter a number of lines: ";
		cin >> numLines;

		if(numLines != 0) //only displays it if numLines is above 0.
		{
			cout << "Resulting string is: " << combineStr(input, numLines) << endl; //result
		}
	}

	return 0;
}
