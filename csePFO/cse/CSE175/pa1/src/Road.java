//
// Road
//
// This class implements a segment of road directly connecting two nearby
// locations on a map. Thus, Road objects form the "links" between location
// "states", and the collection of all Road objects leading out of a given
// location provides the result of the "successor function" for that "state".
// Each road segment has a name. While it would be nice if these road names
// were unique, there is nothing in this or related classes that depends on
// road names being unique identifiers. (This is unlike Location names, which
// must be unique.)  Each Road also maintains the names of "from" and "to" 
// locations, as well as references to the actual Location objects 
// corresponding to those locations. (Note that this is slightly redundant,
// as the Location objects know their own names, but this redundancy makes
// the reading of maps from files a little easier.) Lastly, each Road object
// has an incremental path cost:  the cost, in either time or distance, of
// traversing this road segment.
//
// David Noelle -- Sun Feb 11 17:53:48 PST 2007
//                 Modified Sun Sep 23 18:34:05 PDT 2018
//                   (Made minor changes.)
//


import java.io.*;
import java.util.*;


public class Road {
    public String name;
    public String fromLocationName;
    public String toLocationName;
    public Location fromLocation;
    public Location toLocation;
    public double cost = 0.0;


	// read -- Read a road segment description from the given stream into this
	// object. Every road segment description must include the following
	// fields, separated by whitespace: a textual name, a textual "from"
	// location name, a textual "to" location name, and a double precision
	// floating point incremental path cost. Return true if and only if all
	// fields are successfully read.
	public boolean read(BufferedReader str) {
		try {
			String thisLine = str.readLine();
			if (thisLine == null)
				// No more input, at all ...
				return (false);
			Scanner inScanner = new Scanner(thisLine);
			inScanner.useDelimiter("\\s+");
			if (!inScanner.hasNext()) {
				inScanner.close();
				return (false);
			}
			name = inScanner.next();
			if (!inScanner.hasNext()) {
				inScanner.close();
				return (false);
			}
			fromLocationName = inScanner.next();
			fromLocation = null;
			if (!inScanner.hasNext()) {
				inScanner.close();
				return (false);
			}
			toLocationName = inScanner.next();
			toLocation = null;
			if (!inScanner.hasNextDouble()) {
				inScanner.close();
				return (false);
			}
			cost = inScanner.nextDouble();
			inScanner.close();
			return (true);
		} catch (IOException e) {
			// Something went wrong ...
			return (false);
		}
	}

	// write -- Write a description of this Road object to the given stream.
	// If "showLocs" is false, then only write the name of the road segment.
	// If "showLocs" is true, then generate a more verbose description of
	// the road segment that includes the names of the "from" and "to"
	// locations.
	public void write(OutputStream str, boolean showLocs) {
		PrintWriter out = new PrintWriter(str, true);
		if (showLocs) {
			out.printf("%s FROM %s TO %s", name, fromLocationName, toLocationName);
		} else {
			out.printf("%s", name);
		}
	}

}

