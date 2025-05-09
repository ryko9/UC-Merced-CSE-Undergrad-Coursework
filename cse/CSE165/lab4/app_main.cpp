/*David Wang*/

#include <iostream>
#include <vector>
#include <cmath>

#if defined WIN32
#include <freeglut.h>
#elif defined __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif


using namespace std;

// Store the width and height of the window
int width = 640, height = 640;

class Shape{
public:
    virtual void draw() const {
        cout << "Drawing generic shape" << endl;
    }
};

class Rect: public Shape {
    float x;
    float y;
    float w;
    float h;
public:
    Rect (): x(0), y(0), w(0.5), h(0.5){}
    
    Rect (float x, float y, float w, float h) : x(x), y(y), w(w), h(h) {}
    
    void draw() const {
        glBegin(GL_LINES);
        
        glVertex2f(x, y);
        glVertex2f(x + w, y);
        
        glVertex2f(x + w, y);
        glVertex2f(x + w, y - h);
        
        glVertex2f(x + w, y - h);
        glVertex2f(x, y - h);
        
        glVertex2f(x, y - h);
        glVertex2f(x, y);
        
        glEnd();
    }
};

class Circle: public Shape {
    float x;
    float y;
    float r;
    
public:
    Circle(): x(0), y(0), r(0.2){}
    Circle(float x, float y, float r): x(x), y(y), r(r) {}
    
    void draw() const {
        glBegin(GL_LINES);
        
        float inc = 0.1;
        
        for(float theta = 0; theta < 2*M_PI; theta += inc){
            glVertex2f(r*cos(theta)+x, r*sin(theta) + y);
            glVertex2f(r*cos(theta+inc)+x, r*sin(theta+inc) + y);
        }
        
        glEnd();
    }
    
};


class Point: public Shape {
    float x;
    float y;
public:
    Point() : Shape(), x(-0.5), y(0.5){}
    
    void draw() const {
        glBegin(GL_POINTS);
        
        glVertex2f(x, y);
        
        glEnd();
    }
};


class TextBox : public Shape {
    string displayText;
    float x;
    float y;
    void* textFont;
    float red = 1;
    float green = 0;
    float blue = 0;

public:
    TextBox(string displayText, float x, float y, void* textFont = GLUT_BITMAP_HELVETICA_18) :
    displayText(displayText), x(x), y(y), textFont(textFont){
        this->draw();
    }
    
    void draw() const {
        glColor3f(red, green, blue);
        float offset = 0;
        for (int i = 0; i < displayText.length(); i++) {
            glRasterPos2f(x+offset, y);
            glutBitmapCharacter(textFont, displayText[i]);
            int w = glutBitmapWidth(textFont, displayText[i]);
            offset += ((float)w / width)*2;
    }
    }
};


vector<Shape*> shapes;


void renderText(string text, float x, float y, void* font = GLUT_BITMAP_HELVETICA_18, float r = 1, float g = 1, float b = 1){
    glColor3f(r, g, b);
    float offset = 0;
    for (int i = 0; i < text.length(); i++) {
        glRasterPos2f(x+offset, y);
        glutBitmapCharacter(font, text[i]);
        int w = glutBitmapWidth(font, text[i]);
        offset += ((float)w / width)*2;
    }
}

//-------------------------------------------------------
// A function to draw the scene
//-------------------------------------------------------
void appDrawScene() {
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Set background color to black
	glClearColor(0.0, 0.0, 0.0, 1.0);

	// Set up the transformations stack
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    // Draw stuff here
//    rect->draw();
//    circ->draw();
    
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i]->draw();
    }
    
    
    // This is only for testing purposes
    renderText("This is a test", -0.8, 0, GLUT_BITMAP_TIMES_ROMAN_24);

	// We have been drawing everything to the back buffer
	// Swap the buffers to see the result of what we drew
	glFlush();
	glutSwapBuffers();
}

//-------------------------------------------------------
// A function to convert window coordinates to scene
// We use it when a mouse event is handled
// Arguments: 	
//	x, y - the coordinates to be updated
//-------------------------------------------------------
void windowToScene(float& x, float& y) {
	x = (2.0f*(x / float(width))) - 1.0f;
	y = 1.0f - (2.0f*(y / float(height)));
}

