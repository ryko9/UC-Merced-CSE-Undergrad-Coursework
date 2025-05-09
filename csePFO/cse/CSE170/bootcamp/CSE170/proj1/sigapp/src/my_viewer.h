# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>
# include <sig/sn_manipulator.h>
# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>

// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvNormals, EvAnimate, EvExit };
	UiCheckButton* _nbut;
	bool _animating;

	SnManipulator* ra_manip;
	SnManipulator* la_manip;
	SnManipulator* rl_manip;
	SnManipulator* ll_manip;
	SnManipulator* hd_manip;
	SnManipulator* ts_manip;

	float upperarm = (float)(GS_PI / 60);
	float lowerarm = (float)(GS_PI / 80);
	float hand = (float)(GS_PI / 100);

   public :
	MyViewer ( int x, int y, int w, int h, const char* l );
	void build_ui ();
	void add_model ( SnShape* s, GsVec p );
	void build_scene ();
	void show_normals ( bool view );
	void run_animation ();
	void switchCam();
	void regCam();
	void upperArmUp();
	void upperArmDown();
	void lowerArmUp();
	void lowerArmDown();
	void handUp();
	void handDown();
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
};

