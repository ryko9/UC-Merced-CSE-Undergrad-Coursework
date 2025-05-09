#ifndef Player_h
#define Player_h

#include "TexRect.h"
#include "AnimatedRect.h"

#include <deque>

class Player
{
	bool isAlive;
	bool isLeft;
	bool isRight;
	int rows;
	int cols;
	int projectile_count;
	float cornerX;
	float cornerY;
	float width;
	float height;
	float rate;
	float boost;
	TexRect *player;

public:
	Player(const char* filename1, const char* filename2, int rows, int cols, float x, float y, float w, float h)
	{
		player = new TexRect(filename1, x, y, w, h);
		this->rows = rows;
		this->cols = cols;
		projectile_count = 0;
		isLeft = false;
		isRight = false;
		cornerX = x;
		cornerY = y;
		width = w;
		height = h;
		isAlive = true;
		rate = 0.02;
		boost = 0.0;
	}

	int getcount()
	{
		return projectile_count;
	}

	float getboost()
	{
		return boost;
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


	void keydown(int key)
	{
		if(key == 100)
		{
			isLeft = true;
		}
		else if(key == 102)
		{
			isRight = true;
		}
	}

	void keyup(int key)
	{
		if(key == 100)
		{
			isLeft = false;
		}
		else if(key == 102)
		{
			isRight = false;
		}
	}

	void keydownchar(unsigned char key)
	{
        if(key == 'd')
        {
            isRight = true;
        }
		else if(key == 'a')
		{
			isLeft = true;
		}
	}

	void keyupchar(unsigned char key)
	{
        if(key == 'd')
        {
            isRight = false;
        }
		else if(key == 'a')
		{
			isLeft = false;
		}
	}

	void draw()
	{
		if(isAlive)
		{
			if(isLeft == true && cornerX >= -0.99)
			{
				cornerX -= rate;
				player->moveLeft(rate);
			}
            else if(isRight && cornerX + width <= 0.99)
            {
                cornerX += rate;
                player->moveRight(rate);
            }
			player->draw();
		}
	}

	bool shot(bool input)
	{
		if(input != false)
		{
			cornerX = 2;
			player->moveLeft(2);
			isAlive = false;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	~Player()
	{

	}
};

#endif
