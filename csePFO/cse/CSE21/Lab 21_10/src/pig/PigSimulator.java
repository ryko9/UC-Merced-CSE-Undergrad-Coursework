package pig;

import java.util.Random;

public class PigSimulator {
	
	// used to roll dice and pick the starting player
	private static Random r = new Random ( );

	public static void main (String [ ] args) {
		PigSimulator game = new PigSimulator ( );
		Player [ ] players = new Player [2];
		players[0] = new ConservativePlayer ( );
		players[1] = new RiskyPlayer ( );

		
		int [ ] totalWins = {0, 0};
		for (int k=0; k<9; k++) {
			System.out.println("\n -- Game " + k);
			totalWins[game.play1game (players)]++;
			System.out.println ("Player 0 scored " + players[0].total ( ) 
					+ ", player 1 scored " + players[1].total ( )); 
		} 
	
		//task  7
		
		PigSimulator game2 = new PigSimulator(); 	//second simulator to calculate results for player 2 and player 3
		Player [] players1 = new Player[2];  		//new array to store player 2 and player 3, 
													//since I couldn't figure out how to use a four object array in the play1game method
		players1[0] = new RollEightPlayer(); 		//player 2. new strategy of rolling only eight times
		players1[1] = new RollTenPlayer();   		//player 3, new strategy of rolling only ten times
		
		int [ ] totalWins1 = {0, 0};
		for (int k=0; k<9; k++) {
			System.out.println("\n -- Game " + k);
			totalWins1[game2.play2game (players1)]++;
			System.out.println ("Player 2 scored " + players1[0].total ( ) 
					+ ", player 3 scored " + players1[1].total ( )); 
		}
		System.out.println ("Player 0 won " + totalWins[0] + ", player 1 won " + totalWins[1]);
		System.out.println ("Player 2 won " + totalWins1[0] + ", player 3 won " + totalWins1[1]); 
		
	}
	
	
	
	
	// Returns 0 if player 0 wins, 1 if player 1 wins.
	public int play1game (Player [ ] players) {
		players[0].initGame();
		players[1].initGame();
		
		int currentPlayer = r.nextInt(2);
		boolean wonGame = false;
		while (!wonGame) { 
			currentPlayer = 1 - currentPlayer;
			System.out.println ("player " + currentPlayer + ": score = " + players[currentPlayer].total ( ));
			play1turn (players[currentPlayer], players[1 - currentPlayer]);
			wonGame = players[currentPlayer].won ( );
		}
		return currentPlayer;
	}
	

	
	public void play1turn (Player p, Player opponent) {
		boolean okRoll;
		p.initTurn ( );
		do {
			int roll = r.nextInt (6) + 1;
			System.out.print (" Roll " + roll + "   ");
			okRoll = p.tallyRoll (roll);
		} while (okRoll && !p.won ( ) && p.throwAgain ( opponent ));
		System.out.println ( );
		if (okRoll) {
			p.updateTotal ( );
		}
	}
	
	//task 7
	public int play2game(Player [] players){
		players[0].initGame(); //player 2
		players[1].initGame(); //player 3
		
		int currentPlayer = r.nextInt(2); //random number from 2 to 3 for the new players created for task 7
		boolean wonGame = false;
		while (!wonGame) { 
			currentPlayer = 1 - currentPlayer;
			System.out.println ("player " + (currentPlayer + 2) + ": score = " + players[currentPlayer].total ( )); 
			play2turn (players[currentPlayer], players[1 - currentPlayer]);
			wonGame = players[currentPlayer].won ( );
		}
		return currentPlayer;
	}
	public void play2turn (Player p, Player opponent) {
		boolean okRoll;
		p.initTurn ( );
		do {
			int roll = r.nextInt (6) + 1;
			System.out.print (" Roll " + roll + "   ");
			okRoll = p.tallyRoll (roll);
		} while (okRoll && !p.won ( ) && p.throwAgain ( opponent ));
		System.out.println ( );
		if (okRoll) {
			p.updateTotal ( );
		}
	
//		Wasn't sure how to use a four object method in the play1game method, so I made a play2game and play2turn to correspond to my new
//      two object array.
//      Just made a new two object array with the 2 new players and used the code from the original methods with slightly altered
//      variables to change the numbering in the output.
}
}
