#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;


int checkArraySort(string* A, int array_size)
{
        bool isAscending = true; //assumes ascending and descending are true initially
        bool isDescending = true;
        int isSorted = 0;

        for(int i = 0; i < array_size - 1; i++)
        {
                if(A[i] > A[i + 1])
                {
                        isAscending = false; //if anything descending is ever found, ascending is false
                        break;
                }
        }

        for(int i = 0; i < array_size - 1; i++)
        {
                if(A[i] < A[i + 1])
                {
                        isDescending = false; //if anything ascending is ever found, descending is false
                        break;
                }
        }

        if(isAscending == true && isDescending == false) //if nothing descending is found and only ascending is found
        {
                isSorted = 1; //whole thing is ascending since there are no descending pairs
        }
        else if(isAscending == false && isDescending == true)//if nothing ascending is found and only descending are found
        {
                isSorted = -1; //whole thing is descending since there are no ascending pairs
        }
        else
        {
                isSorted = 0; //only other case is in which there were descending AND ascending pairs. Thus both
                                //isAscending and isDescending would end up false; array is not sorted.
        }

return isSorted;
}

int binarySearchR (string* A, int first, int last, string key)
{


	        int middle = (first + last)/2; //middle index

		if(first > last) //to prevent infinite recursion, make sure first and last are in valid order
		{
			return -1;
		}


		if(key == A[middle]) //if value is same as key
		{
			return middle;
		}
		else if (key < A[middle]) //if key is less than middle element
		{
			return binarySearchR(A, first, middle - 1, key); //narrows search down to less than middle, calls again from start to middle - 1.
		}
		else //if key is greater than middle element
		{
			return binarySearchR(A, middle + 1, last, key); //narrows search down to starting from middle + 1 up to last index.
		}

}

int main()
{
        string* lines = NULL; //string array to store lines
        int size = 0; //size of array
        string line; //arbitrary string to go through text file while increasing size;

        ifstream input; //file we get input from

        input.open("words_in.txt"); //opening input file

        assert(!input.fail()); //making sure there is valid address
        input >> line; //goes through first value
        size++; //since it went through first value, size increases by one

        while (!input.eof()) //if not at end of file, proceed
        {
                input >> line;
                size++; //adding 1 to size of array every interation of while loop
        }

        lines = new string[size]; //dynamically allocated array
	 input.close(); //closing and reopening to go through input from start again
        input.open("words_in.txt");

        for(int i = 0; i < size; i++) //inputting lines from file into array
        {
                input >> lines[i]; //inputting line (0+i) into element i of array
        }
        input.close(); //close input

        int sort = checkArraySort(lines, size); //function call

        if(sort == 1) //appropriate statements based on sort's value
        {
                cout << "The array is sorted in ascending order!" << endl;
        }
        else if(sort == -1)
        {
                cout << "The array is sorted in descending order!" << endl;
        }
        else
        {
                cout << "The array is not sorted!" << endl;
        }

	if(sort == 1) //if array is in ascending order, we can use binarySearchR
	{
		string key;
		cout << "Enter string to search for in array: ";
		cin >> key;

		int foundAt = binarySearchR(lines, 0, size - 1, key); //(Array, Start, Finish, Key)
									//starts from first element 0, to last element, size - 1.
		if(foundAt == -1)
		{
			cout << "The key '" << key << "' was not found in the array!" << endl;
		}

		else//binarySearchR returns -1 if key is not found, so any other number would mean key is found.
		{
			cout << "Found key '" << key << "' at index " << foundAt << "!" << endl;
		}
	}



        delete [] lines; //freeing memory
        lines = NULL; //clearing lines to prevent invalid memory reference
        return 0;
}

