# pragma once
# include "sn_mynode.h" //in order to create snmynodeobject
# include <sig/sn_poly_editor.h>
# include <sig/sn_lines2.h>

# include <sigogl/ui_button.h>
# include <sigogl/ws_viewer.h>
# include <sigogl/ui_check_button.h>
// Viewer for this example:
class MyViewer : public WsViewer
{  protected :
	enum MenuEv { EvAdd, EvInfo, EvExit,  EvMultiColor, EvNormals, EvAnimate};
	UiCheckButton* mcolorbut;
	UiCheckButton* _nbut;
	bool _animating;
   public :

	   //declare node
	   SnMyNode* c; //implementing snmynode function in order to access member variables in keyboard handler class

	MyViewer ( int x, int y, int w, int h, const char* l );
	void add_ui ();
	void add_mynode ( int n );
	void build_ui();
	void add_model(SnShape* s, GsVec p);
	void build_scene();
	void show_normals(bool view);
	void run_animation();
	virtual int handle_keyboard ( const GsEvent &e ) override;
	virtual int uievent ( int e ) override;
};
