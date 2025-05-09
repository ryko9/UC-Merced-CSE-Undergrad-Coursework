#include <iostream>
#include "App.h"

App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer
    
    if (singleton->up){
        float ypos = singleton->projectile->getY();
        ypos +=0.05;
        singleton->projectile->setY(ypos);
        singleton->redraw();
        
        if(singleton->mushroom->contains(0, ypos - 0.06)) {
            singleton->up = false;
            singleton->explode = true;
            singleton->fire->playOnce();
            
        }
    }
    
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){
    
    mushroom = new TexRect("/Users/dawang3/Documents/CSE165/lab6/mushroom.png", -0.25, 0.9, 0.5, 0.5);
    projectile = new Rect(-0.05, -0.8, 0.1, 0.1);
    fire = new AnimatedRect("/Users/dawang3/Documents/CSE165/lab6/fireball.bmp", 6, 6, 60, true, true, -0.25, 0.9, 0.5, 0.5);
    up = false;
    explode = false;
    
    singleton = this;
    
    timer(1);
}

void App::draw() {
    mushroom->draw(0.1);
    projectile->draw();
    
    //storing coordinates to compare
    if(explode)
    {
        fire->draw(1);
    }
}
void App::keyDown(unsigned char key, float x, float y){
    if (key == 27){
        exit(0);
    }
    if (key == ' '){
        up = true;
    }
}

App::~App(){
    delete mushroom;
    std::cout << "Exiting..." << std::endl;
}
