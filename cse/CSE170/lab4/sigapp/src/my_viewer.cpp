
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>
# include <cmath>

GsModel& torus; //GsModel object for the torus

bool isFlat; //boolean to keep status smooth or not smooth

float pi = (float)GS_PI;
float rad = pi / 180; //helper variable to convert from degrees to radians

//Member variables

float R = 0.1f;
float r = 0.025f;// R = inner radius, R = outer radius, N = number of faces / resolution 
float n = 40;

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;
	build_ui ();
	build_scene ();
}

void MyViewer::build_ui ()
{
	UiPanel *p, *sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel ( "", UiPanel::HorizLeft );
	p->add ( new UiButton ( "View", sp=new UiPanel() ) );
	{	UiPanel* p=sp;
		p->add ( _nbut=new UiCheckButton ( "Normals", EvNormals ) ); 
	}
	p->add ( new UiButton ( "Animate", EvAnimate ) );
	p->add ( new UiButton ( "Exit", EvExit ) ); p->top()->separate();
}

void MyViewer::add_model ( SnShape* s, GsVec p )
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
	m.translation ( p );
	manip->initial_mat ( m );

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

	float theta;
	float phi; 
	float step = (2 * pi) / n;

	//torus = new GsModel; 

	SnModel* s; 

	torus = *s->model(); //access the GsModel

	rootg()->add(s); //add to the scene

	//1. generating geometry

	int i = 0; //keep track of index

	for (theta = 0.0; theta < 2 * pi; theta += step)//nested for loop iterating through theta and phi
	{
		for (phi = 0.0; phi < 2 * pi; phi += step)
		{
			//create 6 coordinates for the two initial triangles
			//going off of coordinates shown by TA = (theta, phi) B = (theta + delta theta, y) C = (theta, y + deltaphi), D = (theta + deltatheta), (phi + deltaphi)
			GsVec A((R + r * cos(theta)) * cos(phi), (R + r * cos(theta)) * sin(phi), r * sin(theta));
			GsVec B((R + r * cos(theta + step)) * cos(phi), (R + r * cos(theta + step)) * sin(phi), r * sin(theta + step));
			GsVec C((R + r * cos(theta)) * cos(phi + step), (R + r * cos(theta)) * sin(phi + step), r * sin(theta));
			GsVec D((R + r * cos(theta + step)) * cos(phi + step), (R + r * cos(theta + step)) * sin(phi + step), r * sin(theta + step));

			GsModel::Face face0 = GsModel::Face(i, i + 1, i + 2);
			GsModel::Face face1 = GsModel::Face(i + 3, i + 4, i + 5);

			//push points
			torus->V.push() = A; 
			torus->V.push() = C;
			torus->V.push() = D;

			torus->V.push() = A;
			torus->V.push() = D;
			torus->V.push() = B;	

			//push faces

			torus->F.push() = face0;
			torus->F.push() = face1;
			
			//use isFlat to switch between flat and smooth

			if(!isFlat) //if isFlat == true, flat calculations
			{

				//Calculating normals using origin points

				GsVec o1(R * cos(phi), R * sin(phi), 0);
				GsVec o2(R * cos(phi + step), R * sin(phi + step), 0);

				GsVec A1 = (A - o1);
				GsVec B1 = (B - o1);
				GsVec C1 = (C - o2);
				GsVec D1 = (D - o2); 

				//push normal triangles

				torus->N.push() = A1;
				torus->N.push() = C1;
				torus->N.push() = D1;

				torus->N.push() = A1;
				torus->N.push() = D1;
				torus->N.push() = B1;

				torus->set_mode(GsModel::Smooth, GsModel::NoMtl);
			}

			else //isFlat = false, SMOOTH calculations
			{
				GsVec a = torus->V[face0.b] - torus->V[face0.a]; //Set a to Triangle point 2 - Triangle point 1
				GsVec b = torus->V[face0.c] - torus->V[face0.a]; //Set b to Triangle point 3 - Triangle point 1

				//calculate cross products, then push
				
				float p = a.y * b.z - a.z * b.y;
				float p1 = a.z * b.x - a.x * b.z;
				float p2 = a.x * b.y - a.y * b.x;
				
				GsVec c(p, p1, p2);
				
				torus->N.push() = c;

				a = torus->V[face1.b] - torus->V[face1.a];
				b = torus->V[face1.c] - torus->V[face1.a];

				p = a.y * b.z - a.z * b.y;
				p1 = a.z * b.x - a.x * b.z;
				p2 = a.x * b.y - a.y * b.x;

				
				GsVec d(p, p1, p2);

				torus->N.push() = d;

				torus->set_mode(GsModel::Flat, GsModel::NoMtl);
			}

			i += 6;

		}
	}

	//2. creating material group

	GsModel::Group& g = *m.G.push();
	g.fi = 0;
	g.fn = m.F.size();
	g.dmap = new GsModel::Texture;
	g.dmap->fname.set("C:/Users/Dawan/Desktop/CSE170/lab5/sigapp/src/checkers.png");

	//3. making sure the number of materials matches number of groups

	m.M.push().init(); 
	m.M.top() = GsMaterial();

	//4. Adding texture coordinates to be used per vertex

	int nv = m.V.size();
	m.T.size(nv); //set same size as m.V array
	
	for (int i = 0; i < nv; i++)
	{
		m.T[i].set(i, i);
	}

	//5. Set parameters to enable texturing

	m.set_mode(GsModel::Smooth, GsModel::PerGroupMtl);
	m.textured = true;

	s = new SnModel(torus); //send torus to SnModel


	add_model(s, GsVec(0, 0, 0)); //initialize torus at origin using addmodel
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation ()
{
	if ( _animating ) return; // avoid recursive calls
	_animating = true;
	
	int ind = gs_random ( 0, rootg()->size()-1 ); // pick one child
	SnManipulator* manip = rootg()->get<SnManipulator>(ind); // access one of the manipulators
	GsMat m = manip->mat();

	double frdt = 1.0/30.0; // delta time to reach given number of frames per second
	double v = 4; // target velocity is 1 unit per second
	double t=0, lt=0, t0=gs_time();
	do // run for a while:
	{	while ( t-lt<frdt ) { ws_check(); t=gs_time()-t0; } // wait until it is time for next frame
		double yinc = (t-lt)*v;
		if ( t>2 ) yinc=-yinc; // after 2 secs: go down
		lt = t;
		m.e24 += (float)yinc;
		if ( m.e24<0 ) m.e24=0; // make sure it does not go below 0
		manip->initial_mat ( m );
		render(); // notify it needs redraw
		ws_check(); // redraw now
	}	while ( m.e24>0 );
	_animating = false;
}

