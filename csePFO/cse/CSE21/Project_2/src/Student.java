
public class Student {
	private String name; //instance variables
	private char gender;
	private Date birthDay;
	private Preference pref;
	Boolean matched = false;
	
	public Student(String name, char gender, Date birthDay, Preference pref)
	{
		this.name = name;
		this.gender = gender;
		this.birthDay = birthDay;
		this.pref = pref;
	}
	
	public Student()
	{
		
	}
	public String getName()
	{
		return name;
	}
	
	public char getGender()
	{
		return gender;
	}
	
	public Date getBirth()
	{
		return birthDay;
	}
	
	public Preference getPref()
	{
		return pref;
	}
	
	public Boolean getMatched()
	{
		return matched;
	}
	
	public void setMatched(boolean matched)
	{
		this.matched = matched;
	}
	
	public int compare(Student st) //parameter is Student object st
	{
		int Preferences = this.pref.compare(st.getPref()); 	//compares current instance of pref to st's instance of pref
		int AgeDifference = this.birthDay.compare(st.getBirth()); //compares current instance of birthDay to st's instance of birthDay	
		int result = (40 - Preferences) + (60 - AgeDifference);
		if(this.gender != st.getGender()) //if genders different, return 0
		{
			result = 0;
		}
		return result;
	}
	
}
