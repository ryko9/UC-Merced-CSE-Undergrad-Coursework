#include "Stack.h"
#include <iostream>
using namespace std;

//constructor

Stack::Stack()
{
	cout << "Constructing derived" << endl;
}

//destructor
Stack::~Stack()
{
	cout << "Destructing derived" << endl;
}

//insert value at front of stack
void Stack::push(int value)
{
	LinkedList::insertAtFront(value);
}

int Stack::pop()
{
	int originalFront = first->val; //value of val that first is pointing to
	removeFromFront(); //removes number at front
	return originalFront; //returns original front.
}

int& Stack::top()
{

	return first->val;

}
