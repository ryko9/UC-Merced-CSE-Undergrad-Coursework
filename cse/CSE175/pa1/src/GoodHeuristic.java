//
// GoodHeuristic
//
// This class extends the Heuristic class, providing a reasonable
// implementation of the heuristic function method. The provided "good"
// heuristic function is admissible.
//
// DAVID WANG -- 10/11/2019
//


// IMPORT ANY PACKAGES THAT YOU NEED.
// import java.util.*;

import java.lang.Math;

public class GoodHeuristic extends Heuristic 
{


	StreetMap map; //initialize Streetmap object
	double v; //v for velocity
	double index; //value to use for comparison

	public GoodHeuristic(StreetMap map, Location finish)
	{

		super.setDestination(finish); //call setDestination using super to set destination to finish, since GoodHeuristic inherits heuristic

		this.map = map;

		//calculate velocity
		
		v = 0.0; //initialize velocity to 0

		for(Location loc: map.locations)
		{
			for(Road r : loc.roads)
			{
				//using euclidian distance formula to calculate distance

				//distance = Sqrt(X^2 + Y^2)

				double dLatitude; //difference in latitude
				double dLongitude; //difference in longitude;


				dLatitude = r.fromLocation.latitude - r.toLocation.latitude;
				dLongitude = r.fromLocation.longitude - r.toLocation.longitude;

				double latSq = Math.pow(dLatitude, 2); //dLat squared
				double longSq = Math.pow(dLongitude, 2); //dLong squared


				//distance = Sqrt(dLat^2 + dLong^2)
				index = Math.sqrt(latSq + longSq); 

				//velocity = distance / time

				index = index / r.cost; //divide distance by cost to get velocity

				if(v < index) //compare initial velocity of 0 to index's value
				{
					v = index; //store index into v if higher than v
				}


			}
		}

		this.v = v; //set member variable to the final velocity value
	}

	// heuristicValue -- Return the appropriate heuristic values for public void testName() throws Exception {}
	// given search tree node. Note that the given Node should not be
	// modified within the body of this function.
	public double heuristicValue(Node thisNode) 
	{

		Location loc = thisNode.loc;

		double hVal = 0.0;	

		// COMPUTE A REASONABLE HEURISTIC VALUE HERE

		double x = loc.latitude - destination.latitude;
 
		double y = loc.longitude - destination.longitude;

		double xSq = Math.pow(x, 2); //x squared

		double ySq = Math.pow(y, 2); //y squared

		//distnace = sqrt ( x^2 - y^2 s)

		hVal = Math.sqrt(xSq + ySq);

		hVal = hVal / v;

		return (hVal);
	}
	
}

