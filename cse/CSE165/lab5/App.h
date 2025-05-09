#ifndef App_h
#define App_h

#include "GlutApp.h"
#include "AnimatedRect.h"


class App: public GlutApp {
    
    TexRect *background;
    TexRect *background1;
    AnimatedRect *cat;
   
    float point, next, diff;
    
public:
    
    App(int argc, char** argv, int width, int height, const char* title);
    
    void draw();
    
    void keyDown(unsigned char key, float x, float y);
    
    ~App();
    
    friend void timer(int);
    
};

#endif
