//David Wang CSE 175

import java.util.*;

public class BFSearch {
	
	Map map; 
	
	int limit; //integer depth limit
	
	int nodeExpansionCount; //To keep track of expansion count
	
	String start; //start location
	String finish; //finish location

	public BFSearch(Map map, String start, String finish, int limit) //constructor
	{
		//Store argument values into instance variables
		
		this.map = map;
		this.start = start;
		this.finish = finish;
		this.limit = limit - 1;
		
	}
	
	public Node search(boolean isExplored)
	{
		Frontier frontier = new Frontier();  
		Set<String> locationsExplored = new HashSet<String>(); //storing locations explored
		
		nodeExpansionCount = 0;
		
		Location indexLocation = map.findLocation(start); //find index Location using findLocation()
		Node index = new Node(indexLocation); //keeping track of current index node
		int indexDepth = index.depth; // helper variable to keep track of index depth
		
		frontier.addToBottom(index);
		locationsExplored.add(index.loc.name);
		
		while(frontier.isEmpty() == false) //while not empty
		{
			index = frontier.removeTop(); //set index Node to top, remove
			
			if(nodeExpansionCount > limit) //if count > limit, return null
			{
				return null;
			}
			
			if(indexDepth > limit) //if depth greater than or equal to limit, return null
			{
				return null;
			}		
			
			if(index.isDestination(finish) == true) //if index node location = destination
			{
				return index;
			}
			
			if(start == finish) //if start = finish, return index node
			{
				return index;
			}
			
			index.expand();
			nodeExpansionCount++;
					
			if(isExplored == true)
			{
				for(Node next: index.children)
				{
					boolean isContains = locationsExplored.contains(next.loc.name);
							
					if(isContains == false) //WITH repeated check, added if statement to check if in locationsExplored
					{
						frontier.addToBottom(next);
						locationsExplored.add(next.loc.name);
					}
				}
			}
			
			else
			{
				for(Node next: index.children) //next = next node after index
				{
					{
						//WITHOUT repeated check
						frontier.addToBottom(next);
						locationsExplored.add(next.loc.name);
					}
				}
			}
				
		}
		
		return null; //else return null
	}
}
