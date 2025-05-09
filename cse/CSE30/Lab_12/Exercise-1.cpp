#include <iostream>
#include <string>
#include "HTable.h"
using namespace std;

int main() {
        HTable h1(11);
        data d = {18, "Appliances"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 41;
		d.value = "Auto Parts";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 22;
		d.value = "Books";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 44;
		d.value = "Clothing";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 59;
		d.value = "Computers";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 32;
		d.value = "Electronics";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 31;
		d.value = "Furniture";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 70;
		d.value = "Home Improvement";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 13;
		d.value = "Movies";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 27;
		d.value = "Music";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 33;
		d.value = "Pets";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

		d.key = 26;
		d.value = "Software";
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        data dt = {27, "Toys"};
		d.key = 27;
		d.value = "Toys";
        if(h1.remove(dt) == 0) //remove that record from table
            cout << "Data removed." << endl;
        else
            cout << "Cannot remove data...Key not found." << endl;

		d.key = 23;
		d.value = "Jewelry & Watches";
        if(h1.remove(dt) == 0) //remove that record from table
            cout << "Data removed." << endl;
        else
            cout << "Cannot remove data...Key not found." << endl;

        cout << "Content of table: " << endl;
        h1.output(); 
        return 0;
}
