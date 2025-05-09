//
// Location
//
// This class implements a place on a map. It is a single "state" in the
// "state space" to be searched for a short route from one location to
// another. Each location includes a textual name, a pair of Cartesian
// coordinates, and a collection of Road objects which encode the immediate
// routes leading away from this location. Note that textual names are
// assumed to be unique; two locations are considered the same if they have
// the same name.
//
// David Noelle -- Sun Feb 11 17:37:21 PST 2007
//


import java.io.*;
import java.util.*;


public class Location {
    public String name = "";
    public double longitude = 0.0;
    public double latitude = 0.0;
    public List<Road> roads;

	// Default constructor ...
	public Location() {
		this.roads = new ArrayList<Road>();
	}

	// Constructor with location name specified ...
	public Location(String name) {
		this();
		this.name = name;
	}

	// Constructor with location name and coordinates specified ...
	public Location(String name, double longitude, double latitude) {
		this(name);
		this.longitude = longitude;
		this.latitude = latitude;
	}

	// equals -- Return true if and only if this location has the same name
	// as the argument location.
	public boolean equals(Location loc) {
		return (loc.name.equals(this.name));
	}

	// read -- Read a location description from the given stream into this
	// object. At minimum, a name must be read from the stream. Optionally,
	// coordinates may also be specified as a pair of double precision
	// floating point numbers. Return true if at least a name was read and
	// false otherwise.
	public boolean read(BufferedReader str) {
		try {
			String thisLine = str.readLine();
			if (thisLine == null)
				// No more input, at all ...
				return (false);
			Scanner inScanner = new Scanner(thisLine);
			inScanner.useDelimiter("\\s+");
			if (inScanner.hasNext()) {
				// There is something to read ...
				name = inScanner.next();
				if (inScanner.hasNextDouble()) {
					// There is a longitude to read ...
					longitude = inScanner.nextDouble();
					if (inScanner.hasNextDouble()) {
						// There is a latitude to read ...
						latitude = inScanner.nextDouble();
					}
				}
				// At least a name was successfully read ...
				inScanner.close();
				return (true);
			} else {
				// Did not even read a name ...
				inScanner.close();
				return (false);
			}
		} catch (IOException e) {
			// Something went wrong ...
			return (false);
		}
	}

	// write -- Write the name of this location to the given stream. If the
	// "showCoords" argument is true, then also output the Cartesian
	// coordinates of this location, separated by blanks, on the same line.
	public void write(OutputStream str, boolean showCoords) {
		PrintWriter out = new PrintWriter(str, true);
		out.printf("%s", name);
		if (showCoords) {
			out.printf(" %f %f", longitude, latitude);
		}
	}

	// findRoad -- Search the collection of roads leading out of this
	// location for one that leads directly to the argument destination
	// location. Return this Road object if it is found, or null if no
	// matching road is found.
	public Road findRoad(Location destination) {
		for (Road r : roads) {
			if (r.toLocation.equals(destination))
				return (r);
		}
		return (null);
	}

	// recordRoad -- Add the given Road object to the collection of roads
	// leading out of this location.
	public void recordRoad(Road r) {
		roads.add(r);
	}

}

