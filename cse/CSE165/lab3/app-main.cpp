/* David Wang CSE 165, Lab 3*/

#include <iostream>
#include <cmath>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#define RED 1
#define GREEN 2
#define CYAN 3
#define PURPLE 4
#define ERASER 5

static int height = 600;
static int width = 600;
static int brushSize = 7;

GLfloat red = 1.0;
GLfloat green = 0;
GLfloat blue = 1.0;

void display(void){

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void clearDisplay(void){
    
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void createDisplay(){
    
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
    clearDisplay();
}

void cursor(int mx, int my){

    glColor3f(red, green, blue);
    GLint x = mx;
    GLint y = height - my;
    glRecti(x, y, x + brushSize, y + brushSize);
    glRecti(x, y, x + brushSize, y + brushSize);
    glFlush();
}

void commands(unsigned char key, int xm, int ym){

	switch(key)
	{
        case 'q':
            exit(0);
            break;

		case '1':
            glClear(GL_COLOR_BUFFER_BIT);
            glFlush();
			break;
            
        default:
            break;
	}
    
    glutPostRedisplay();
}

void menuItems(int option){
	switch(option){
		case RED: red = 1.0; green = 0.0; blue = 0.0; break;
		case GREEN: red = 0.0; green = 1.0; blue = 0.0; break;
        case PURPLE: red = 1.0; green = 0.0; blue = 1.0; break;
		case CYAN: red = 0.0; green = 1.0; blue = 1.0; break;
		case ERASER: red = 1; green = 1; blue = 1; break;
	}
}

void menuCreate(void){
    
    int scolor;
    
    scolor = glutCreateMenu(menuItems);
    glutAddMenuEntry("RED", 1);
    glutAddMenuEntry("GREEN", 2);
    glutAddMenuEntry("CYAN", 3);
    glutAddMenuEntry("PURPLE", 4);
    glutAddMenuEntry("ERASER", 5);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    }

int main(int argc, char** argv){
    
    glutInit(&argc, argv);
    
    glutInitWindowSize(width, height);
    glutCreateWindow("Lab 3 David Wang");
    glutDisplayFunc(createDisplay);
    glutMotionFunc(cursor);
    glutKeyboardFunc(commands);
    
    menuCreate();
    
    glutMainLoop();
}
