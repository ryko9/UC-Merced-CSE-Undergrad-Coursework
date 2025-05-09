#include "Queue_char.h"
#include <iostream>
using namespace std;


//constructor
Queue_char::Queue_char()
{
//	cout << "Calling subclass constructor" << endl;
}

//destructor
Queue_char::~Queue_char()
{
//	cout << "Calling subclass destructor" << endl;
}

void Queue_char::enqueue(char value)
{
	//inserts value at end of the queue
	LinkedList_char::insertAtBack(value);
}

char Queue_char::dequeue()
{
	if(LinkedList_char::isEmpty()) //cannot remove from queue if queue is empty.
	{
		throw -1;
	}
	{
		//removes value from front of queue and returns the value that was removed
		char front = first->val; //storing the value at first node.
		removeFromFront();
		return front;
	}
}

char& Queue_char::front()
{
	if(LinkedList_char::isEmpty())
	{
		throw -1;
	}
	//returns value at front of queue.
	return first->val;
}

