package pig;

import java.util.Random;

public class Player {

	// score for current game
	private int myTotal;
	// score for the current turn
	private int myTurnTotal;
	// number of rolls in the current turn
	private int myRollCount;
	
	public static final int WINNING_TOTAL = 100;
	public static Random r = new Random ( );
	
	public Player ( ) {
		myTotal = 0;
	}
	
	// initializes field when a new game is started
	public void initGame ( ) {
		myTotal = 0;
	} 	
	
	// initializes fields for a new turn
	public void initTurn ( ) {
		myTurnTotal = 0;
		myRollCount = 0;
	}
	
	
	public int total ( ) {
		return myTotal;
	}
	
	public int turnTotal ( ) {
		return myTurnTotal;
	}
	
	public int rollCount ( ) {
		return myRollCount;
	}
	
	
	public boolean tallyRoll (int roll) {
		if (roll == 1) {
			myTurnTotal = 0;
			return false;
		} else {
			myTurnTotal += roll;
			myRollCount++;
			return true;
		}
	}
	
	public boolean won ( ) {
		return myTotal + myTurnTotal >= WINNING_TOTAL;
	}
	
	public void updateTotal ( ) {
		myTotal += myTurnTotal;
		myTurnTotal = 0;
	}
	
	public boolean throwAgain ( Player opponent ) {
		// this player randomly chooses whether to throw again or not
		return r.nextBoolean();
	}
}
