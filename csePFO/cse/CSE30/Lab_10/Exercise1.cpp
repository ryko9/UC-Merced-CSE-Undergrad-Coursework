	#include <iostream>
#include "Queue.h"
using namespace std;

int main()
{


	Queue test;

	cout << "Queue values: ";
	test.print();
	cout << endl;

	try
	{
		test.dequeue();
	}
	catch(int e)
	{
		cout << "Error: The queue is empty." << endl;
	}

	try
	{
		test.front();
	}
	catch(int e)
	{
		cout << "Error: The queue is empty." << endl;
	}
	cout << "The size of the queue is: " <<  test.size() << endl;
	cout << endl;

	for(int i = 1; i <= 10; i++) //adding values 1 to 10 the queue.
	{
		cout << "Added value to queue: " << i << endl;
		test.enqueue(i);
		cout << "Queue values: ";
		test.print();
		cout << endl;
	}
	cout << endl;

	try
	{
		cout << "The front value is: " << test.front() << endl;
	}
	catch(int e)
	{
		cout << "Error: The queue is empty." << endl;
	}

	cout << "The size of the queue is: " << test.size() << endl;
	cout << endl;

	for(int i = 0; i < 3; i++)
	{
		//calling dequeue 4 times
		cout << "Removed element from the queue: " << test.dequeue() << endl;
		cout << "Queue values: ";
		test.print();
		cout << endl;
	}
	cout << endl;

        try
        {
                cout << "The front value is: " << test.front() << endl;
        }
        catch(int e)
        {
                cout << "Error: The queue is empty." << endl;
        }

	cout << "The size of the queue is: " << test.size() << endl;
	return 0;
}
