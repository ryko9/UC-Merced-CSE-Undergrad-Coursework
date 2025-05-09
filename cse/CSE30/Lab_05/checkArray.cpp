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


cout << "Value of isAscending: " << isAscending << endl;
cout << "Value of isDescending: " << isDescending << endl;
cout << "Value of isSorted: " << isSorted << endl;
return isSorted;
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
	if(sort == 1)
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

        delete [] lines; //freeing memory
        lines = NULL; //clearing lines to prevent invalid memory reference
        return 0;
}


