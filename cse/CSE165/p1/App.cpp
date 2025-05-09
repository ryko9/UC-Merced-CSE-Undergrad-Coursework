#include "App.h"

using namespace std;

static App* game;
void app_timer(int value)
{
	srand(time(NULL));
	if(game->screens->getShow() == true)
	{
		if(game->screens->getLose() == true)
		{
	        game->redraw();
	        glutTimerFunc(100, app_timer, value);
		}
		else
		{
			game->redraw();
			glutTimerFunc(16, app_timer, value);
		}
	}
	else if(game->game_start)
	{
//kill enemies
        int x = 0;
        while(x != game->p1_projectiles->getSize())
		{
			if(game->enemies->containsprojectile(game->p1_projectiles->getprojectile(x)))
			{
				game->p1_projectiles->noMove(x);
			}
            x++;
		}


		//enemy count if enemycount = 0, win
        int amountAlive = game->enemies->getalive();
        
		if(amountAlive == 0)
		{
			game->screens->isWin();
		}
        int q = game->enemies->getnum() - 1;
        while(q != -1)
        {
			if(game->enemies->getenemy(q)->getY() <= -0.65 && game->enemies->getenemy(q)->getAlive())
			{
				game->screens->isLose();
			}
            
            q--;
		}

		game->redraw();
		glutTimerFunc(16, app_timer, value);
	}
}

App::App(const char* label, int x, int y, int w, int h): GlutApp(label, x, y, w, h)
{
	// Initialize state variables
    
	game = this;
	mx = 0.0;
	my = 0.0;

	screens = new Screen("/Users/dawang3/Desktop/p1/images/title_screen.png","/Users/dawang3/Desktop/p1/images/pause_screen.png","/Users/dawang3/Desktop/p1/images/game_over.png","/Users/dawang3/Desktop/p1/images/win_screen.png","/Users/dawang3/Desktop/p1/images/endgame.png");
	background = new TexRect("/Users/dawang3/Desktop/p1/images/grass.png", -1, 1, 2, 2); 
	enemies = new multiEnemy("/Users/dawang3/Desktop/p1/images/cat.png","/Users/dawang3/Desktop/p1/images/mushroom.png", 3, 2, -0.9, 0.95, .14, .20, 5, 8);
	thePlayer = new Player("/Users/dawang3/Desktop/p1/images/Dog.png", " ", 3, 2, -0.7, -0.8, .15, .2);
	p1_projectiles = new MultiProjectile("/Users/dawang3/Desktop/p1/images/bone.png", 0.0, 0.0, 0.0477, 0.114);
	game_start = false;
	app_timer(1);
}

void App::draw()
{

	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 1.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(screens->getShow())
	{
		screens->draw();
	}
	else
	{
		background->draw();
		p1_projectiles->draw();
		thePlayer->draw();
		enemies->draw();

	}

	glFlush();
	glutSwapBuffers();
}

void App::mouseDown(float x, float y)
{
	// Update app state
	mx = x;
	my = y;
}

void App::mouseDrag(float x, float y)
{
	// Update app state
	mx = x;
	my = y;
}

void App::idle()
{

}

void App::keyPress(unsigned char key)
{
    if(key == 'p')
    {
        screens->setPause();
        app_timer(1);
    }
	else if (key == 'q')
	{
		if(screens->getShow() == true)
		{
			// Exit the app when Esc key is pressed
			delete thePlayer;
			delete enemies;
			delete background;
			delete this;
			exit(0);
		}
	}
	else if(key == 'w')
	{
		if(p1_projectiles->getSize() <= thePlayer->getcount())
		{
			p1_projectiles->addProjectile(true, thePlayer->getcornerX() + 0.01, thePlayer->getcornerY() - 0.01,  0.02 + thePlayer->getboost());
		}
	}
    else if(key == 32)
    {
        playercount = 1;
        
        game_start = true;
        screens->showFalse();
        app_timer(1);
    }
	else if(key == 'r')
	{
		if(screens->getShow() == true)
		{
			screens->isStart();
			enemies = new multiEnemy("/Users/dawang3/Desktop/p1/images/cat.png","/Users/dawang3/Desktop/p1/images/mushroom.png", 3, 2, -0.9, 0.95, .14, .20, 4, 10);
			thePlayer = new Player("/Users/dawang3/Desktop/p1/images/Dog.png", " ", 3, 2, -0.7, -0.8, .15, .2);
			p1_projectiles = new MultiProjectile("/Users/dawang3/Desktop/p1/images/bone.png", 0.0, 0.0, 0.0477, 0.114);
			game_start = false;

			app_timer(1);
		}
	}
	else
	{
		thePlayer->keydownchar(key);
	}
}

void App::keyUp(unsigned char key)
{
	thePlayer->keyupchar(key);
}

