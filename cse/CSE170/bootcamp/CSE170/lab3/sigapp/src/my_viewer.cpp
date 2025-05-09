/* David Wang CSE 170 Fall 2019*/
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

float pi = (float) GS_PI; //value of pi in float
float piD = pi / 180; // in degrees

float hAngle = 5;  //to adjust hand degrees
float lAngle = -15; //to adjust lowerarm degrees
float uAngle = -5; //to adjust upperarm degrees

GsMat ma[3];
SnTransform* t[3];

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;
	
	//declaring SnManipulators in constructor to have position of arm and hand by default

	hand_manip = new SnManipulator; //SnManipulator for hand
	lower_manip = new SnManipulator; //SnManipulator for lowerarm
	upper_manip = new SnManipulator; //SnManipulator for upperarm

	//translation matrices
	A.translation(GsVec(0.0F, 0.0F, 26.5835F)); //values obtained from gsout
	B.translation(GsVec(0.0F, 0.0F, 28.7448F));
	C.translation(GsVec(-28.7448F, 0.0F, 0.0F));

	Y.roty((pi / 2)); //90 degrees rotation x
	
	//z rotation matrices
	A1.rotx(piD * hAngle);  //rotating hand, 0 degrees
	B1.rotz(piD * lAngle); //rotating lowerarm, 10 degrees 
	C1.rotz(piD * uAngle); //rotating upperarm, -10 degrees 

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

void MyViewer::build_scene ()
{

	//upper arm hlu abc

	GsModel* uaModel = new GsModel(); //GsModel for upper arm (ua)
	SnModel* upperArm;
	uaModel->load("../arm/rupperarm.m");
	upperArm = new SnModel(uaModel);

	SnGroup* ua_sng = new SnGroup; //SnGroup for ua
	
	upper_manip->initial_mat(C * C1 * Y); //multiplying matrices to rotate
	ua_sng->add(upperArm);
	upper_manip->child(ua_sng);
	upper_manip->visible(false);
	//rootg()->add(upper_manip);

	/*GsMat m1;
	m1.rotz(.5f);
	ua_mani->initial_mat(m1);
	GsBox gb1;
	upperArm->get_bounding_box(gb1);
	gsout << "Upper arm size = " << gb1.b << gsnl; */

	//lower arm

	GsModel* laModel = new GsModel(); //GsModel for lowel arm (ua)
	SnModel* lowerArm;
	laModel->load("../arm/rlowerarm.m");
	lowerArm = new SnModel(laModel);

	SnGroup* la_sng = new SnGroup; //SnGroup for la

	lower_manip->initial_mat(B * B1); //multiplying matrices to rotate
	la_sng->add(lowerArm);
	lower_manip->child(la_sng);

	ua_sng->add(lower_manip); //add lower SnManip to upper group

	lower_manip->visible(false);


	//rootg()->add(lower_manip);

	/*GsMat m2;
	m2.rotz(.5f);
	la_mani->initial_mat(m2);
	GsBox gb2;
	lowerArm->get_bounding_box(gb2);
	gsout << "Lower arm size = " << gb2.b << gsnl;*/

	//translation * z * y

		//hand

	GsModel* hmodel = new GsModel(); //GsModel to load rhand.m
	SnModel* hand;
	hmodel->load("../arm/rhand.m");
	hand = new SnModel(hmodel);

	SnGroup* hand_sng = new SnGroup; //SnGroup for hand

	hand_manip->initial_mat(A * A1); //multiplying matrices to rotate
	hand_sng->add(hand);
	hand_manip->child(hand_sng);

	la_sng->add(hand_manip);

	hand_manip->visible(false);

	rootg()->add(upper_manip);

	/*GsMat m;
	m.rotz(.5f);
	hand_mani->initial_mat(m);
	GsBox gb;
	hand->get_bounding_box(gb);
	gsout << "Hand size = " << gb.b << gsnl;
	t[0] = new SnTransform;
	ma[0].translation(GsVec(0.0f, 0.0f, -gb.dz() / 2.0f));
	t[0]->set(ma[0]);*/


	/*
	SnPrimitive* p;

	p = new SnPrimitive(GsPrimitive::Box,1,3,1);
	p->prim().material.diffuse=GsColor::yellow;
	add_model ( p, GsVec(0,0,0) );

	p = new SnPrimitive(GsPrimitive::Sphere,2);
	p->prim().material.diffuse=GsColor::red;
	add_model ( p, GsVec(-4,0,0) );

	p = new SnPrimitive(GsPrimitive::Cylinder,1.0,1.0,1.5);
	p->prim().material.diffuse=GsColor::blue;
	add_model ( p, GsVec(4,0,0) );

	p = new SnPrimitive(GsPrimitive::Capsule,1,1,3);
	p->prim().material.diffuse=GsColor::red;
	add_model ( p, GsVec(8,0,0) );

	p = new SnPrimitive(GsPrimitive::Ellipsoid,2.0,0.5);
	p->prim().material.diffuse=GsColor::green;
	add_model ( p, GsVec(-8,0,0) ); 

	*/
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
	{	
		while ( t-lt<frdt ) { ws_check(); t=gs_time()-t0; } // wait until it is time for next frame

		lt = t;
	
	}	while ( m.e24>0 );
	_animating = false;

	gsout << "Not yet implemented :(";
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
		case 'n' : { bool b=!_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
		
		case 'q' : //rotate shoulder +

			uAngle += 1; 

			C1.rotz(piD * uAngle);

			upper_manip->initial_mat(C * C1 * Y); 

			redraw();

			return 1;


		case 'a' : //rotate shoulder - 

			uAngle -= 1;

			C1.rotz(piD * uAngle);

			upper_manip->initial_mat(C * C1 * Y);

			redraw();

			return 1;

		case 'w' : //rotate elbow +

			lAngle -= 1;

			B1.rotx(piD * lAngle);

			lower_manip->initial_mat(B * B1);

			redraw();

			return 1;

		case 's' : //rotate elbow -

			lAngle += 1;

			B1.rotx(piD * lAngle);

			lower_manip->initial_mat(B * B1);

			redraw();

			return 1;

		case 'e' : //rotate wrist +

			hAngle -= 1;

			A1.rotx(piD * hAngle);

			hand_manip->initial_mat(A * A1);

			redraw();

			break;

		case 'd' : //rotate wrist - 


			hAngle += 1;

			A1.rotx(piD * hAngle);

			hand_manip->initial_mat(A * A1);

			redraw();

			break;



		default: gsout<<"Key pressed: "<<e.key<<gsnl;
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
