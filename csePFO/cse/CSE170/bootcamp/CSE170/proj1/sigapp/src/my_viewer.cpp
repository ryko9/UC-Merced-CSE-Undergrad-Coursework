/* David Wang CSE 170 Fall 2019 */

# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

float pi = (float) GS_PI; //Helper variable for Pi value in radians
float piD = pi / 180; //in degrees

GsVec mover = GsVec(0.0f, 0.0f, 0.0f); //for updating values during movement
GsVec xmove = GsVec(0.0f, 0.0f, 0.0f);
GsVec nxmove = GsVec(0.0f, 0.0f, -2.0f);

SnGroup* fullBody = new SnGroup;
SnGroup* g = new SnGroup;
SnPrimitive* body;

SnModel* obs[9]; //array of SnModels to store individual objects
SnTransform* ts[3]; //array of SnTransforms for the non-moving background objects

GsMat A[9]; //GsMatrices for translations
GsMat B[9];

//Declare GsBoxs to get bounding coordinates
GsBox ra; //Right arm gsbox
GsBox la; //Left arm gsbox
GsBox rl; //Right leg gsbox
GsBox ll; //Left leg gsbox
GsBox hd; //Head gsbox
GsBox to; //Torso gsbox
GsBox tr; //Tree gsbox
GsBox bx; //Box gsbox
GsBox bx1; //Box 2

GsMat m;
GsMat m1, m2;

//Angles

float raAngle = 0; //adjusting right arm
float laAngle = 0; //adjusting left arm
float hdAngle = 0; //adjusting head
float rlAngle = 0; //adjusting right leg
float llAngle = 0; //adjusting left leg

//Boolean for moving in arrow key directions

bool isForward; //if true move forward, if false move backward
bool isRight; //if true movef right, if false move left
bool cam = true;

