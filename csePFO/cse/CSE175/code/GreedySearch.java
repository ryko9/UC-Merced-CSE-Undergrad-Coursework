//David Wang CSE 175

import java.util.*;

public class GreedySearch {

StreetMap map; //declare StreetMap object

	int limit; //integer depth limit
	int nodeExpansionCount; //to track number of expansions to be output
	
	String start; //initial location
	String finish; //destination location


	Heuristic heuristicFunction; //intialize Heuristic object to be used for expansion 

	//in accordance with spec pdf, constructor that takes in (StreetMap, String initial, String final, int limit)
	public GreedySearch(StreetMap map, String start, String finish, int limit)
	{
		this.map = map; //storing argument values into member/instance varibles
		this.start = start;
		this.finish = finish;
		this.limit = limit - 1; //starting from 0, so final is 999 instead of 1000

		this.heuristicFunction = new GoodHeuristic(map, map.findLocation(finish)); //initialize instance of heuristic function with appropriate parameters
	}

	public Node search(boolean isExplored) //bool isExplored for state check
	{
		SortedFrontier frontier = new SortedFrontier(SortBy.h); //used from provided SortedFrontier.java implentation
		Set<String> locationsExplored = new HashSet<String>(); //HashSet to keep track of locations already encountered/explored

		nodeExpansionCount = 0; //initialize count to 0

		Location indexLocation = map.findLocation(start); //find index location using findLocation() from StreetMap implementation;
		Node index = new Node(indexLocation); //intialize Index node at indexLocation to keep track of current node
		int indexDepth = index.depth; //store node's depth into int to track depth

		frontier.addSorted(index); //call AddSorted(index) to add index to the sorted frontier
		locationsExplored.add(index.loc.name); //call add() to add index.loc.name to HashSet of explored locations
	
		while(frontier.isEmpty() == false) //while frontier is NOT empty
		{
			index = frontier.removeTop(); //remove top node and set index to removed node

			if(nodeExpansionCount > limit) //return null if expansion count over limit 
			{
				return null;
			}

			if(indexDepth > limit) //return null if indexDepth exceeds limit
			{
				return null;
			}
			if(index.isDestination(finish) == true)
			{
				return index; //return index if index's location is already at final destination
			}	
			if(start == finish) //if initial and final destination are the same, return index
			{
				return index; 
			}

			index.expand(heuristicFunction); //expand, with heuristic function
			nodeExpansionCount++; //update expansion count by 1 after expanding


			if(isExplored == true) //if already explored, check for reoccurences in isExplored
			{
				for(Node next: index.children) //new node next for node after index
				{
					//check if next.loc.name is already explored, store result in isContains
					boolean isContains = locationsExplored.contains(next.loc.name); //check if isExplored.contains returns true or false

					if(isContains == false) //repeated state check, if true add next node to frontier and set
					{						
						frontier.addSorted(next); //add next to frontier
						locationsExplored.add(next.loc.name); //add next to locationsExplored
					}

				} 

			}

			else //else if isContains == false next is not in set yet, add index's next node to locationsExplored
			{
						frontier.addSorted(index.children);
			}
		}

	
		return null; //else return null
	}
}



