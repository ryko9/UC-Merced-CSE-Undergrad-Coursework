#ifndef STACK_CHAR_H
#define STACK_CHAR_H
#include "LinkedList_char.h"

class Stack_char: public LinkedList_char
{

	public:

		Stack_char(); //constructor
		~Stack_char(); //destructor
		void push(char value);
		char pop();
		char& top();
};

#endif