MyViewer::MyViewer ( int x, int y, int w, int h, const char* l ) : WsViewer(x,y,w,h,l)
{
	_nbut=0;
	_animating=false;

	//initialize manipulators
	ra_manip = new SnManipulator;
	la_manip = new SnManipulator;
	rl_manip = new SnManipulator;
	ll_manip = new SnManipulator;
	hd_manip = new SnManipulator;
	ts_manip = new SnManipulator;

	build_ui();
	build_scene();
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

	//Right Arm (A[0])

	obs[0] = new SnModel; //initialize at index 0 of obs[]
	//ts[0] = new SnTransform; //initialize at index 0 of ts[0]
	SnGroup* ra_grp = new SnGroup;

	if (!obs[0]->model()->load("../objects/arm1/a.obj")) //debug
	{
		gsout << "Right arm was not loaded" << gsnl;
	}

	obs[0]->model()->get_bounding_box(ra); //Calculate bounding box coordinates
	A[0].translation(mover);

	//ra_manip->visible(true); //put into SnManip
	ra_manip->initial_mat(A[0]);
	ra_grp->add(obs[0]);
	ra_manip->child(ra_grp);

	//gsout << "Right arm coordinates = " << ra.b << gsnl;

	//Right Leg (A[1])

	obs[1] = new SnModel;
	//ts[1] = new SnTransform;
	SnGroup* rl_grp = new SnGroup;

	if (!obs[1]->model()->load("../objects/leg1/leg1.obj"))
	{
		gsout << "Right leg was not loaded" << gsnl;
	}

	obs[1]->model()->get_bounding_box(rl);
	A[1].translation(mover);


	//rl_manip->visible(true);
	rl_manip->initial_mat(A[1]);
	rl_grp->add(obs[1]);
	rl_manip->child(rl_grp);

	gsout << "Right leg coordinates = " << rl.b << gsnl;

	//Left Arm A([2])

	obs[2] = new SnModel;
	//ts[2] = new SnTransform;
	SnGroup* la_grp = new SnGroup;

	if (!obs[2]->model()->load("../objects/arm2/arm2.obj"))
	{
		gsout << "Left arm was not loaded" << gsnl;
	}

	obs[2]->model()->get_bounding_box(la);
	A[2].translation(mover);


	//la_manip->visible(true);
	la_manip->initial_mat(A[2]);
	la_grp->add(obs[2]);
	la_manip->child(la_grp);

	gsout << "Right arm coordinates = " << la.b << gsnl;

	//Left Leg A[3]

	obs[3] = new SnModel;
	//ts[3] = new SnTransform;
	SnGroup* ll_grp = new SnGroup;

	if (!obs[3]->model()->load("../objects/leg2/leg2.obj"))
	{
		gsout << "Left leg was not loaded" << gsnl;
	}

	obs[3]->model()->get_bounding_box(ll);

	A[3].translation(mover);


	//ll_manip->visible(true);
	ll_manip->initial_mat(A[3]);
	ll_grp->add(obs[3]);
	ll_manip->child(ll_grp);

	gsout << "Left leg coordinates = " << ll.b << gsnl;

	//Head A[4]

	obs[4] = new SnModel;
	//ts[4] = new SnTransform;
	SnGroup* hd_grp = new SnGroup;

	if (!obs[4]->model()->load("../objects/head/head.obj"))
	{
		gsout << "Head was not loaded" << gsnl;
	}
	obs[4]->model()->get_bounding_box(hd);
	A[4].translation(mover);
	//ts[4]->set(A[4]);


	//hd_manip->visible(true);
	hd_manip->initial_mat(A[4]);
	hd_grp->add(obs[4]);
	hd_manip->child(hd_grp);

	gsout << "Head coordinates = " << hd.b << gsnl;

	//Torso A[5]

	obs[5] = new SnModel;
	//ts[5] = new SnTransform;
	SnGroup* ts_grp = new SnGroup;

	if (!obs[5]->model()->load("../objects/torso/torso.obj"))
	{
		gsout << "Torso was not loaded" << gsnl;
	}

	obs[5]->model()->get_bounding_box(to);
	A[5].translation(mover);
	//ts[5]->set(A[5]);

	ts_grp->add(obs[5]);

	//ts_manip->visible(true);
	ts_manip->initial_mat(A[5]);
	ts_grp->add(obs[5]);
	ts_manip->child(ts_grp);

	gsout << "Torso coordinates = " << to.b << gsnl;

	//Add body part SnManips to ts_grp since torso is the only object that does not move

	ts_grp->add(hd_manip);
	ts_grp->add(ra_manip);
	ts_grp->add(la_manip);
	ts_grp->add(rl_manip);
	ts_grp->add(ll_manip); 

	rootg()->add(ts_manip); //draw ts_manip 

	//Tree

	obs[6] = new SnModel;
	ts[0] = new SnTransform;

	if (!obs[6]->model()->load("../objects/tree/tree.obj"))
	{
		gsout << "Tree was not loaded" << gsnl;
	}

	obs[6]->model()->get_bounding_box(tr);
	A[6].translation(GsVec(0, 0, 0));
	ts[0]->set(A[6]);

	gsout << "Tree coordinates = " << tr.b << gsnl;

	//Box

	obs[7] = new SnModel;
	ts[1] = new SnTransform;

	if (!obs[7]->model()->load("../objects/box/box.obj"))
	{
		gsout << "Box was not loaded" << gsnl;
	}

	obs[7]->model()->get_bounding_box(bx);
	A[7].translation(mover);
	ts[1]->set(A[7]);

	//gsout << "Box coordinates = " << bx.b << gsnl;

	//Box 2

	obs[8] = new SnModel;
	ts[2] = new SnTransform;

	if (!obs[8]->model()->load("../objects/box1/box1.obj"))
	{
		gsout << "2nd box was not loaded" << gsnl;
	}

	obs[8]->model()->get_bounding_box(bx1);
	A[8].translation(mover);
	ts[2]->set(A[8]);

	//gsout << "Box coordinates = " << bx1.b << gsnl;

	//Floor
	
	body = new SnPrimitive(GsPrimitive::Box, 100, 100, 1);
	body->prim().material.diffuse = GsColor::black;
	add_model(body, GsVec(0.0f, -33.0f, 0.0f));	
	
	//Drawing the non-moving objects
	
	for (int i = 0; i < 3; i++) 
	{
		g->add(ts[i]);
		g->add(obs[i + 6]);
	}
	rootg()->add(g); 
	
}


void MyViewer::switchCam() {

	double lt, t0 = gs_time();
	do {
		lt = gs_time() - t0;
		camera().eye.x += 0.02f;
		camera().center.x += 0.02f;
		//camera().up.x += 0.001f;
		render();
		ws_check();
		message().setf("local time =%f", lt);
	} 
	while (lt < 3.0f); 
		

}


