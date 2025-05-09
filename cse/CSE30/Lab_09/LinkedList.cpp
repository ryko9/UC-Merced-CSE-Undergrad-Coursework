#include "LinkedList.h"
#include <iostream>
using namespace std;

//constructor

LinkedList::LinkedList()
{
	first = NULL; //head pointing to nothing, empty list
	last = NULL;  //tail pointing to nothing
	cout << "Constructing base" << endl;
}

//destructor
LinkedList::~LinkedList()
{
	cout << "Destructing base" << endl;
	if(isEmpty() == false) //if isEmpty returns true, call clear
	{
		clear();
	}
}

//to insert a new node to end of list
void LinkedList::insertAtBack(int valueToInsert)
{
	//check to see if list is empty
	if(isEmpty())
	{
		Node* newNode = new Node();
		newNode->val = valueToInsert;
		newNode->next = NULL;

		//if list is empty, then we create a new node and then point both first and last to it.
		first = newNode;
		last = newNode;
	}

	else //if list already has values
	{
		//have to traverse through linkedlist to go from current head to curent tail
		Node* increment = new Node(); //used to increment through list
		increment = first; //increment is pointed to the first node
		while(increment->next != NULL)
		{
			increment = increment->next;
					      /*temp1 is pointed to NEXT value since 'next' stores the
					      address of the next node. If it points to null, that means
					      we have reached the end of the linkedlist*/
		}

		/*while loop runs until we get to the current end of the list, now we can create new node
		to add onto the end of the list*/

		Node* temp = new Node(); //temp points to newly allocated node that will be added to list
        	temp->val = valueToInsert; //the newly allocated node's val member is assigned the input
       	 	temp->next = NULL; /*since we area adding a new node to the end of the list, last node
                             should point to null*/

		//since while loop iterated until increment reached the LAST node, we now point  last->next to temp.
		increment->next = temp;
		last = temp;
	}
}

bool LinkedList::removeFromBack()
{

	if(isEmpty()) //if its empty, you can't remove from it. return false
	{
		return false;
	}
	else if(first == last) //if there is only one node, first and last point to same node
	{
		delete first; //clears memory first is pointing to

		first = NULL; //no more values so first and last are NULL.
		last = NULL;
		return true; //returns true for successfull removal
	}
	else
	{
		Node* increment = new Node();//node to traverse through list
		increment = first;

		Node* previous = new Node(); //the node BEFORE increment.


		while(increment->next != NULL) //traversing through list
		{
			previous = increment; //previous is assigned the value of increment before it goes to the next node
			increment = increment->next;
		}

		//increment is now pointing to end of list, and previous is pointing to node before end

		last = previous; //last now points to previous since it is the new tail of the list
		previous->next = NULL;

		delete increment; //increment is pointing to the node that we removed from the linkedlist. we can now clear memory it is pointing to

		return true;
	}
}

void LinkedList::print()
{

	if(isEmpty()) //if empty, print out blank
	{
		cout << "";
	}

	else
	{
		Node* temp = new Node();
		temp = first;
		cout << first->val; //prints out first so we can just put commas after
		while(temp->next != NULL)
		{
			temp = temp->next;
			cout << ", " << temp->val;
		}
	}

}

bool LinkedList::isEmpty()
{
	if(first == NULL && last == NULL) //if both first and last point to NULL, then list is empty
	{
		return true;
	}

	return false;
}

int LinkedList::size()
{
	if(isEmpty())
	{
		return 0;
	}

	else
	{
		Node* temp = new Node();
		temp = first; //since we are pointing to first node, size starts at 1
		int size = 1;
		while(temp->next != NULL) //size is incremented every time we traverse to next node, so starting at 1 counts actual # of nodes
		{
			size++;
			temp = temp->next;
		}
		return size;
	}
}

void LinkedList::clear()
{
	Node* increment = new Node(); //pointer to go through each node
	increment = first; //points to start of list
        while(increment != NULL) //going through entire list and deleting. last points to NULL, so when we get to last and free the memory there, increment would then be equal to last->next
        {				//since last->next = NULL, loop would stop.

                Node* nextNode = increment->next; //extra pointer to store address of the next node before we free memory at increment
                delete increment; //clears memory that increment is pointing to
                increment = nextNode; /*points increment to nextNode and continues looping traversing we get to last node, which points to null*/
        }

	//after while loop is over, increment is now pointing to NULL.

	first = increment; //settng first and last to null since they shouldn't point to anything in an empty list
	last = increment;
	delete increment;
}


void LinkedList::insertAtFront(int valueToInsert)
{
	if(isEmpty())
	{
		//if list is initially empty, we insert a new Node that is the first and last node.
		Node* onlyNode = new Node();
		onlyNode->val = valueToInsert;
		onlyNode->next = NULL; //points to NULL since there are no nodes after currently.

		first = onlyNode;
		last = onlyNode;
	}
	else
	{
		//if there are already nodes in the list, we just add one and point it to FIRST and then make it the new FIRST
		Node* newFirst = new Node();
		newFirst->val = valueToInsert;
		newFirst->next = first; //the new first node points to the old first node
		first = newFirst; //first now points to newFirst
	}
}

bool LinkedList::removeFromFront()
{
	if(isEmpty())
	{
		//if list is empty, nothing can be removed.
		return false;
	}
	else if(first == last) //if first and last are equal, there is only one node in the list
	{
		delete first; //frees memory that first is pointing to.

		//now the list is empty, so first and last point to NULL.
		first = NULL;
		last = NULL;
		return true;
	}
	else //if there is more than one node in the list
	{
		Node* newFirst = new Node();
		newFirst = first->next; //new node points to the node after first

		delete first; //clears memory at first
		first = newFirst; //first now points to newFirst.
		return true;
	}
}