//-------------------------------------------------------
// A function to handle window resizing
// Called every time the window is resized
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appReshapeFunc(int w, int h) {
	// Window size has changed
	width = w;
	height = h;

	double scale, center;
	double winXmin, winXmax, winYmin, winYmax;

	// Define x-axis and y-axis range
	const double appXmin = -1.0;
	const double appXmax = 1.0;
	const double appYmin = -1.0;
	const double appYmax = 1.0;

	// Define that OpenGL should use the whole window for rendering
	glViewport(0, 0, w, h);

	// Set up the projection matrix using a orthographic projection that will
	// maintain the aspect ratio of the scene no matter the aspect ratio of
	// the window, and also set the min/max coordinates to be the disered ones
	w = (w == 0) ? 1 : w;
	h = (h == 0) ? 1 : h;

	if ((appXmax - appXmin) / w < (appYmax - appYmin) / h) {
		scale = ((appYmax - appYmin) / h) / ((appXmax - appXmin) / w);
		center = (appXmax + appXmin) / 2;
		winXmin = center - (center - appXmin)*scale;
		winXmax = center + (appXmax - center)*scale;
		winYmin = appYmin;
		winYmax = appYmax;
	}
	else {
		scale = ((appXmax - appXmin) / w) / ((appYmax - appYmin) / h);
		center = (appYmax + appYmin) / 2;
		winYmin = center - (center - appYmin)*scale;
		winYmax = center + (appYmax - center)*scale;
		winXmin = appXmin;
		winXmax = appXmax;
	}

	// Now we use glOrtho to set up our viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(winXmin, winXmax, winYmin, winYmax, -1, 1);
}


//-------------------------------------------------------
// A function to handle mouse clicks
// Called every time the mouse button goes up or down
// Arguments: 	
//	b    - mouse button that was clicked, left or right
//	s 	 - state, either mouse-up or mouse-down
//	x, y - coordinates of the mouse when click occured
//-------------------------------------------------------
void appMouseFunc(int b, int s, int x, int y) {
	// Convert from Window to Scene coordinates
	float mx = (float)x;
	float my = (float)y;

	windowToScene(mx, my);
    

	// Redraw the scene by calling appDrawScene above
	// so that the point we added above will get painted
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle mouse dragging
// Called every time mouse moves while button held down
// Arguments: 	
//	x, y - current coordinates of the mouse
//-------------------------------------------------------
void appMotionFunc(int x, int y) {

	// Again, we redraw the scene
	glutPostRedisplay();
}

//-------------------------------------------------------
// A function to handle keyboard events
// Called every time a key is pressed on the keyboard
// Arguments: 	
//	key  - the key that was pressed
//	x, y - coordinates of the mouse when key is pressed
//-------------------------------------------------------
void appKeyboardFunc(unsigned char key, int x, int y) {
	
    if (key == 27){
        for (int i = 0; i < shapes.size(); i++) {
            delete shapes[i];
        }
        exit(0);
    }

	// After all the state changes, redraw the scene
	glutPostRedisplay();
}


void idle(){

}


int main(int argc, char** argv) {
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);

	// Setup window position, size, and title
	glutInitWindowPosition(20, 60);
	glutInitWindowSize(width, height);
	glutCreateWindow("CSE165 OpenGL Demo");

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
    
    glPointSize(5);

    shapes.push_back(new Rect());
    shapes.push_back(new Circle());
    shapes.push_back(new Point());
    shapes.push_back(new Circle(0.5, 0.5, 0.5));
    
    // Everything should be working when we uncomment next line
    shapes.push_back(new TextBox("Hello World", -0.8, 0.5));
    //shapes.push_back(new TextBox("Hello World", -0.8, 0.5, "GLUT_BITMAP_HELVETICA_18", 0,1,0));
    

	// Set callback for drawing the scene
	glutDisplayFunc(appDrawScene);

	// Set callback for resizing th window
	glutReshapeFunc(appReshapeFunc);

	// Set callback to handle mouse clicks
	glutMouseFunc(appMouseFunc);
    
    
    glutIdleFunc(idle);

	// Set callback to handle mouse dragging
	glutMotionFunc(appMotionFunc);

	// Set callback to handle keyboad events
	glutKeyboardFunc(appKeyboardFunc);

	// Start the main loop
	glutMainLoop();
}
