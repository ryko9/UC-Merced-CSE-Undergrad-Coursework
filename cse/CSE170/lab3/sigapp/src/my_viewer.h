# pragma once

# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>

# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>
# include <sig/sn_manipulator.h>
// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvNormals, EvAnimate, EvExit };
	UiCheckButton* _nbut;
	bool _animating;
   public :
	MyViewer ( int x, int y, int w, int h, const char* l );
	void build_ui ();
	void add_model ( SnShape* s, GsVec p );
	void build_scene ();
	void show_normals ( bool view );
	void run_animation ();
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
	SnManipulator* hand_manip;
	SnManipulator* lower_manip;
	SnManipulator* upper_manip;
	GsMat A;
	GsMat B;
	GsMat C;
	GsMat Y;
	GsMat A1; //new hand
	GsMat B1; //new lower arm
	GsMat C1; //new upper arm
};

