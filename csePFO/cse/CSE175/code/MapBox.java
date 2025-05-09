import java.util.ArrayList;
import java.util.HashSet;

//David Wang, CSE 175 Fall 2019

public class MapBox{
	
	public ArrayList<Location> locations; //arraylist to store location objects
	public HashSet<String> recordedLocation; //hashset for recordedLocation function
	
	public MapBox() //default constructor
	{
	
		this.locations = new ArrayList<Location>(); //create new instance of locations with every instance of MapBox
		this.recordedLocation = new HashSet<String>(); //new instance of recordedLocation to store each instance's location names
	}
	
	public double Westmost() //find minimum x 
	{
		double minimum = locations.get(0).longitude; //store first element's longitude by default
		
		for(int i = 1; i < locations.size(); i++) //iterate through loop starting from 1 since first element stored, comparing value at each index to next to find smaller values
		{
			if(minimum > locations.get(i).longitude) //if minimum is larger locations.get(i).longitude, store new value into minimum
			{
				minimum = locations.get(i).longitude;
			}
		}
		
		return minimum;
	}
	
	public double Eastmost() //find maximum x
	{
		double maximum = locations.get(0).longitude;
		
		for(int i = 1; i < locations.size(); i++)
		{

			if(maximum < locations.get(i).longitude) //if maximum is smaller than element's longitude, store it as new maximum
			{
				maximum = locations.get(i).longitude;
			}
		}
		
		return maximum;
	}
	
	public double Southmost() //find minimum y
	{
		double minimum = locations.get(0).latitude; //same implementation as WestMost, but with latitude
		
		for(int i = 1; i < locations.size(); i++)
		{
			if(minimum > locations.get(i).latitude)
			{
				minimum = locations.get(i).latitude;
			}
		}
		
		return minimum;
	}
	
	public double Northmost() //find maximum y
	{
		{
			double maximum = locations.get(0).latitude; //same implementation as EastMost, but with latitude
			
			for(int i = 1; i < locations.size(); i++)
			{
				if(maximum < locations.get(i).latitude)
				{
					maximum = locations.get(i).latitude;
				}
			}
			
			return maximum;
		}
	}
	
	public boolean recordLocation(Location loc)
	{
		if (recordedLocation.contains(loc.name)) //if loc's name is already in recordedLocation, return false
		{
			return false;
		}
		
		else //if loc's name is not in recordedLocation
		{
			locations.add(loc); //add loc to locations arrayList
			recordedLocation.add(loc.name); //add loc's name to recordedLocations hashset
			return true;
		}
	}
}
