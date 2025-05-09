import java.util.Scanner;

public class ScorerCombo {

    // the number of innings in a regulation game (after which only tie scores continue)
    // in MLB, this is 9.  A smaller number will make manual testing easier.
    public static int REGULATION_NUM_INNINGS = 9;
    
    // assume game can never go over this number of innings (used when allocating arrays)
    public static int MAX_BOX_SCORE_LENGTH = 20;
    
    // value in a boxScore: an indicator that a half-inning hasn't been played yet
    // this need to be distinguishable from a baseball score
    public static final int SENTINEL = -999;
    
    // indicators on which team is currently batting
    private static final int VISITORS = 1;
    private static final int HOME = 2;
    
    public static void initialize (int[] visitorScores, int [] homeScores ) {
        // Your code goes here.    
        // Only should deal with the two parameters 
        
        for(int i = 0; i < visitorScores.length; i++)
        {
            visitorScores[i] = SENTINEL;
            homeScores[i] = SENTINEL;
        }
                
    }
    
    // Read the scores for each half of each inning until the end of the game,
    // and fill-in the boxScore arrays for visitors and home.
    // The scanner returns first the visiting team's score in the first half
    // of the first inning, then the home team's score in the second half of
    // the first inning, then the visiting team's score in the first half of
    // second inning, and so on. If the game is over, no more values remain
    // to be returned from the scanner.
    public static void readScores(Scanner scores, int[] visitorScores, int[] homeScores) {
        
        int batter = VISITORS;  // 1 is visitor, 2 is home
        int inning = 1;
        
        while (!gameIsOver(inning, batter, visitorScores, homeScores)) 
        {
            
            if(batter == VISITORS)
            {

                visitorScores[inning - 1] = scores.nextInt();    
                batter = HOME;
            
            }
            
            else
            {
                
                homeScores[inning - 1] = scores.nextInt();
                
                batter = VISITORS;
                inning++;
            }
        }

    }

    
    // Takes a int[] representing a team's scores over all innings,
    // and returns the total runs.
    public static int gameScore(int[] teamBoxScore) {
        int output = 0;
        for (int i : teamBoxScore) {
            if (i != SENTINEL) {
                output += i;
            }
        }
        return output;
    }
    
    // Count the innings
    public static int innings(int[] teamBoxScore) {
        int output = 0;
        for (int i : teamBoxScore) {
            if (i != SENTINEL) {
                output++;
            }
        }
        return output;
    }
    
    
    // Determine if the game is over, that is, either we've played
    // at least nine complete innings and the score isn't tied,
    // or eight-and-a-half innings and the home team is ahead.
    // batter contains 1 if the visitors are about to bat (and thus
    // we've completed both halves of the inning), and contains 2
    // if the home team is about to bat (and thus we've completed
    // only the first half of the inning).
    public static boolean gameIsOver(int inning, int batter, int[] visitorScores, int[] homeScores) {
        
        int visitorScore = gameScore(visitorScores);
        int homeScore = gameScore(homeScores);
        
        return (inning > REGULATION_NUM_INNINGS && batter == VISITORS && visitorScore != homeScore)
                || (inning == REGULATION_NUM_INNINGS && batter == HOME && visitorScore < homeScore);
    }
    
    // Print the box score Version 1
    public static void printBoxScore(int[] visitorScores, int[] homeScores) {
        
        System.out.println();
        System.out.print(" Visitor: ");
        for (int v : visitorScores) {
            if (v != SENTINEL) {
                System.out.print(v);
            }
        }
        System.out.println();
        
        System.out.print("    Home: ");
        for (int v : homeScores) {
            if (v != SENTINEL) {
                System.out.print(v);        
            }
        }            
        System.out.println();
    }

    // Print the box score Version 2
    public static int printBoxScore(int[] teamBoxScore) {
        int i;
        for (i = 0; i < teamBoxScore.length; i++) {
            if (teamBoxScore[i] != SENTINEL) {
                System.out.print(teamBoxScore[i] + " ");
            } else
                break;
        }
        System.out.println();
        return i;
    }
    
    // Print the box score Version 3
    public static int printBoxScore(String name, int[] teamBoxScore) {
        System.out.print(name);
        return printBoxScore(teamBoxScore);
    }
    
    // result Version 1
    // The game is over. Return a string that describes the outcome.
    public static String result(int inning, int visitorScore, int homeScore) 
    {
    	if(visitorScore > homeScore) 
        {
        	return("The visiting team won " + visitorScore + " to " + homeScore + " in " + inning + " innings.");
        }
        else
        {
        	return("The home team won " + homeScore + " to " + visitorScore + " in " + inning + " innings.");
        }
    }

    // result Version 2
    // The game is over. Print the box Score first
    // Return a string that describes the outcome.
    public static String result(int[] visitorScores, int[] homeScores) {
        
        int visitorScore = gameScore(visitorScores);
        int homeScore = gameScore(homeScores);

        int inning = printBoxScore(" Visitor: ", visitorScores);
        
        printBoxScore("    Home: ", homeScores);
        
        return result(inning, visitorScore, homeScore);
    }
    
    public static void main(String[] args) {

        int[] visitorScores = new int [MAX_BOX_SCORE_LENGTH]; 
        int[] homeScores = new int [MAX_BOX_SCORE_LENGTH];
        
        initialize(visitorScores, homeScores);
        
        Scanner input = new Scanner(System.in);
        System.out.print("Do you want to see BoxScore? (y or n): ");
        String answer = input.next();
        
        System.out.println("Please enter the scores below");
        readScores(input, visitorScores, homeScores);
        
        if (answer.charAt(0) == 'y' || answer.charAt(0) == 'Y') 
        {
            System.out.println(result(visitorScores, homeScores));
        }
        
        else 
        {
            // Call result Version 1
        	        //inning, visitor score, gamescore
            System.out.println(result(innings(visitorScores), gameScore(visitorScores), gameScore(homeScores)));
        }
        

    }
}
