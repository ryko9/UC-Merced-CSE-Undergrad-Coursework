
public class Preference {

	private int quietTime;
	private int music;
	private int reading;
	private int chatting;
	
	public Preference(int quietTime, int music, int reading, int chatting)
	{
		//checking to see if values are in between 0 and 10
	    if(quietTime >= 0 && quietTime <= 10 && music >= 0 && music <= 10 && reading >= 0 && reading <= 10 && chatting >= 0 && chatting <= 10)
		{
			this.quietTime = quietTime;
			this.music = music;
			this.reading = reading;
			this.chatting = chatting;
		}
	}
	
	public int getQuiet()
	{
		return quietTime;
	}
	
	public int getMusic()
	{
		return music;
	}
	
	public int getReading()
	{
		return reading;
	}
	
	public int getChatting()
	{
		return chatting;
	}

	public int compare(Preference pref) //Parameter of Preference object pref
	{
		int sum = Math.abs(pref.getMusic() - this.music) + Math.abs(pref.getChatting() - this.chatting)
		+ Math.abs(pref.getQuiet() - this.quietTime) + Math.abs(pref.getReading() - this.reading);
			
		return sum;
	}
}
