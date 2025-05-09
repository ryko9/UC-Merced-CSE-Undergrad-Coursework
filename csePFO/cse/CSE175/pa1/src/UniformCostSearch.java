//David Wang, CSE 175 10/11/19

import java.util.*;

public class UniformCostSearch {

	
	StreetMap map; //declare StreetMap object

	int limit; //integer depth limit
	int nodeExpansionCount; //to track number of expansions to be output
	
	String start; //initial location
	String finish; //destination location

	//in accordance with spec pdf, constructor that takes in (StreetMap, String initial, String final, int limit)
	public UniformCostSearch(StreetMap map, String start, String finish, int limit)
	{
		this.map = map; //storing argument values into member/instance varibles
		this.start = start;
		this.finish = finish;
		this.limit = limit - 1;
	}

	public Node search(boolean isExplored) //bool isExplored for state check
	{
		SortedFrontier frontier = new SortedFrontier(SortBy.f); //used from provided SortedFrontier.java implentation
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

			index.expand();
			nodeExpansionCount++; //update expansion count by 1 after expanding


			if(isExplored == true) //if already explored, check for reoccurences in isExplored
			{
				for(Node next: index.children) //new node next for node after index
				{
					//check if next.loc.name is already explored, store result in isContains
					boolean isContains = locationsExplored.contains(next.loc.name); //check if isExplored.contains returns true or false

					if(isContains == true) //if next.loc.name is in locationsExplored
					{
						//if next node is already in locationsExplored, compare costs between next nodes for lowest cost

						boolean isFrontier = frontier.contains(next.loc.name); //check if next is already in sortedFrontier  
						
						if(isFrontier == true) //repeated state check for reoccurences in isExplored
						{
							//use find to find the node that matches in location, store into next1 node to be used for comparison of path costs
							Node next1 = frontier.find(next); 

							if(next.partialPathCost < next1.partialPathCost)
							{
								//if next1's partialcost is less than next node's partialcost, remove next1 and add new 'next' node

								frontier.remove(next1); //remove next1 from frontier
								frontier.addSorted(next); //add next to frontier
							}

						} 

					}

					else //else if isContains == false next is not in set yet, sadd next to locationsExplored
					{
						frontier.addSorted(next);
						locationsExplored.add(next.loc.name);
					}
				}

			}

			else // if isExplored == false, not already explored does not check for reoccurences in isExplored
			{
				frontier.addSorted(index.children);
			}


		
		

	

	}
		return null; //else return null

}
	
}


