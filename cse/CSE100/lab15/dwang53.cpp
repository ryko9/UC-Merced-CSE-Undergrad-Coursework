#include <map>
#include <list>
#include <iostream>
#include <string>
#include <queue>
#include <limits.h>

using namespace std;

struct Graph {
    list<string> vertices;
    map<pair<string,string>,int> edges;
    void PrintOut(void);
    void AddEdge(string,string,int);
    bool FindVertex(string);
    int FindEdgeCost(string vert1, string vert2);
    int IsReachable(string vert1, string vert2);
};

void Graph::PrintOut(void) {
    list<string>::iterator it;
    map<pair<string,string>,int>::iterator eit;
    
    for(it=vertices.begin(); it!=vertices.end(); it++) {
        cout << *it << endl;
    }
    
    for(eit = edges.begin(); eit != edges.end(); eit++) {
        cout << (*eit).first.first << " " << (*eit).first.second << " " << (*eit).second << endl;
    }
}

void Graph::AddEdge(string vert1,string vert2,int weight)
{
    bool a = FindVertex(vert1);
    bool b = FindVertex(vert2);

    if((a == 1) && (b == 1)) //if a and b are 1, true
    {
        edges.insert(make_pair(make_pair(vert1, vert2), weight));
    }
}

bool Graph::FindVertex(string vert1) 
{

    bool r1 = 1; //true
    bool r2 = 0; //false

    string s = vert1;
    list<string>::iterator i;
    list<string>::iterator start = vertices.begin();
    list<string>::iterator fin = vertices. end();
    int a; //keeping track

    i = start;
    while(i != fin)
    {
        if((s == *i))
        {
            return r1;
        }
        i++;
    }

    return r2;
}

int Graph::FindEdgeCost(string vert1, string vert2) 
{
    map<pair<string, string>, int>::iterator e;
    map<pair<string, string>, int>::iterator x = edges.begin();
    map<pair<string, string>, int>::iterator y = edges.end();

    bool a = FindVertex(vert1);
    bool b = FindVertex(vert2);

    if((b == 1) && (a == 1))
    {
        e = x;

        while(e != y)
        {
            if(((*e).first.second == vert2) && (*e).first.first == vert1)
            {
                    return (*e).second;
                    break;
            }

            e++;
        }
    }

    return -1;

}

int Graph::IsReachable(string vert1, string vert2)
{
    int arr[23];
    int max = INT_MAX;
    int c1;
    int c2;
    int vsize = vert1.size() + vert2.size();

    map<string,string> c;
    map<string,int> d;
    map<string, string> prev;

    queue<string> q1;
    
    list<string>::iterator in; //iterator to keep track.
    list<string>::iterator beg = vertices.begin(); //starting index
    list<string>::iterator end = vertices.end(); //ending index;

    string w = "WHITE";
    string b = "BLACK";
    string g = "GRAY";

    in = beg;
    while(in != end)
    {   
        for(int i = 0; i < 3; i++)
        {
            c1++;
        }

        c[*in] = w;
        for(int i = 0; i < 3; i++)
        {
            c[*in] = w;
            for(int j = 0; j < c2; j++)
            {
                c1--;
            }
        }
        d[*in] =  max;
        prev[*in] = "";

        in++;
    }

    int total;

        for(int i = 0; i < 3; i++)
        {
            c1++;
            c2++;
            total = c1 * c2;
        }

        c[vert1] = g;
        d[vert1] = 0;  
        q1.push(vert1);
  

    map<pair<string, string>, int>::iterator in1;
    map<pair<string, string>, int>::iterator start1 = edges.begin();
    map<pair<string, string>, int>::iterator start2 = edges.end();


    bool empty = (q1.empty());
    //check for empty

    string front = q1.front();

    in1 = start1;

    while(!(q1.empty())) 
    {
        for(int i = 0; i < 3; i++)
        {
            c1++;
        }

        if(!(empty))
        {
            front = q1.front();
            q1.pop();
        }

        for(c1 = 0; c1 < c2; c1++)
        {
        
        in1 = start1;
        while(in1 != start2)
        {
            string ad; //adjacent string

            if((*in1).first.first == (front))
            {
                ad = (*in1).first.second;

                if(c[ad] == w)
                {
                    c[ad] = b;
                    d[ad] = d[front] + 1;
                    prev[ad] = front;
                    q1.push(ad);
                }
            }

            in1++;
         }   
     }
        
        c[front] = b; //set to black
    }
    
    if(d[vert2] != max) //check not max
    {
        return d[vert2];
    }

    //else return -1
    return -1;
}


int main() 
{
    Graph A;

    string quit = "END";
    string input;
    string prev;
    string next;
    int count = 1;
    int val;

    // cin >> input; //get first input

    cin >> input;

    while(input != quit)
    {
        if(count == 1) //first input;
        {
            // cin >> input;
        }

        A.vertices.push_back(input);
        cin >> input;
        count++;
    }

    cin >> prev;

    while(prev != quit)
    {
        cin >> next;
        cin >> val;

        A.AddEdge(prev, next, val);

        cin >> prev;
    }

    int rVals[40]; //store then print the return values

    for(int i = 0; i < 35; i++)
    {
        rVals[i] = -100; //initialize to -1 default
    }

    int proto; //different actions performed based on proto's value;
    string in1;
    string in2;
    int a = 0;
    int cost;
    int edges;

    do
    {
        cin >> proto;

        if(proto == 0)
        {
            break;
        }

        else if(proto == 3)
        {
            cin >> in1;
            cin >> in2;

            int edgeCount = A.IsReachable(in1, in2);
            rVals[a] = edgeCount;
            a++;
        }
        else if(proto == 2)
        {
            cin >> in1;
            cin >> in2;

            cost = A.FindEdgeCost(in1, in2);
            rVals[a] = cost;
            a++;
        }
        else if(proto == 1)
        {
            // bool found = A.FindVertex(proto);

            cin >> in1;

            if(!(A.FindVertex(in1)))
            {
                rVals[a] = 0;
                a++;
            }
            else
            {
                rVals[a] = 1;
                a++;
            }  

        }

    }while(proto != 0);

    A.PrintOut(); //print out contents

    for(int i = 0; i < 35; i++) //print out the values from rVals
    {
        if(rVals[i] != -100) //for the unitialized values
            cout << rVals[i] << endl;
    }


}
