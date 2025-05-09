#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;

int main()
{
	string* lines = NULL; //string array to store lines
	int size = 0; //size of array
        string line; //arbitrary string to go through text file while increasing size;

	ifstream input; //file we get input from
	ofstream output; //file to be written to

	input.open("words_in.txt"); //opening input file

	assert(!input.fail()); //making sure there is valid address
	input >> line; //goes through first value
	size++; //since it went through first value, size increases by one

	while (!input.eof()) //if not at end of file, proceed
	{
		input >> line;
		size++; //adding 1 to size of array every interation of while loop
	}

	cout << size << endl;

	lines = new string[size]; //dynamically allocated array
	input.close(); //closing and reopening to go through input from start again
	input.open("words_in.txt");

	for(int i = 0; i < size; i++) //inputting lines from file into array
	{
		input >> lines[i]; //inputting line (0+i) into element i of array
	}
	input.close(); //close input

	output.open("words_out.txt");
	for(int i = 0; i < size; i++)
	{
		output << lines[i] << endl; //writing each element of array per line
	}
	output.close();

	delete [] lines; //freeing memory
	lines = NULL; //clearing lines to prevent invalid memory reference
	return 0;
}
