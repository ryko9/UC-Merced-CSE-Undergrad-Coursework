//
// StreetMap
//
// This class implements a simple street map for the purposes of shortest-path
// search. It makes use of Location objects to encode specific locations on
// the map and Road objects to encode direct connections between locations.
// These maps are designed to be read from simple text files. In particular,
// two files are needed to specify a map:  a location file and a road file.
// The location file contains a list of all locations on the map, with one
// location per line. The road file contains a list of all road segments on
// the map, with one road segment per line. The pathnames of these two files
// are stored in the StreetMap object, so the files can be specified in 
// advance of their being read and parsed. The map is stored as a collection
// of Location objects, with each Location being given the responsibility of
// maintaining all of the Road objects corresponding to road segments leading
// out of it.
//
// David Noelle -- Sun Feb 11 18:05:18 PST 2007
//                 Modified Sun Sep 23 18:34:05 PDT 2018
//                   (Made minor changes.)
//


import java.io.*;
import java.util.*;


public class StreetMap {
    String locationFilename = "locations.dat";
    String roadFilename = "roads.dat";
    List<Location> locations;

	// Default constructor ...
	public StreetMap() {
		this.locations = new ArrayList<Location>();
	}

	// Constructor with filenames specified ...
	public StreetMap(String locationFilename, String roadFilename) {
		this();
		this.locationFilename = locationFilename;
		this.roadFilename = roadFilename;
	}

	// setLocationFilename -- Record the given pathname of a location file
	// for later use during map reading.
	public void setLocationFilename(String filename) {
		locationFilename = filename;
	}

	// setRoadFilename -- Record the given pathname of a road file for later
	// use during map reading.
	public void setRoadFilename(String filename) {
		roadFilename = filename;
	}

	// promptForFilenames -- Using the standard output stream and the standard
	// input stream, prompt the user to input the pathnames for a location
	// file and for a road file. Record the input pathnames in this
	// StreetMap object for later use during map reading. Return false on
	// error.
	public boolean promptForFilenames() {
		try {
			InputStreamReader converter = new InputStreamReader(System.in);
			BufferedReader in = new BufferedReader(converter);
			String buffer;

			System.out.println("Enter the name of the location file:");
			buffer = in.readLine();
			setLocationFilename(buffer);
			System.out.println("Enter the name of the road file:");
			buffer = in.readLine();
			setRoadFilename(buffer);
		} catch (IOException e) {
			// Something went wrong ...
			return (false);
		}
		return (true);
	}

	// findLocation -- Search through the collection of locations on this map
	// for one with the given textual name. Return a reference to the
	// corresponding Location object, or null if no such location is found.
	public Location findLocation(String name) {
		for (Location loc : locations) {
			if (loc.name.equals(name))
				return (loc);
		}
		return (null);
	}

	// recordLocation -- Add the given Location object to the collection of
	// locations for this map.
	public void recordLocation(Location loc) {
		locations.add(loc);
	}

	// readLocations -- Attempt to open the location file specified by the
	// appropriate pathname stored in this StreetMap object. If this file can
	// be opened for reading, read a collection of locations from this file
	// into the StreetMap object's collection of Location objects. Return
	// false on error.
	public boolean readLocations() {
		try {
			File locFile = new File(locationFilename);
			if (locFile.exists() && locFile.canRead()) {
				FileInputStream locFileIn = new FileInputStream(locFile);
				InputStreamReader locISReader = new InputStreamReader(locFileIn);
				BufferedReader locBufferedReader = new BufferedReader(locISReader);
				// Allocate storage for the first location to be read ...
				Location loc = new Location();
				while (loc.read(locBufferedReader)) {
					// Record location in the map ...
					recordLocation(loc);
					// Allocate storage for the next location ...
					loc = new Location();
				}
				return (true);
			} else {
				// The file cannot be read ...
				return (false);
			}
		} catch (IOException e) {
			// Something went wrong ...
			return (false);
		}
	}

	// readRoads -- Attempt to open the road file specified by the appropriate
	// pathname stored in this StreetMap object. If this file can be opened for
	// reading, read a collection of roads from this file. Generate
	// corresponding Road objects and store those objects in the appropriate
	// Location objects in this StreetMap object's collection of locations.
	// Note that this means that the map must know about all locations on the
	// map before a road file is read. This can be done by calling the
	// "readLocations" method before calling this method. Return false on
	// error.
	public boolean readRoads() {
		try {
			File roadFile = new File(roadFilename);
			if (roadFile.exists() && roadFile.canRead()) {
				FileInputStream roadFileIn = new FileInputStream(roadFile);
				InputStreamReader roadISReader = new InputStreamReader(roadFileIn);
				BufferedReader roadBufferedReader = new BufferedReader(roadISReader);
				// Allocate storage for the first road segment ot be read ...
				Road r = new Road();
				while (r.read(roadBufferedReader)) {
					// Fill in connections to location objects ...
					r.fromLocation = findLocation(r.fromLocationName);
					if (r.fromLocation == null) {
						System.err.printf("The location, %s, is not known.\n", r.fromLocationName);
						roadBufferedReader.close();
						return (false);
					}
					r.toLocation = findLocation(r.toLocationName);
					if (r.toLocation == null) {
						System.err.printf("The location, %s, is not known.\n", r.toLocationName);
						roadBufferedReader.close();
						return (false);
					}
					// Record the road in the appropriate location ...
					r.fromLocation.recordRoad(r);
					// Allocate storage for the next road segment ...
					r = new Road();
				}
				return (true);
			} else {
				// The specified road file could not be read ...
				return (false);
			}
		} catch (IOException e) {
			// Something went wrong ...
			return (false);
		}
	}

	// readMap -- Prompt the user for the pathnames of a location file and
	// a road file, and then read those files into this StreetMap object.
	// Return false on error.
	public boolean readMap() {
		return (promptForFilenames() && readLocations() && readRoads());
	}

}

