#ifndef __NODEMODEL_H__	//guard against cyclic dependancy
#define __NODEMODEL_H__

#include "node.h"
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
 

enum ModelType{
	Sphere,
	Cube,
	Teapot,
	Cone,
	Cylinder,
	Torus,
	Tetrahedron,
	Custom
};

class NodeModel:public Node{
public:
	NodeModel(ModelType whatType);	//constructor
	
	void drawWireFrame();

	ModelType modelType;
	virtual void nodeSpecificCodeDown();
};

#endif