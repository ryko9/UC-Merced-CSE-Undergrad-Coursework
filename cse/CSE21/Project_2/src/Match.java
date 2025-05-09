import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.*;

public class Match {
	

public static void main(String[] args){
		
		int numStudents = 0; //counting total number of students
		int currentScore; //for comparing scores
		Student[] students = new Student[100]; //array to store students
		
		Scanner input = new Scanner(System.in); //scanner to get filename
		
		System.out.println("Enter 'data/Students.txt' or 'data/FullRoster.txt'.");
		System.out.print("Enter file name: ");
		String filename = input.next();
		
		try {
			input = new Scanner(new FileReader(filename));
			while (input.hasNextLine()) {
				input.useDelimiter("[\t\r,-]");
				
				String name = input.next();
				char gender = input.next().charAt(0);
				Date birth = new Date(input.nextInt(), input.nextInt(), input.nextInt());
				Preference  pref = new Preference(input.nextInt(), input.nextInt(), input.nextInt(), input.nextInt());
				
				students[numStudents]= new Student(name, gender, birth, pref);
				numStudents++;
			} 
			input.close();
		} catch ( NoSuchElementException e){
			System.out.println(e);

		} catch (FileNotFoundException e) {
			System.out.println(e);
		}
		
		System.out.println(); //spacing for clarity
		
		for(int i = 0; i < numStudents; i++)
		{
			Student bestMatchStudent = new Student(); //bestMatchStudent, empty Student to store the bestMatchStudent later on
			int maxScore = 0; //best possible score
			if(!students[i].getMatched())
			{ //for students that arent already matched
				for(int j = numStudents - 1; j >= 0; j--)
				{
					if(!students[j].getMatched() && students[j]!= students[i])	//for rest of students that arent already matched
					{
						currentScore = students[i].compare(students[j]);  
						if(currentScore > maxScore)
						{ 
//if currentScore is greater than maxScore, maxScore is assigned the value of currentScore. That way, maxScore will only change throughout the loop if it finds a score better than it. 
							bestMatchStudent = students[j];  //bestMatchStudent is assigned the student that had the highest score.
							maxScore = currentScore; //maxScore stores the highest scores found.
						}
					}
				}
			students[i].setMatched(true);
			bestMatchStudent.setMatched(true);
			
				if(maxScore == 0)
				{
					System.out.println(students[i].getName().trim() + " has no matches"); //using getName().trim() since there is a space in between names
				}
				else 
					System.out.println(students[i].getName().trim() + " matches with " + bestMatchStudent.getName().trim() + " with the score " + maxScore);
			}
	   }
   }
}
