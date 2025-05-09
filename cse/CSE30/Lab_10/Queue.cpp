#include "Queue.h"
#include <iostream>
using namespace std;


//constructor
Queue::Queue()
{
//	cout << "Calling subclass constructor" << endl;
}

//destructor
Queue::~Queue()
{
//	cout << "Calling subclass destructor" << endl;
}

void Queue::enqueue(int value)
{
	//inserts value at end of the queue
	LinkedList::insertAtBack(value);
}

int Queue::dequeue()
{
	if(LinkedList::isEmpty()) //cannot remove from queue if queue is empty.
	{
		throw -1;
	}
	{
		//removes value from front of queue and returns the value that was removed
		int front = first->val; //storing the value at first node.
		removeFromFront();
		return front;
	}
}

int& Queue::front()
{
	if(LinkedList::isEmpty())
	{
		throw -1;
	}
	//returns value at front of queue.
	return first->val;
}