void MyViewer::compute_segments(bool flat) {

	SnLines* l = new SnLines;
	l->init();
	l->color(GsColor::red);

	if (isFlat) //flat vectors
	{

		GsModel& m = *torus;

		for (int i = 0; i < m.F.size(); ++i) 
		{
			const GsVec& a = m.V[m.F[i].a];
			const GsVec& b = m.V[m.F[i].b];
			const GsVec& c = m.V[m.F[i].c];
			GsVec fcenter = (a + b + c) / 3.0f;
			l->push(fcenter, fcenter + m.N[i] * 15.0f);
		}

	}
	else //smooth vectors
	{

		GsModel& m = *torus;

		for (int i = 0; i < m.V.size(); ++i) 
		{

			const GsVec& a = m.V[i];
			l->push(a, a + m.N[i] * 0.1f);
		}
	} 

	rootg()->add(l); 

}

void MyViewer::show_normals ( bool view )
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for ( int k=0; k<r->size(); k++ )
	{	SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if ( !view ) { l->visible(false); continue; }
		l->visible ( true );
		if ( !l->empty() ) continue; // build only once
		l->init();
		if ( s->instance_name()==SnPrimitive::class_name )
		{	GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face ( fn );
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for ( int i=0; i<m.F.size(); i++ )
			{	const GsVec& a=m.V[m.F[i].a]; l->push ( a, a+(*n++)*f );
				const GsVec& b=m.V[m.F[i].b]; l->push ( b, b+(*n++)*f );
				const GsVec& c=m.V[m.F[i].c]; l->push ( c, c+(*n++)*f );
			}
		}  
	}
}

int MyViewer::handle_keyboard ( const GsEvent &e )
{
	int ret = WsViewer::handle_keyboard ( e ); // 1st let system check events
	if ( ret ) return ret;

	switch ( e.key )
	{	case GsEvent::KeyEsc : gs_exit(); return 1;
		/*case 'n' : { bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		default: gsout<<"Key pressed: "<<e.key<<gsnl; */

	case 'q': //implementing q to increase resolution
		n++;  // increase resolution value by 1
		rootg()->remove_all();
		build_scene();
		render();
		break;

	case 'a':  //implementing a to decrease resolution
		n--; // decrement resolution value by 1
		rootg()->remove_all();
		build_scene();
		render();
		break;

	case 'w': //implementing w to increase outer radius
		r += (r * 0.1f); //increasing outer radius by 10%		
		rootg()->remove_all();
		build_scene();
		render();
		break;

	case 's': //implementing w to decrease outer radius
		r -= (r * 0.1f); //decreasing radius by 10%
		rootg()->remove_all();
		build_scene();
		render();
		break;

	case 'e': //implementing e to increase inner radius 
		R += (R * 0.1f);  //increase R value by 10%
		rootg()->remove_all();
		build_scene();
		render();
		break;

	case 'd': //implementing d to decrease inner radius
		R -= (R * 0.1f); //decrease R value by 10%
		rootg()->remove_all();
		build_scene();
		render();
		break;
	case 'z': //enable flat shading
		isFlat = true; //set flat to true
		rootg()->remove_all();
		build_scene();
		render();
		break;
	case 'x': //enable smooth shading
		isFlat = false ; //set flat to false
		rootg()->remove_all();
		build_scene();
		render();
		break;
	case 'c': //enable normal vectors
		compute_segments(isFlat); //call compute segments
		build_scene();
		render();
		break;
	case 'v': //disable normal vectors
		rootg()->remove_all(); 
		build_scene();
		render();
		break;
	}

	return 0;
}

int MyViewer::uievent ( int e )
{
	switch ( e )
	{	case EvNormals: show_normals(_nbut->value()); return 1;
		case EvAnimate: run_animation(); return 1;
		case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
