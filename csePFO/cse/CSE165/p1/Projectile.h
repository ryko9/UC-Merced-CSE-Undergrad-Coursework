#ifndef Projectile_h
#define Projectile_h

#include "TexRect.h"
#include "Player.h"

using namespace std;

class Projectile
{
	bool up;
	bool down;
	bool ismove;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float rate;
	TexRect* projectile;

public:
	Projectile(const char* filename, float x, float y, float twidth, float theight, float speed, bool up, bool ismove)
	{
		projectile = new TexRect(filename, x, y, twidth, theight);
		this->up = up;
		down = !up;
		cornerX = x;
		cornerY = y;
		width = twidth;
		height = height;
		this->ismove = ismove;
		rate = speed;
	}

	void setDirection(bool input)
	{
		if(input)
		{
            down = false;
            up = true;
		}
		else
		{
            down = true;
            up = false;
		}
	}

	bool shotplayer(Player* player)
	{
		float x1 = player->getcornerX();
		float x2 = x1 + player->getwidth();
		float y1 = player->getcornerY() - 0.5;
		float y2 = y1 + player->getheight();
		if(projectile->contains(x1,y1) || projectile->contains(x1,y2) || projectile->contains(x2,y2) || projectile->contains(x2,y1))
		{
			return true;
		}
	}

	void setnotmoving()
	{
		ismove = false;
		cornerY = 2;
	}

	void setSpeed(float speed)
	{
		rate = speed;
	}

	float getcornerX()
	{
		return cornerX;
	}

	float getcornerY()
	{
		return cornerY;
	}

	float getwidth()
	{
		return width;
	}

	float getheight()
	{
		return height;
	}

	void draw()
	{
		if(ismove)
		{
			if(up)
			{
				projectile->draw();
				cornerY = cornerY + rate;
				projectile->moveUp(rate);
			}
			else if(down)
			{
				projectile->draw();
				cornerY = cornerY - rate;
				projectile->moveDown(rate);
			}
		}
	}

};

#endif
