#include "NodeModel.h"
#include <stdio.h> //needed for printf command
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
 

NodeModel::NodeModel(ModelType whatType){	//constructor
	nodeType = model;
	modelType = whatType;
	isDrawable = true;
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
	switch (modelType){
	case Sphere:
		glColor3f(0,0,1);
		glutSolidSphere(1, 12, 10);
		break;
	case Cube:
		glColor3f(1,0,1);
		glutSolidCube(1);
		break;
	case Teapot:
		glColor3f(0,1,1);
		glutSolidTeapot(1);
		break;
	case Cone:
		glColor3f(1,1,0);
		glutSolidCone(1,2,40,1);
		break;
	case Cylinder:
		glColor3f(1,0.5,1);
		glutSolidCone(1,3,30, 10);
		break;
	case Torus:
		glColor3f(0,1,0);
		glutSolidTorus(0.5,1,30, 30);
		break;
	case Tetrahedron:
		glColor3f(1,0,0);
		glutSolidTetrahedron();
		break;
	case Custom:
		//own mesh thing
		break;
	}
}