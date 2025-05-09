#include <iostream>
using namespace std;

int main()
{

        int input; // number of lines for punishment
	int input2; //line typo input

        cout << "Enter the number of lines for the punishment: ";
        cin >>  input;

        if(input > 0) //if the first input is valid, then we can ask for the second input
        {
		cout << "Enter the line for which we want to make a typo: ";
        	cin >> input2;
		if(input2 > 0) //if the the second input is correct, then both inputs are correct and the for loop runs.
		{
                	for(int i = 0; i < input; i++)
                	{
                     		if (i == input2 - 1) // (input2 - 1) since the for loop starts from i = 0. Line 1 should be at index 0, etc.
				{
					cout << "I will always use object oriented programing. ";
				}
		        	else
				{

					 cout << "I will always use object oriented programming. ";
				}
			}
		cout << endl; //spacing for clarity.
		}
	        else     //if second input for line typo is wrong
        	{
                	cout << "You entered an incorrect value for the line typo!" << endl;
        	}
	}
        else  //if the first input is incorrect
        {
                cout << "You entered an incorrect value for the number of lines!" << endl;
        }

	return 0;
}

