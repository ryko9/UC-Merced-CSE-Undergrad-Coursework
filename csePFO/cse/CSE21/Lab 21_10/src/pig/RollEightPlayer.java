package pig;

public class RollEightPlayer extends Player{
//only rolls up to 8 times, then holds
	public boolean throwAgain(Player Opponent)
	{
		boolean i = false;
		if(super.rollCount() <= 8)
		{
			i = true;
		}
		return i;
	}
}
