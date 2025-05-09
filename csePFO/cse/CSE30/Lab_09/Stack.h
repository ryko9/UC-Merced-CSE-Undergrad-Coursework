#ifndef STACK_H
#define STACK_H
#include "LinkedList.h"

class Stack: public LinkedList
{

	public:

		Stack(); //constructor
		~Stack(); //destructor
		void push(int value);
		int pop();
		int& top();
};

#endif
