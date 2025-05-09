# include "sn_mynode.h"

const char* SnMyNode::class_name = "SnMyNode"; // static
SN_SHAPE_RENDERER_DEFINITIONS(SnMyNode);

//===== SnMyNode =====

SnMyNode::SnMyNode () : SnShape ( class_name )
{
	width = 0.5f;
	height = 1.0f;
	R = 0.75; //use R, r, and n as member functions of SnMyNode so they can be accessed from keyboard class
	r = 0.02;// R = inner radius, R = outer radius, N = number of faces / resolution 
	n = 12;
	if ( !SnMyNode::renderer_instantiator ) SnMyNodeRegisterRenderer ();
}

SnMyNode::~SnMyNode ()
{
}

void SnMyNode::get_bounding_box ( GsBox& b ) const
{
	// the bounding box is needed for camera view_all computations
	b.set ( init, init+GsVec(width,height,0) );
}

//===== Renderer Instantiator =====

# include "glr_mynode.h"

static SnShapeRenderer* GlrMyNodeInstantiator ()
{
	return new GlrMyNode;
}

void SnMyNodeRegisterRenderer ()
{
	SnMyNode::renderer_instantiator = &GlrMyNodeInstantiator;
}
