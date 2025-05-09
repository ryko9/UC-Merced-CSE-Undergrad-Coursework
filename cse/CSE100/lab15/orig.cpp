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
    int FindEdgeCost(string v1, string v2);
    int IsReachable(string v1, string v2);
};

void Graph::PrintOut(void) {
    list<string>::iterator it;
    map<pair<string,string>,int>::iterator edgeit;
    
    for(it = vertices.begin(); it != vertices.end(); it++) {
        cout << *it << endl;
    }
    
    for(edgeit = edges.begin(); edgeit != edges.end(); edgeit++) {
        cout << (*edgeit).first.first << " " << (*edgeit).first.second << " " << (*edgeit).second << endl;
    }
}

//Add Edge
void Graph::AddEdge(string v1,string v2,int weight) {

    //Make a Pair of vertices if true
    if(FindVertex(v1) && FindVertex(v2)) {

        //insert pair of vertices into map
        edges.insert(make_pair(make_pair(v1,v2), weight)); 
    }
}

//Find vertex, bool
bool Graph::FindVertex(string v1) {
    list<string>::iterator it;

    //iterate through the list of vertices
    for(it = vertices.begin(); it != vertices.end(); it++) {

	//If Match, return true
        if(*it == v1) {
            return true;
        }
    }

    //else return false
    return false;
}


int Graph::FindEdgeCost(string v1, string v2) {
    map<pair<string,string>,int>::iterator edgeit;
    
    //If both true
    if(FindVertex(v1) && FindVertex(v2)) {
	
	//iterate through map
        for(edgeit = edges.begin(); edgeit != edges.end(); edgeit++) {

	    //if both strings match, return cost then break
            if(((*edgeit).first.first == v1) && ((*edgeit).first.second == v2)) {
                return (*edgeit).second;
                break;
            }
        }
    }
	
    //else return -1
    return -1;
}

int Graph::IsReachable(string v1, string v2) {
	//white = it hasn't visited this node
	//gray = adjacent/ hasn't be
	//black: visited
	map<string,string> color;
	map<string,int> D;
	map<string, string> pred;
	queue<string> Q;
	list<string>::iterator it1;

	//iterate through vertices, set everything to : White, INT_MAX, " "
	for(it1 = vertices.begin(); it1 != vertices.end(); it1++) {
		
		//set to white
		color[*it1] = "WHITE";

		//set int max
		D[*it1] = INT_MAX;

		//" "
		pred[*it1] = "";
	}

	//Set vertices 1 to GRAY, 0
	color[v1] = "GRAY";
	D[v1] = 0;

	//Push into Queue
	Q.push(v1);

	map<pair<string, string>,int>::iterator it2;

	//While Queue is not empty
	while(!Q.empty()) {
		
		//set u to Q.front
		string u = Q.front();

		//pop from queue
		Q.pop();

		//iterate through the map
		for(it2 = edges.begin(); it2 != edges.end(); it2++) {

			//adjacent string
			string adj;

			//if match
			if((*it2).first.first == u) {

				//set adj var to the pair
				adj = (*it2).first.second;

				//if adjacent is White, swich to Gray
				if(color[adj] == "WHITE") {
					color[adj] = "GRAY";
					
					//set the adjacent to 1
					D[adj] = D[u]+1;
					
					//set pred[adj] to v1
					pred[adj] = u;

					//push the adjacent into Queue
					Q.push(adj);
				}
			}
		}
		

		//set Color of vect1 to Black
		color[u] = "BLACK";
	}
	
	//if not INT MAX return D[v2]
	if(D[v2] != INT_MAX) {
		return D[v2];
	}

	//else return -1
	return -1;
}


int main() {

    //object
    Graph G;

    //name
    string name;
    cin >> name;

    //While not END
    while(name != "END") {
        G.vertices.push_back(name);
        
        //repeat
        cin >> name;
    }
    
    //first, second
    string first, second;
    int weight;
    
    //first name
    cin >> first;

    //While not END
    while(first != "END") {

	//second
        cin >> second;

	//weight
        cin >> weight;

	//ADD
        G.AddEdge(first, second, weight);
        
	//repeat
        cin >> first;   //start next insertion
    }
    
    //cost, operation, and edge count
    int opCode, cost, edgeCount;

    //string A and B
    string A, B;
    
    do {
	//enter num
        cin >> opCode;

	//if operation 0, break
        if(opCode == 0) {
            break;
        }
        
	//else if 1
        else if(opCode == 1) {

	    //enter string A
            cin >> A;
            
	    //if Found, print 1
            if(G.FindVertex(A)) {
                cout << "1" << endl;
            }
		
	    //else print 0
            else {
                cout << "0" << endl;
            }
        }
        
	//if 2
        else if(opCode == 2) {
		
	    //Enter the 2 strings
            cin >> A;
            cin >> B;
            
	    //Find edge cost between the 2 strings
            cost = G.FindEdgeCost(A,B);
            
	    //output cost
            cout << cost << endl;
        }
        
	//If 3
        else if(opCode == 3) {

	    //Enter the 2 strings
            cin >> A;
            cin >> B;
            
	    //Find Edge Count using BFS
            edgeCount = G.IsReachable(A,B);
            
	    //output edge count
            cout << edgeCount << endl;
        }
    }while(opCode != 0); //while not 0
    G.PrintOut();
}
