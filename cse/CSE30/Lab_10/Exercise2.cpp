#include <iostream>
#include "Queue_char.h"
using namespace std;

int main()
{
	Queue_char test;

	cout << "\n";
	cout << "Function call\t\t Output\t\t Front\tQueue\tRear " << endl;
	cout << "\n";

	try
	{
		cout << "dequeue()\t\t " << test.dequeue();
        	cout << "\t\t ";
        	test.print();
	        cout << "\n\n";

	}
	catch(int e)
	{
		cout << "dequeue()\t\t exception\t\t";
		test.print();
		cout << "\n\n";
	}

	test.enqueue('D');
	cout << "enqueue(D)\t\t\t\t ";
	test.print();
	cout << "\n\n";

	test.enqueue('A');
	cout << "enqueue(A)\t\t\t\t ";
	test.print();
	cout << "\n\n";

        try
        {
                cout << "dequeue()\t\t " << test.dequeue();
                cout << "\t\t ";
                test.print();
                cout << "\n\n";

        }
        catch(int e)
        {
                cout << "dequeue()\t\t exception\t\t";
                test.print();
                cout << "\n\n";
        }


	cout << "size()\t\t\t " << test.size();
	cout << "\t\t ";
	test.print();
	cout << "\n\n";

        test.enqueue('D');
        cout << "enqueue(D)\t\t\t\t ";
        test.print();
        cout << "\n\n";


	cout << "isEmpty()\t\t ";
	if(test.isEmpty())
	{
		cout << "true\t\t ";
	}
	else
	{
		cout << "false\t\t ";
	}
	test.print();
	cout << "\n\n";

	try
	{
		cout << "front()\t\t\t " << test.front();
		cout << "\t\t ";
		test.print();
		cout << "\n\n";
	}
	catch(int e)
	{
		cout << "front()\t\t exception \t\t";
		test.print();
		cout << "\n\n";
	}

        test.enqueue('T');
        cout << "enqueue(D)\t\t\t\t ";
	test.print();
        cout << "\n\n";

        try
        {
                cout << "front()\t\t\t " << test.front();
                cout << "\t\t ";
                test.print();
                cout << "\n\n";
        }
        catch(int e)
        {
                cout << "front()\t\t exception \t\t";
                test.print();
                cout << "\n\n";
        }


	return 0;
}


