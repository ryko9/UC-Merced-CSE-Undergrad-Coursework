#ifndef multiEnemy_h
#define multiEnemy_h

#include "Enemy.h"
#include "Projectile.h"
#include <vector>
#include <iostream>

using namespace std;

class multiEnemy
{
	vector<Enemy*> enemies;
	Enemy* troop;
	bool right;
	bool left;
	bool down;
	float top_left_X;
	float top_right_X;
	float top_Y;
	int rows;
	int cols;
	int numEnemies;
	int numAlive;
	int shotcount;

public:
	multiEnemy(const char* filename1, const char* filename2, int anirows, int anicols, float x, float y, float w, float h, int rows, int cols)
	{
		troop = new Enemy(filename1,filename2,anirows,anicols,x,y,w,h);
		top_left_X = x;
		top_right_X = top_left_X + cols * w;
		top_Y = y;
		this->rows = rows;
		this->cols = cols;
		numEnemies = rows * cols;
		numAlive = rows * cols;
		right = true;
		down = false;
		int j = 1;
		Enemy* temp;
		float setX = x;
		float setY = y;
		int tot = 3;
        
        int i = 1;
        while(i != numEnemies + 1)
		{
			temp = new Enemy(filename1,filename2,anirows,anicols,setX,setY,w,h);
			if(i % cols == 0)
			{
				setX = x;
				setY -= h;
			}
			else
			{
				setX += w + 0.01;
			}
			enemies.push_back(temp);
            i++;
		}
	}

	~multiEnemy()
	{
        int i = 0;
        while(i != numEnemies)
        {
			delete[] enemies[i];
            i++;
		}
	}

	bool containsprojectile(Projectile* projectile)
	{
		float x1 = projectile->getcornerX();
		float x2 = projectile->getcornerX() + projectile->getwidth();
		float y1 = projectile->getcornerY() - 0.05;
		float y2 = projectile->getcornerY() - projectile->getheight();
        
        int i = 0;
        int size = enemies.size();
        
        while( i != size)
        {
			if(enemies.at(i)->contains(x1,y1) || enemies.at(i)->contains(x2,y2))
			{
				enemies.at(i)->isDead();
				numAlive--;
				return true;
			}
            i++;
		}
		return false;
	}

	Enemy* getenemy(int a)
	{
		return enemies.at(a);
	}

	int getnum()
	{
		return numEnemies;
	}

	int getalive()
	{
		return numAlive;
	}

	void draw()
	{
        int i = 0;
        
		while (i != numEnemies)
		{
			enemies.at(i)->draw();
            i++;
		}
		if(top_Y - (troop->getHeight()/2) >= enemies.at(0)->getY())
		{
			top_Y -= (troop->getHeight()/2);
			down = false;
			if(enemies.at(0)->getX() <= -0.99)
			{
				right = true;
				left = false;
			}
			else
			{
				right = false;
				left = true;
			}
		}
		else if(enemies.at(cols-1)->getX() + troop->getWidth() >= 0.99)
		{
			right = false;
			left = false;
			down = true;
		}
		else if(enemies.at(0)->getX() <= -0.99)
		{
			right = false;
			left = false;
			down = true;
		}
        
        int y = 0;
        while(y != numEnemies)
		{
			enemies.at(y)->setMove(left,right,down);
            y++;
					}
		top_left_X = enemies.at(0)->getX();
	}

};

#endif