void MyViewer::regCam()
{
	camera().eye = GsPnt(0.0, 0.0, 1.0);
	camera().center = (GsPnt(0.0, 200.0, 0.0));
	camera().up = GsPnt(0.0, 1.0, 0.0);
	camera().translate(GsVec(0.0, -200.0, 50.0));
	render();
	ws_check();
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
		default: gsout<<"Key pressed: "<<e.key<<gsnl;

		case 'q': //Move right arm up
			
			raAngle += 1;

			B[0].rotx(piD * raAngle);
			
			m = ra_manip->mat();
			
			m1.translation(xmove);
			m2.translation(nxmove);
			//m.setrans(xmove);
			//m1.setrans(nxmove);

				///m*rot*m1

			ra_manip->initial_mat(B[0] * A[0]);
			//ra_manip->initial_mat(m * m2 * B[0] * m1);

			//ra_manip->initial_mat(m * B[0]);

			redraw();

			return 1;
	
		 case 'a': //Move right arm down

			raAngle -= 1;

			B[0].rotx(piD * raAngle);

			ra_manip->initial_mat(A[0] * B[0]);

			redraw();

			return 1;

		case 'w':  //Move left arm up
			
			laAngle += 1;

			B[2].rotx(piD * laAngle);

			la_manip->initial_mat(A[2] * B[2]);

			redraw();

			return 1;

		case 's': //Move left arm down

			laAngle -= 1;

			B[2].rotx(piD * laAngle);

			la_manip->initial_mat(A[2] * B[2]);

			redraw();

			return 1;

		case 'e':  //Move head up
			
			hdAngle += 1;

			B[4].rotx(piD * hdAngle);

			hd_manip->initial_mat(A[4] * B[4]);

			redraw();

			return 1;

		case 'd': //Move head down 

			hdAngle -= 1;

			B[4].rotx(piD * hdAngle);

			hd_manip->initial_mat(A[4] * B[4]);

			redraw();

			return 1;

		case 'r': //Move right leg up

			rlAngle += 1;

			B[1].rotx(piD * rlAngle);

			rl_manip->initial_mat(A[1] * B[1]);

			redraw();

			return 1;

		case 'f': //Move right leg down

			rlAngle -= 1;

			B[1].rotx(piD * rlAngle);

			rl_manip->initial_mat(A[1] * B[1]);

			redraw();

			return 1;


		case 't': //Move left leg up

			llAngle += 1;

			B[3].rotx(piD * llAngle);

			ll_manip->initial_mat(A[3] * B[3]);

			redraw();

			return 1;

		case 'g': //Move left leg down

			llAngle -= 1;

			B[3].rotx(piD* llAngle);

			ll_manip->initial_mat(A[3] * B[3]);

			redraw();

			return 1;

		case GsEvent::KeySpace: //Switching camera angles
			
			if (cam == true)
			{
				switchCam();
				cam = false;
			}
			else if (cam == false)
			{
				regCam();
				cam = true;
			}
			

			redraw();

			return 1;

		//case LeftArrow

		case GsEvent::KeyUp: {
			
			/*GsMat trans, rot;
			trans.translation((1) * GsVec::j);

			rl_manip->getref().mult(rl_manip->getref(), trans);
			la_manip
			ll_manip*/


				isForward = true;

				//mover.x += 100;
				mover.y -= 10;
				//mover.z += 100;


				//A[0].translation(mover);
				//A[1].translation(mover);
				//A[2].translation(mover);
				//A[3].translation(mover);
				//A[4].translation(mover);
				A[5].translation(mover);

				//ra_manip->initial_mat(A[0]);
				//rl_manip->initial_mat(A[1]);
				//la_manip->initial_mat(A[2]);
				//ll_manip->initial_mat(A[3]);
				//hd_manip->initial_mat(A[4]);
				ts_manip->initial_mat(A[5]);



				redraw();


			return 1;
		}

		case GsEvent::KeyDown: {

			isForward = false;

			mover.y += 10;

			A[5].translation(mover);

			ts_manip->initial_mat(A[5]);

			redraw();


			return 1;
		}

		case GsEvent::KeyRight: {

			isRight = true;

			mover.x += 10;

			A[5].translation(mover);

			ts_manip->initial_mat(A[5]);

			redraw();


			return 1;
		}

		case GsEvent::KeyLeft: {

			isRight = false;

			mover.x -= 10;

			A[5].translation(mover);

			ts_manip->initial_mat(A[5]);

			redraw();


			return 1;
		}


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
