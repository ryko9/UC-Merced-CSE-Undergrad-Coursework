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

        d = {41, "Auto Parts"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {22, "Books"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {44, "Clothing"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {59, "Computers"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {32, "Electronics"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {31, "Furniture"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {70, "Home Improvement"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {13, "Movies"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {27, "Music"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {33, "Pets"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        d = {26, "Software"};
        if(h1.add(d)) //add this record to table
            cout << "Cannot add data...table is full." << endl;
        else
            cout << "Data added." << endl;

        data dt = {27, "Toys"};
        if(h1.remove(dt) == 0) //remove that record from table
            cout << "Data removed." << endl;
        else
            cout << "Cannot remove data...Key not found." << endl;

        dt = {23, "Jewelry & Watches"};
        if(h1.remove(dt) == 0) //remove that record from table
            cout << "Data removed." << endl;
        else
            cout << "Cannot remove data...Key not found." << endl;

        cout << "Content of table: " << endl;
        h1.output(); //see the output, notice there is one empty record, in index number 33, that was the record with id of 271861
        return 0;
}
