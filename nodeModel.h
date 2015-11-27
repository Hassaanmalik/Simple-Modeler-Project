#ifndef __NODEMODEL_H__	//guard against cyclic dependancy
#define __NODEMODEL_H__

#include "node.h"
#include <gl/glut.h>

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
	ModelType modelType;

	virtual void nodeSpecificCodeDown();
};

#endif