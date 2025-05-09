#ifndef STACK_H
#define STACK_H
#include "LinkedList.h"
#include <iostream>

template<class T>
class Stack: public LinkedList<T>
{

	public:

		Stack(); //constructor
		~Stack(); //destructor
		void push(T value);
		T pop();
		T& top();
};

//function implementations

//constructor

template<class T>
Stack<T>::Stack()
{
}

//destructor
template<class T>
Stack<T>::~Stack()
{
}

//insert value at front of stack
template<class T>
void Stack<T>::push(T value)
{
	LinkedList<T>::insertAtFront(value);
}

template<class T>
T Stack<T>::pop()
{
	T originalFront = LinkedList<T>::first->val; //value of val that first is pointing to
	LinkedList<T>::removeFromFront(); //removes number at front
	return originalFront; //returns original front.
}

template<class T>
T& Stack<T>::top()
{

	return LinkedList<T>::first->val;

}

#endif

