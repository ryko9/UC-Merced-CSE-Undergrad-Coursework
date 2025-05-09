package tests;

import static org.junit.Assert.*;

import io.People;
import io.Person;
import java.util.ArrayList;
import org.junit.Test;
import edu.berkeley.eduride.EduRideTest;
import edu.berkeley.eduride.EduRideTest.Description;

@Description("Test for the People class")
public class PeopleTest extends EduRideTest {

	@Test
	@Name("Reading People objects from a file")
	public void test ( ) {
		ArrayList<Person> correct = new ArrayList<Person> ( );
		correct.add (new Person ("Obama", 52, "Washington, DC"));
		correct.add (new Person ("Washington", 67, "New York City, NY"));
		correct.add (new Person ("Joe Moonbeam", 105, "The moon"));
		People group = new People (	);
		ArrayList<Person> computed = group.readFile ("lib/tests/presidents.txt");
		assertEquals ("Number of People read incorrect", correct.size(), computed.size());
		personFieldsEqual ("First People object incorrectly read", correct.get(0), computed.get(0));
		personFieldsEqual ("Second People object incorrectly read", correct.get(1), computed.get(1));
		personFieldsEqual ("Third People object incorrectly read", correct.get(2), computed.get(2));

	}

	


	// checks each field and throws assertion if not equal
	private static void personFieldsEqual(String errMsg, Person expected, Person observed) {
		assertEquals(errMsg + ": incorrectly read name ", expected.getName(), observed.getName());
		assertEquals(errMsg + ": incorrectly read age ", expected.getAge(), observed.getAge());
		assertEquals(errMsg + ": incorrectly read location ", expected.getLocation(), observed.getLocation());
	}


}
