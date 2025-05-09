#include <iostream>
using namespace std;

int main()
{
	string input; //original string which will be inputted
	string reverse; //reversed string which will be outputted

	cout << "Enter the string to reverse: ";
	getline(cin, input);

	//for loop goes through string backwards and adds each char to Reverse
	for(int i = input.length() - 1; i >= 0; i--)
	{
		reverse += input[i];
	}

	cout << reverse << endl;

	return 0;
}
