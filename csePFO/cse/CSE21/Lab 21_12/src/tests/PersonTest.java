package tests;

import static org.junit.Assert.*;
import io.Person;
import org.junit.Test;
import edu.berkeley.eduride.EduRideTest;
import edu.berkeley.eduride.EduRideTest.Description;

@Description("Tests for building and modifying Person instances")
public class PersonTest extends EduRideTest {

	@Test
	@Name("Building and inspecting Person")
	public void test() {
		Person p = new Person ("Obama", 52, "Washington, DC");
		for (int k=0; k<2; k++) {
			assertEquals ("wrong result when getting person's name after creating it", 
					"Obama", p.getName());
			assertEquals ("wrong result when getting person's age after creating it", 
					52, p.getAge());
			assertEquals ("wrong result when getting person's location after creating it", 
					"Washington, DC", p.getLocation());
		}
		p.setName("Washington");
		p.setAge(67);
		p.setLocation("New York City, NY");
		for (int k=0; k<2; k++) {
			assertEquals ("wrong result when getting person's name after setting it", 
					"Washington", p.getName());
			assertEquals ("wrong result when getting person's age after setting it", 
					67, p.getAge());
			assertEquals ("wrong result when getting person's location after setting it", 
					"New York City, NY", p.getLocation());
		}
		p.setName("");
		p.setAge(0);
		p.setLocation("");
		Person p2 = new Person ( );
		for (int k=0; k<2; k++) {
			assertEquals ("wrong toString result when comparing to default person",
					p.toString(), p2.toString());
		}
	}
}
