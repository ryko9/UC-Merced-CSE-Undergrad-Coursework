#include "HTable.h"
#include <iostream>
#include <string>
using namespace std;

//constructor

HTable::HTable()
{
	max_size = 23;
	dt = new data[max_size]; //dt is array of struct datas

	for(int i = 0; i < max_size; i++) //initializing members
	{
		dt[i].key = -1;
		dt[i].value = "N/A";
	}

	numel = 0;
}

HTable::HTable(int t_size)
{
	max_size = t_size;

	dt = new data[max_size];

	for(int i = 0; i < max_size; i++)
	{
		dt[i].key = -1;
		dt[i].value = "N/A";
	}

	numel = 0;
}

int HTable::hash(int &k) //takes the KEY of a node and then mods by max
{
	return(k % max_size);
}

int HTable::rehash(int &k) //takes KEY + 1 then mods by max
{
	return (k+1) % max_size;
}

int HTable::add(data &d)
{
	int index = hash(d.key); //gets hash value of d
	int count = 0;

	if(numel < max_size) //numel represents number of data added, cant be full
	{
		if(dt[index].key == -1) //attempts to insert d into dt[index]
		{
			dt[index] = d; //if dt[index]->key = -1, space is unoccupied
			numel++;
			return 0; //returns 0 is successful
		}
		else
		{
			while(dt[index].key != -1 && count < max_size)  //else, rehash until unoccupied
			{
				index = rehash(index);
				count++;
			}

			if(count >= max_size) //out of bounds, so it isn't there
			{
				cout << "AOERHOAUERHOAUEREAR" << endl;
				return -1;
			}
			else
			{
				dt[index] = d; //then point dt[index] to d to point to its members
				numel++;
				return 0;
			}
		}
	}
	else
	{
		return -1; //returns -1 if full.
	}
}

int HTable::remove(data &d)
{
	int index = hash(d.key); //index = d->key % max_value
	int count = 0;

	if(numel == 0) //if numel = 0, table is empty
	{
		return -1;
	}
	else
	{
		if(dt[index].key == d.key)
		{
			dt[index].key = -1;
			dt[index].value = "N/A";
			numel--;
			return 0;
		}
		else
		{
			while(dt[index].key != d.key && count < max_size)
			{
				index = rehash(index);
				count++;
			}

			if(count >= max_size) //out of bounds
			{
				return -1;
			}
			else
			{
				dt[index].key = -1;
				dt[index].value = "N/A";
				numel--;
				return 0;
			}
		}
	}
}

void HTable::output()
{
	for(int i = 0; i < max_size; i++)
	{
		cout << i << " -> " << dt[i].key << " " << dt[i].value << endl;
	}
	cout << "There are " << numel << " data in the table." << endl;
}

