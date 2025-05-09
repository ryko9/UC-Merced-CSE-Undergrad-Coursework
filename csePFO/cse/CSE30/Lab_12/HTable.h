#ifndef HTABLE_H
#define HTABLE_H
#include <string>
using namespace std;

// Representation of a key/value pair in the table.
struct data {
        int key;
        string value;
};

class HTable {
        data *dt; //the table to hold hashed data structs
        int max_size; //max size of the table
        int numel; //number of elements in table, to check if it's full
public:
        HTable(); //default constructor to initialize a table of size 23
        HTable (int t_size); //alternate constructor to initialize a table of size t_size
        int hash(int &k);  //evaluates hash code of key
        int rehash(int &k); //performs linear probing if collision appears
        int add(data &d);   //adda a data pair into the table according to its key
        int remove(data &d); //removes data pair from the table according to its key
        void output();  //print out the content of the table
};
#endif
