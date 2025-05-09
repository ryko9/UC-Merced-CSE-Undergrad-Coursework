package tests;

import static org.junit.Assert.*;

import org.junit.Test;

import pig.Player;
import pig.RiskyPlayer;

import arraylist.TrackedArrayList;
 
import edu.berkeley.eduride.EduRideTest.Name;
import edu.berkeley.eduride.EduRideTest.Description;
import edu.berkeley.eduride.EduRideTest.hideWhenSuccessful;


@Description("Tests for RiskyPlayer.")
public class RiskyPlayerTest {

	

	
	
	
	@Test
	@Name("Implements risky strategy")
	public void testRiskyStrategy() {
		RiskyPlayer p = new RiskyPlayer();
		Player opponent = new Player();
		for (int i=0; i<20; i++) {
			assertTrue("RiskyPlayer chose to throw again!", p.throwAgain(opponent));

		}
	}
	
	
	
}
