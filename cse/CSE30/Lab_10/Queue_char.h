#ifndef QUEUE_CHAR_H
#define QUEUE_CHAR_H
#include "LinkedList_char.h"

class Queue_char: public LinkedList_char //Queue, inherits from LinkedList
{

	public:

		Queue_char(); //constructor
		~Queue_char(); //destructor
		void enqueue(char value);
		char dequeue();
		char& front();
};

#endif
