
public class Date {
	private int year;
	private int month;
	private int day;
	
	public Date(int month, int day, int year)
	{	
		if(year >= 1900 && year <= 3000 && month >= 1 && month <= 12 && day >=1 && day <= 31) //range for year, month, date
		{
			this.month = month;
			if(this.month == 2) //February always 28 days
			{
				this.day = 28;
			}
			else
			{
				this.day = day;
			}
			this.year = year;
		}
		
	}
	
	public int getYear()
	{
		return this.year;
	}
	
	public int getMonth()
	{
		return month;
	}
	
	public int getDay()
	{
		return day;
	}
	
	public int dayOfYear() //used for compare
	{
		int totalDays = 0;
		switch (this.month) 
		{
			case 12: totalDays += 30;
			case 11: totalDays += 31;
			case 10: totalDays += 30;
			case 9 : totalDays += 31;
			case 8 : totalDays += 31;
			case 7 : totalDays += 30;
			case 6 : totalDays += 31;
			case 5 : totalDays += 30;
			case 4 : totalDays += 31;
			case 3 : totalDays += 28;
			case 2 : totalDays += 31;
		} 
			 totalDays += this.day;
			 return totalDays;
	} 
	
	public int compare(Date dt) //parameter of Date object dt
	{
		
		int days = this.dayOfYear() + (365 * this.getYear()); //days for first object
		int dtDays = dt.dayOfYear() + (365 * dt.getYear()); //days for object dt
		
		int total = Math.abs(days - dtDays)/30; //day differential divided by 30 to get month differential.
		
		if(total > 60)
		{
			total = 60;
		}
		
		return total;
	}
}
