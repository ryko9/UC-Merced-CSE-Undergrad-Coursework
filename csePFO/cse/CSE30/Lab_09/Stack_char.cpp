#include "Stack_char.h"
#include <iostream>
using namespace std;

//constructor

Stack_char::Stack_char()
{
}

//destructor
Stack_char::~Stack_char()
{
}

//insert value at front of Stack_char
void Stack_char::push(char value)
{
	LinkedList_char::insertAtFront(value);
}

char Stack_char::pop()
{
	char originalFront = first->val; //value of val that first is pointing to
	removeFromFront(); //removes number at front
	return originalFront; //returns original front.
}

char& Stack_char::top()
{

	return first->val;

}

