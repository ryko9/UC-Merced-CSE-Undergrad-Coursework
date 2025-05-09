/*David Wang CSE 165 lab 5*/

#include <iostream>
#include "App.h"
#include "TexRect.h"
#include "AnimatedRect.h"

App* singleton;

void timer(int id){
    // This will get called every 16 milliseconds after
    // you call it once
    
    // If you want to manipulate the app in here
    // do it through the singleton pointer
    glutTimerFunc(16, timer, id);
}


App::App(int argc, char** argv, int width, int height, const char* title): GlutApp(argc, argv, width, height, title){

    background = new TexRect("/Users/dawang3/Documents/CSE165/lab5/bg.png", -2, 1, 4, 2);
    background1 = new TexRect("/Users/dawang3/Documents/CSE165/lab5/bg.png", 2, 1, 4, 2);
    cat = new AnimatedRect("/Users/dawang3/Documents/CSE165/lab5/cat.png", 4, 2, 80, true, true, -.04, -.25, 0.8, 0.5);

    point = background -> getX(), next = point, diff = point; //keeping track of current
    timer(1);
    
}

void App::draw() {
    
    background -> draw(0);
    background1 -> draw(0);
    cat -> draw(1);
    
    float num = 0;
    
   if(num == 0)
   {
    
       num = .13;
       next -= num;
       diff += num;
       background ->setX(next);
       background1 -> setX(0 - diff);
   }

    if(diff > 2)
    {
        background -> setX(-2);
        background1 -> setX(0);
        diff = -2;
        next = -2;
    }
}

void App::keyDown(unsigned char key, float x, float y){
    if (key == 'q'){ //press q to quit
        exit(0);
    }
}

App::~App(){
    std::cout << "Exiting..." << std::endl;
}
