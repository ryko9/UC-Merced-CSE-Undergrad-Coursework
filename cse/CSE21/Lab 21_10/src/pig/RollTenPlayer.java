package pig;

public class RollTenPlayer extends Player{
//player that only rolls up to 10 times, then holds
	public boolean throwAgain(Player opponent)
	{
		
		boolean i = false;
		
		if(super.rollCount() <= 10)
		{
			i = true;
		}
		
		return i;
	}
}
