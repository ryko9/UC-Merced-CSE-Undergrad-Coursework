
# include "my_viewer.h"
# include "sn_mynode.h"

# include <sigogl/gl_tools.h>
# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

bool isRotate = false;  //when set to true, moves hands

float sec = 0.0f; //for updating seconds on small hand
float min = 0.0f; //updating minutes on big hand

float pi = (float) GS_PI; //helper variable for value of pi

float rSec = (float) pi / 30; //in order to move by 6 degrees, divide pi by 30 to get value of 6 degrees in radians
float rMin = (float)pi / 1800; // pi / 1800 = 180/1800 = 1/10

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	add_ui ();
	add_mynode(1);
	_nbut = 0;
	_animating = false; //bool for animation
	build_ui();
	build_scene();
	
	/*c = new SnMyNode; //initializing SnMyNode with the constructor of myViewer, with its own member functions R, r, n
	
	c->color ( GsColor::random() ); //giving random color to 3d object

	//add_mynode (1);

	rootg()->add(c); */

}

void MyViewer::add_ui ()
{
	UiPanel *p;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "Add", EvAdd ) );
	p->add ( new UiButton ( "Info", EvInfo ) );
	p->add ( new UiButton ( "Exit", EvExit ) );
}

void MyViewer::add_mynode ( int n )
{
	SnMyNode* c;

	float r=0.15f; // position range
	while ( n-->0 )
	{	c = new SnMyNode;
		c->init.set ( gs_random(-r,r), gs_random(-r,r), gs_random(-r,r) );
		c->width = gs_random(0.001f,r);
		c->height = gs_random(0.001f,r*2);
		c->color ( GsColor::darkblue );
		// Example how to print/debug your generated data:
		// gsout<<n<<": "<<c->color()<<gsnl;
		rootg()->add(c);
	}
}

//TRANSFERRED FROM SIGAPP. Used Torus as the base for the clock, therefore I had to take build_Ui, add_model, and other functions from sigapp to sigmynode

void MyViewer::build_ui()
{
	UiPanel* p, * sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel("", UiPanel::HorizLeft);
	p->add(new UiButton("View", sp = new UiPanel()));
	{	UiPanel* p = sp;
	p->add(_nbut = new UiCheckButton("Normals", EvNormals));
	}
	p->add(new UiButton("Animate", EvAnimate));
	p->add(new UiButton("Exit", EvExit)); p->top()->separate();
}

void MyViewer::add_model(SnShape* s, GsVec p)
{
	// This method demonstrates how to add some elements to our scene graph: lines,
	// and a shape, and all in a group under a SnManipulator.
	// Therefore we are also demonstrating the use of a manipulator to allow the user to
	// change the position of the object with the mouse. If you do not need mouse interaction,
	// you can just use a SnTransform to apply a transformation instead of a SnManipulator.
	// You would then add the transform as 1st element of the group, and set g->separator(true).
	// Your scene graph should always be carefully designed according to your application needs.

	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation(p);
	manip->initial_mat(m);

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);
	// manip->visible(false); // call this to turn off mouse interaction

	rootg()->add(manip);
}

