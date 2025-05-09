//
// Pone
//
// This class provides a "main" method that acts as a driver program for
// evaluating a variety of heuristic search algorithms, as applied to 
// shortest-path searches on a map. A StreetMap object is used to read in
// and record a map from two files:  one containing a list of locations and
// the other containing a list of road segments. The user is then prompted
// for a starting location on this map and a destination location. Three
// search algorithms are then tested on this specified search problem:
// uniform-cost search, greedy search, and A* search. Also, the effect of
// repeated state checking is examined. A depth limit is provided to the
// search algorithms, and the algorithms are expected to terminate and 
// report failure if that depth limit is ever reached during search. Summary
// results are sent to the standard output stream.
//
// David Noelle -- Wed Feb 21 17:17:38 PST 2007
//                 Modified Mon Sep 23 21:48:06 PDT 2019
//                   (Made minor changes.)
//


import java.io.*;


public class Pone {

    public static void main(String[] args) {
	try {
			StreetMap graph = new StreetMap();
			InputStreamReader converter = new InputStreamReader(System.in);
			BufferedReader in = new BufferedReader(converter);
			String initialLoc;
			String destinationLoc;
			Node solution;
			int limit = 1000; // depth limit, to avoid infinite loops

			System.out.println("HEURISTIC SEARCH ALGORITHM COMPARISON");
			// Read map ...
			if (!(graph.readMap())) {
				System.err.println("Error:  Unable to read map.");
				return;
			}
			// Get initial and final locations ...
			System.out.println("Enter the name of the initial location:");
			initialLoc = in.readLine();
			System.out.println("Enter the name of the destination location:");
			destinationLoc = in.readLine();

			// Testing uniform-cost search without repeated state checking ...
			System.out.println("TESTING UNIFORM-COST SEARCH WITHOUT REPEATED STATE CHECKING");
			UniformCostSearch ucs = new UniformCostSearch(graph, initialLoc, destinationLoc, limit);
			solution = ucs.search(false);
			System.out.println("Solution:");
			if (solution == null) {
				System.out.println("None found.");
			} else {
				solution.reportSolution(System.out);
				System.out.printf("Path Cost = %f.\n", solution.partialPathCost);
			}
			System.out.printf("Number of Node Expansions = %d.\n", ucs.nodeExpansionCount);

			// Testing uniform-cost search with repeated state checking ...
			System.out.println("TESTING UNIFORM-COST SEARCH WITH REPEATED STATE CHECKING");
			solution = ucs.search(true);
			System.out.println("Solution:");
			if (solution == null) {
				System.out.println("None found.");
			} else {
				solution.reportSolution(System.out);
				System.out.printf("Path Cost = %f.\n", solution.partialPathCost);
			}
			System.out.printf("Number of Node Expansions = %d.\n", ucs.nodeExpansionCount);

			// Testing greedy search without repeated state checking ...
			System.out.println("TESTING GREEDY SEARCH WITHOUT REPEATED STATE CHECKING");
			GreedySearch gs = new GreedySearch(graph, initialLoc, destinationLoc, limit);
			solution = gs.search(false);
			System.out.println("Solution:");
			if (solution == null) {
				System.out.println("None found.");
			} else {
				solution.reportSolution(System.out);
				System.out.printf("Path Cost = %f.\n", solution.partialPathCost);
			}
			System.out.printf("Number of Node Expansions = %d.\n", gs.nodeExpansionCount);

			// Testing greedy search with repeated state checking ...
			System.out.println("TESTING GREEDY SEARCH WITH REPEATED STATE CHECKING");
			solution = gs.search(true);
			System.out.println("Solution:");
			if (solution == null) {
				System.out.println("None found.");
			} else {
				solution.reportSolution(System.out);
				System.out.printf("Path Cost = %f.\n", solution.partialPathCost);
			}
			System.out.printf("Number of Node Expansions = %d.\n", gs.nodeExpansionCount);

			// Testing A* search without repeated state checking ...
			System.out.println("TESTING A* SEARCH WITHOUT REPEATED STATE CHECKING");
			AStarSearch as = new AStarSearch(graph, initialLoc, destinationLoc, limit);
			solution = as.search(false);
			System.out.println("Solution:");
			if (solution == null) {
				System.out.println("None found.");
			} else {
				solution.reportSolution(System.out);
				System.out.printf("Path Cost = %f.\n", solution.partialPathCost);
			}
			System.out.printf("Number of Node Expansions = %d.\n", as.nodeExpansionCount);

			// Testing A* search with repeated state checking ...
			System.out.println("TESTING A* SEARCH WITH REPEATED STATE CHECKING");
			solution = as.search(true);
			System.out.println("Solution:");
			if (solution == null) {
				System.out.println("None found.");
			} else {
				solution.reportSolution(System.out);
				System.out.printf("Path Cost = %f.\n", solution.partialPathCost);
			}
			System.out.printf("Number of Node Expansions = %d.\n", as.nodeExpansionCount);

			// Done ...
			System.out.println("ALGORITHM COMPARISON COMPLETE");
		} catch (IOException e) {
			// Something went wrong ...
		}
	}
    
}
