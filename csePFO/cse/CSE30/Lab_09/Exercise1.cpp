#include <iostream>
#include "Stack.h"
using namespace std;

int main()
{

	Stack test;

	cout << "Current stack contents: " << endl;
	test.print();
	cout << endl;

	if(test.isEmpty())
	{
		cout << "The stack is empty!" << endl;
		cout << endl;
	}
	else
	{
		cout << "The stack is not empty!" << endl;
		cout << endl;
	}

	//adding values from 1 to 10 to the stack and displaying stack values after.
	for(int i = 1; i <= 10; i++)
	{
		test.push(i);
		cout << "Added " << i << " to the stack." << endl;
		cout << "Stack values: ";
		test.print();
		cout << endl;
	}

	cout << endl;

	cout << "The top value is: " << test.top() << endl;
	cout << "The size of the stack is: " << test.size() << endl;

	if(test.isEmpty())
	{
		cout << "The stack is empty!" << endl;
		cout << endl;
	}
	else
	{
		cout << "The stack is not empty!" << endl;
		cout << endl;
	}

	for(int i = 0; i < 3; i++)
	  {
	    //calling pop 4 times.
	    cout << "Removed element: " << test.pop() << endl;
	  }

	cout << "Stack values: ";
	test.print();
	cout << endl;

	cout << "The top value is: " << test.top() << endl;
	cout << "The size of the stack is: " << test.size() << endl;

	return 0;

}
