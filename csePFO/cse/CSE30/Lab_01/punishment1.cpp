#include <iostream>
using namespace std;

int main()
{

	int input;
	cout << "Enter the number of lines for the punishment: ";
	cin >>  input;

	if(input > 0)
	{
		for(int i = 0; i < input; i++)
		{
			cout << "I will always use object oriented programming. ";
		}
		cout <<  endl;
	}
	else
	{
		cout << "You entered an incorrect value for the number of lines!" << endl;
	}

return 0;
}
