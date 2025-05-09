//
// Node
//
// This class implements a node in a search tree being constructed to find
// a shortest path from one location to another on a map. Each node includes
// a reference to the corresponding location "state", a reference to its 
// parent in the search tree (i.e., the "parent" node), and a collection
// of children nodes which remains empty until the node is expanded. Each
// Node object also records the depth of the node in the search tree and
// the partial path cost from the initial node in the search tree to
// this one. This class provides two noteworthy methods. First, the
// "expand" method fills in the "children" list of this node, using
// information embedded in this node's Location object. Second, the
// "reportSolution" recursive method uses the "parent" references of
// nodes in the search tree in order to output the path from the
// initial node of the search tree to this node.
//
// David Noelle -- Sun Sep 23 18:25:04 PDT 2018
//


import java.io.*;
import java.util.*;


public class Node {
    public Location loc;
    public Node parent;
    public List<Node> children;
    public int depth = 0;
    public double partialPathCost = 0.0;
    public double heuristicValue = 0.0;

	// Default constructor ...
	public Node() {
		this.children = new ArrayList<Node>();
	}

	// Constructor with Location object specified ...
	public Node(Location loc) {
		this();
		this.loc = loc;
	}

	// Constructor with Location object and parent node specified ...
	public Node(Location loc, Node parent) {
		this(loc);
		this.parent = parent;
	}

	// expand -- Fill in the collection of children of this node, stored in
	// it's "children" variable. Make sure that each child is appropriately
	// linked into the search tree, and make sure that it's partial path cost
	// is correctly calculated. This version of this method, which takes no
	// arguments, always sets the heuristic values of nodes to zero.
	public void expand() {
		children.removeAll(children);
		for (Road r : loc.roads) {
			Node child = new Node(r.toLocation, this);
			child.depth = this.depth + 1;
			child.partialPathCost = this.partialPathCost + r.cost;
			child.heuristicValue = 0.0;
			children.add(child);
		}
	}

	// expand -- Fill in the collection of children of this node, stored in
	// it's "children" variable. Make sure that each child is appropriately
	// linked into the search tree, and make sure that it's partial path cost
	// is correctly calculated. This version of this method, which takes a
	// heuristic function object as an argument, uses the given heuristic
	// function to fill in the heuristic values of the children nodes.
	public void expand(Heuristic h) {
		children.removeAll(children);
		for (Road r : loc.roads) {
			Node child = new Node(r.toLocation, this);
			child.depth = this.depth + 1;
			child.partialPathCost = this.partialPathCost + r.cost;
			child.heuristicValue = h.heuristicValue(child);
			children.add(child);
		}
	}

	// isDestination -- Return true if and only if the name of the
	// location corresponding to this node matches the provided argument.
	public boolean isDestination(String destinationName) {
		return (loc.name.equals(destinationName));
	}

	// reportSolution -- Output a textual description of the path from the
	// root of the search tree (i.e., the initial node) to this node, sending
	// the description to the given stream. Note that this method is
	// recursive; a recursive call outputs the path up to the parent of this
	// node before the final road segment in the path is described.
	public void reportSolution(OutputStream str) {
		PrintWriter out = new PrintWriter(str, true);
		if (parent == null) {
			// This is the starting point ...
			out.printf("START AT ");
			loc.write(str, false);
			out.printf(".\n");
		} else {
			// First provide the solution up until this point ...
			parent.reportSolution(str);
			// Now report the road segment to this point ...
			out.printf("TAKE ");
			(parent.loc.findRoad(loc)).write(str, true);
			out.printf(".\n");
		}
	}

}
