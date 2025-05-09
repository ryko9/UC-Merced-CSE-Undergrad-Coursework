#ifndef QUEUE_H
#define QUEUE_H
#include "LinkedList.h"

class Queue: public LinkedList //Queue, inherits from LinkedList
{

	public:

		Queue(); //constructor
		~Queue(); //destructor
		void enqueue(int value);
		int dequeue();
		int& front();
};

#endif
