#include <iostream>
#include "Stack_char.h"
using namespace std;

int main()
{
	Stack_char test;

	cout << "\n";
	cout << "Function call\t\t Output\t\t StackContents " << endl;
	cout << "\n";

	test.push('A');
	cout << "push(A)\t\t\t\t\t ";
	test.print();
	cout << "\n\n";

	test.push('Y');
	cout << "push(Y)\t\t\t\t\t ";
	test.print();
	cout << "\n\n";

	cout << "size()\t\t\t " << test.size();
	cout << "\t\t ";
	test.print();
	cout << "\n\n";

	cout << "pop()\t\t\t " << test.pop();
	cout << "\t\t ";
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

	test.push('D');
	cout << "push(D)\t\t\t\t\t ";
	test.print();
	cout << "\n\n";

	cout << "pop()\t\t\t " << test.top();
        cout << "\t\t ";
        test.print();
        cout << "\n\n";

        test.push('T');
        cout << "push(D)\t\t\t\t\t ";
	test.print();
        cout << "\n\n";

	cout << "pop()\t\t\t " << test.pop();
        cout << "\t\t ";
        test.print();
        cout << "\n\n";

	return 0;
}

