package tests;

import static org.junit.Assert.*;

import org.junit.Test;

import pig.ConservativePlayer;
import pig.Player;
import pig.RiskyPlayer;

import arraylist.TrackedArrayList;
 
import edu.berkeley.eduride.EduRideTest.Name;
import edu.berkeley.eduride.EduRideTest.Description;
import edu.berkeley.eduride.EduRideTest.hideWhenSuccessful;


@Description("Tests for ConservativePlayer.")
public class ConservativePlayerTest {


	
	
	@Test
	@Name("Implements conservative strategy")
	public void testConservativeStrategy() {
		ConservativePlayer p = new ConservativePlayer();
		Player opponent = new Player();
		for (int i=0; i<20; i++) {
			assertTrue("ConservativePlayer chose not to throw again!", p.throwAgain(opponent));

		}
	}
	
	
	
}
