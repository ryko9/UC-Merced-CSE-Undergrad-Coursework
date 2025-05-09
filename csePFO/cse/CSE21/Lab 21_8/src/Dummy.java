
public class Dummy {
	public Dummy() {
		System.out.println("(1) No arguments constructor");
	}
	public Dummy(int param1) {
		System.out.println("(2) Int argument constructor");
	}

	public Dummy(double param1) {
		System.out.println("(3) Double argument constructor");
	}

	public Dummy(int[] param1) {
		System.out.println("(4) Int[] argument constructor");
	}

	public Dummy(double[] param1) {
		System.out.println("(5) Double[] argument constructor");
	}

	public Dummy(Dummy param1) {
		System.out.println("(6) Dummy argument constructor");
	}

	public Dummy(Dummy[] param1) {
		System.out.println("(7) Dummy[] argument constructor");
	}

	public Dummy(int param1, double param2) {
		System.out.println("(8) Int, Double arguments constructor");
	}

	public Dummy(int[] param1, double[] param2) {
		System.out.println("(9) Int[], Double[] arguments constructor");
	}

	public Dummy(int param1, double param2, Dummy param3) {
		System.out.println("(10) Int, Double, Dummy arguments constructor");
	}

	public Dummy(int[] param1, double[] param2, Dummy[] param3) {
		System.out.println("(11) Int[], Double[], Dummy[] arguments constructor");
	}
	
	public void display() {
		System.out.println("(1) Display");
	}
	public void display(int param1) {
		System.out.println("(2) Display");
	}

	public void display(double param1) {
		System.out.println("(3) Display");
	}

	public void display(int[] param1) {
		System.out.println("(4) Display");
	}

	public void display(double[] param1) {
		System.out.println("(5) Display");
	}

	public void display(Dummy param1) {
		System.out.println("(6) Display");
	}

	public void display(Dummy[] param1) {
		System.out.println("(7) Display");
	}

	public void display(int param1, double param2) {
		System.out.println("(8) Display");
	}

	public void display(int[] param1, double[] param2) {
		System.out.println("(9) Display");
	}

	public void display(int param1, double param2, Dummy param3) {
		System.out.println("(10) Display");
	}

	public void display(int[] param1, double[] param2, Dummy[] param3) {
		System.out.println("(11) Display");
	}
}

