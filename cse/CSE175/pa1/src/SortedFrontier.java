//
// SortedFrontier
//
// This class implements a priority queue of Node objects, with the next
// object to be removed from the queue being determined by a sorting of
// the contained Node objects. There are three ways in which the
// contents might be sorted, with the sorting strategy determined at the
// time that the priority queue is created. The contents of the priority
// queue can be sorted by partial path cost, by heuristic value, or by the
// sum of these two statistics. The contained object with the lowest value
// is the first to be removed. Note that the insertion method is overloaded
// to accept either an individual Node or a list of multiple Node
// objects. This class is intended to to be used to implement the frontier
// (i.e., the "fringe" or "open list") of nodes in a search tree.
//
// David Noelle -- Created Tue Feb 27 11:25:05 PST 2007
//                 Modified Wed Oct  6 02:32:34 PDT 2010
//                   (Implemented overloaded "contains" and "find" functions.)
//


import java.util.*;
import java.io.*;


enum SortBy { g, h, f }


class NodeComparator implements Comparator<Node>, Serializable {
    static final long serialVersionUID = 1;  // Version 1
    SortBy statistic;

	// Default constructor ...
	public NodeComparator() {
		this.statistic = SortBy.g;
	}

	// Constructor with sorting criterion argument ...
	public NodeComparator(SortBy strategy) {
		this.statistic = strategy;
	}

	// compare -- Determine which of two Nodes is "larger", according
	// to the Comparator protocol.
	public int compare(Node thisNode1, Node thisNode2) {
		// Extract the appropriate statistics ...
		double val1 = 0.0;
		double val2 = 0.0;
		switch (statistic) {
		case g:
			val1 = thisNode1.partialPathCost;
			val2 = thisNode2.partialPathCost;
			break;
		case h:
			val1 = thisNode1.heuristicValue;
			val2 = thisNode2.heuristicValue;
			break;
		case f:
			val1 = thisNode1.partialPathCost + thisNode1.heuristicValue;
			val2 = thisNode2.partialPathCost + thisNode2.heuristicValue;
			break;
		}
		// Compare values ...
		if (val1 < val2)
			return (-1);
		if (val1 > val2)
			return (1);
		if (thisNode1.equals(thisNode2)) {
			// This is the exact same Node ...
			return (0);
		} else {
			// These are two Node objects with the same value, but we
			// still need to put them in some order. Otherwise, two nodes
			// with the same value will "overwrite" each other ...
			if (thisNode1.loc.equals(thisNode2.loc)) {
				// Even the locations are the same, so order the two nodes
				// based on the ordering of their parents in the search
				// tree ...
				return (this.compare(thisNode1.parent, thisNode2.parent));
			} else {
				// The locations differ, so we can use the alphabetical
				// ordering of their names to order the nodes ...
				return (thisNode1.loc.name.compareTo(thisNode2.loc.name));
			}
		}
	}

}
	

public class SortedFrontier {
    SortBy sortingStrategy;
    SortedSet<Node> sortedFringe;
    Map<String, Node> mappedFringe;

	// Default constructor ...
	public SortedFrontier() {
		this.sortingStrategy = SortBy.g;
		Comparator<Node> sortingComparator = new NodeComparator(this.sortingStrategy);
		this.sortedFringe = new TreeSet<Node>(sortingComparator);
		this.mappedFringe = new HashMap<String, Node>();
	}

	// Constructor with sorting strategy specified ...
	public SortedFrontier(SortBy strategy) {
		this.sortingStrategy = strategy;
		Comparator<Node> sortingComparator = new NodeComparator(this.sortingStrategy);
		this.sortedFringe = new TreeSet<Node>(sortingComparator);
		this.mappedFringe = new HashMap<String, Node>();
	}

	// isEmpty -- Return true if and only if there are currently no nodes in
	// the frontier.
	public boolean isEmpty() {
		return (sortedFringe.isEmpty());
	}

	// removeTop -- Return the Node object at the top of the frontier
	// list. Also, remove this node from the frontier. Return null if the
	// frontier is empty.
	public Node removeTop() {
		if (sortedFringe.isEmpty()) {
			return (null);
		} else {
			Node top = sortedFringe.first();
			sortedFringe.remove(top);
			mappedFringe.remove(top.loc.name);
			return (top);
		}
	}

	// addSorted -- Add the given Node object to the frontier in the
	// appropriate position, given its sorting statistics.
	public void addSorted(Node thisNode) {
		sortedFringe.add(thisNode);
		if (mappedFringe.get(thisNode.loc.name) != null) {
			// This is another node with the same location name, which
			// should never appear in the frontier. Still, for the sake
			// of safety, remove it ...
			mappedFringe.remove(thisNode.loc.name);
		}
		mappedFringe.put(thisNode.loc.name, thisNode);
	}
    
	// addSorted -- Add the given list of Node objects to the frontier
	// in the appropriate positions, given their sorting statistics.
	public void addSorted(List<Node> nodeList) {
		for (Node thisNode : nodeList) {
			addSorted(thisNode);
		}
	}

	// remove -- Remove a specified Node object from the frontier.
	public void remove(Node thisNode) {
		sortedFringe.remove(thisNode);
		mappedFringe.remove(thisNode.loc.name);
	}

	// remove -- Remove all of the Node objects in the given list from
	// the frontier.
	public void remove(List<Node> nodeList) {
		for (Node thisNode : nodeList) {
			remove(thisNode);
		}
	}

	// contains -- Return true if and only if the frontier contains a
	// Node with the given Location name.
	public boolean contains(String name) {
		Node thisNode = mappedFringe.get(name);
		return (thisNode != null);
	}

	// contains -- Return true if and only if the frontier contains a
	// Node with the given Location object as its state.
	public boolean contains(Location loc) {
		return (contains(loc.name));
	}

	// contains -- Return true if and only if the frontier contains an
	// equivalent Node (with regard to the Location) to the one provided
	// as an argument.
	public boolean contains(Node thisNode) {
		return (contains(thisNode.loc));
	}

	// find -- Return a Node in the frontier with the given location
	// name, or null if there is no such Node.
	public Node find(String name) {
		Node thisNode = mappedFringe.get(name);
		if (thisNode != null) {
			return (thisNode);
		} else {
			return (null);
		}
	}

	// find -- Return a Node in the frontier with the given location
	// name, or null if there is no such Node.
	public Node find(Location loc) {
		return (find(loc.name));
	}

	// find -- Return a Node in the frontier with the same location
	// name as the provided Node, or null if there is no such Node.
	public Node find(Node thisNode) {
		return (find(thisNode.loc));
	}


}