void MyViewer::build_scene()
{
	SnPrimitive* p;

	p = new SnPrimitive(GsPrimitive::Box, 1, 3, 1);
	p->prim().material.diffuse = GsColor::yellow;
	//add_model(p, GsVec(0, 0, 0));

	p = new SnPrimitive(GsPrimitive::Sphere, 2);
	p->prim().material.diffuse = GsColor::red;
	//add_model(p, GsVec(-4, 0, 0));

	p = new SnPrimitive(GsPrimitive::Cylinder, 1.0, 1.0, 1.5);
	p->prim().material.diffuse = GsColor::blue;
	//add_model(p, GsVec(4, 0, 0));

	p = new SnPrimitive(GsPrimitive::Capsule, 1, 1, 3);
	p->prim().material.diffuse = GsColor::red;
	//add_model(p, GsVec(8, 0, 0));

	p = new SnPrimitive(GsPrimitive::Ellipsoid, 2.0, 0.5);
	p->prim().material.diffuse = GsColor::green;
	//add_model(p, GsVec(-8, 0, 0));

	p = new SnPrimitive(GsPrimitive::Cylinder, .005F, .012F, .4F); //second hand
	p->prim().material.diffuse = GsColor::red;
	add_model(p, GsVec(0, 0, 0)); //add model for second hand at origin

	p = new SnPrimitive(GsPrimitive::Cylinder, .005F, .012F, .5F); //first hand
	p->prim().material.diffuse = GsColor::black;
	add_model(p, GsVec(0, 0, 0)); //add model at origin


}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation()
{
	if (_animating) return; // avoid recursive calls
	_animating = true;

	int ind = gs_random(0, rootg()->size() - 1); // pick one child
	SnManipulator* manip1 = rootg()->get<SnManipulator>(1); // access one of the manipulators
	GsMat a = manip1->mat();
	SnManipulator* manip2 = rootg()->get<SnManipulator>(2); //second SnManipulator to handle second hand
	GsMat b = manip2->mat();

	double frdt = 1.0 / 60.0; // delta time to reach given number of frames per second
	//double v = 4; // target velocity is 1 unit per second
	double t = 0, lt = 0, t0 = gs_time();
	do // run while isRotate = true
	{
		sec += rSec; //increment seconds value by 6 degrees
		min += rMin; //increment minutes value by 1/10th degree

		while (t - lt < frdt) 
		{
			ws_check(); 
			t = gs_time() - t0;
		}

		lt = t;

		a.rotz(-sec);
		b.rotz(-min);

		manip1->initial_mat(a);
		manip2->initial_mat(b);
		render();
		ws_check();
	} while (isRotate); //only runs loop while isRotate = true
	_animating = false;

}

void MyViewer::show_normals(bool view)
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	int k = 0;
	while(k != r->size())
	{
		SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if (!view) { l->visible(false); continue; }
		l->visible(true);
		if (!l->empty()) continue; // build only once
		l->init();
		if (s->instance_name() == SnPrimitive::class_name)
		{
			GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face(fn);
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for (int i = 0; i < m.F.size(); i++)
			{
				const GsVec& a = m.V[m.F[i].a]; l->push(a, a + (*n++) * f);
				const GsVec& b = m.V[m.F[i].b]; l->push(b, b + (*n++) * f);
				const GsVec& c = m.V[m.F[i].c]; l->push(c, c + (*n++) * f);
			}
		}
		k++;
	}
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		case GsEvent::KeyLeft: gsout<<"Left\n"; return 1;
		// etc

		//case 'q': gsout << "Hello world" << gsnl;

		//Keyboard commands implemented here

		case 'q': //implementing q to increase resolution
			c->n++;  // increase resolution value by 1
			break;

		case 'a':  //implementing a to decrease resolution
			c->n--; // decrement resolution value by 1
			break;

		case 'w': //implementing w to increase outer radius
			c->r += (c->r * 0.1f); //increasing outer radius by 10%
			break;

		case 's': //implementing w to decrease outer radius
			c->r -= (c->r * 0.1f); //decreasing radius by 10%
			break;

		case 'e': //implementing e to increase inner radius 
			c->R += (c->R * 0.1f);  //increase R value by 10%
			break;

		case 'd': //implementing d to decrease inner radius
			c->R -= (c->R * 0.1f); //decrease R value by 10%
			break;
		
		case ' ': isRotate = !(isRotate); //when space is pressed, set rotate to true, starting animation. !  negates whatever state rotation is, allowing for stopping then restarting with space
			run_animation();
			return 1;

		case GsEvent::KeyEnter: 
			min = 0.0f; //set minutes and seconds back to 0 to bring to original position when enter is pressed
			sec = 0.0f;
			isRotate = false; //stops rotation
			return 1;
	
		//default: gsout<<"Key pressed: "<<e.key<<gsnl;
	}

	c->touch(); //calling touch and redraw to redraw after changes to R, r, or n values
	redraw();
	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvAdd: add_mynode(1); return 1;

		case EvInfo:
		{	if ( output().len()>0 ) { output(""); return 1; }
			output_pos(0,30);
			activate_ogl_context(); // we need an active context
			GsOutput o; o.init(output()); gl_print_info(&o); // print info to viewer
			return 1;
		}

		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
