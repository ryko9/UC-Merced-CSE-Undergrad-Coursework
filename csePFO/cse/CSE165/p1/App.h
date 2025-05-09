#ifndef App_hpp
#define App_hpp

#include "GlutApp.h"
#include "TexRect.h"
#include "AnimatedRect.h"
#include "multiEnemy.h"
#include "Player.h"
#include "MultiProjectile.h"

#include "Screen.h"
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class App: public GlutApp
{
	// Maintains app state
	float mx;
	float my;

public:
	// Constructors
	App(const char* label, int x, int y, int w, int h);

	void draw();
	void keyPress(unsigned char key);
	void keyUp(unsigned char key);
	void mouseDown(float x, float y);
	void mouseDrag(float x, float y);

	void idle();

	multiEnemy* enemies;
	Player* thePlayer;
	MultiProjectile* p1_projectiles;
	MultiProjectile* enemy_projectiles;
	Screen* screens;
	TexRect* background;

	TexRect* mainmenu;
	TexRect* pausemenu;
	TexRect* gamever;
	TexRect* gameoverscr;

	AnimatedRect* gameOver;

	int playercount;
	bool game_start;
};

#endif
