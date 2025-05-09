/*

	Name: David Wang
	Lab section time: Friday 4:30-7:20 PM
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bitCount (unsigned int n);

int main(int argc, char *argv[]) //problem #5, added arguments to main
{
	if(argc == 2) //if there are two command line arguments
	{
		printf("%d\n", bitCount(atoi(argv[1]))); // the second argument should be the unsigned integer that we need to convert, so we use argv[1] which is the index of the second argument.
	}
	else if(argc > 2) //if there are more than 2 arguments, error statement prints out
	{
		printf("Too many arguements!\n");
	}
	else //else, proceed as normal.
	{
		printf("# 1-bits in base 2 representation of %u = %d, should be 0\n", 0, bitCount (0));
		printf("# 1-bits in base 2 representation of %u = %d, should be 1\n", 1, bitCount(1));
		printf("# 1-bits in base 2 representation of %u = %d, should be 16\n", 2863311530u, bitCount(2863311530u));
		printf("# 1-bits in base 2 representation of %u = %d, should be 1\n", 536870912, bitCount(536870912));
		printf("# 1-bits in base 2 representation of %u = %d, should be 32\n", 4294967295u, bitCount(4294967295u));
	}
	return 0;
}

int bitCount(unsigned int n) //problem #4
{
	unsigned int count = 0; //store number of 1-bit's
	while(n > 0)
	{
		count += n & 1; //if the bit is 1, adds 1 to count.
		n >>= 1; // shifts to the right by 1 and assigns value to n, going to the next bit.
	}

	return count;
}
