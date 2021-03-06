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
 #include "structs.h"

NodeModel::NodeModel(ModelType whatType){	//constructor
	nodeType = model;
	modelType = whatType;
	isDrawable = true;
}

void NodeModel::drawWireFrame(){
	//if(frameOn == true){
	//	printf("frameOn%i\n", frameOn);
		glColor3f(0,1,0);
		glutWireCube(2);

	//}
}

//as the node moves down through it, we want to perform down action
//which in this case means drawing the model
void NodeModel::nodeSpecificCodeDown(){
	switch (modelType){
	case Sphere:
		//frameOn = true;
		if(frameOn){
			glColor3f(0,1,0);
			glutWireCube(2);
		}
		glColor3f(0,0,1);
		glutSolidSphere(1, 12, 10);
		break;
	case Cube:
		frameOn = true;
	//	if(frameOn){drawWireFrame();}
		glColor3f(1,0,1);
		glutSolidCube(1);
		break;
	case Teapot:
	//	frameOn = true;
	//	if(frameOn){drawWireFrame();}
		glColor3f(0,1,1);
		glutSolidTeapot(1);
		break;
	case Cone:
	//	frameOn = true;
	//	if(frameOn){drawWireFrame();}
		glColor3f(1,1,0);
		glutSolidCone(1,1,40,1);
		break;
	case Cylinder:
	//	frameOn = true;
	//	if(frameOn){drawWireFrame();}
		glColor3f(1,0.5,1);
		GLUquadricObj *quadratic;
		quadratic = gluNewQuadric();
		glutSolidCone(1,0.5,40,1);
		glRotatef(180, 1.0, 0.0, 0.0);
		glTranslatef(0,0,-0.5);
		glutSolidCone(1,0.5,40,1);
		gluCylinder(quadratic,1,1, 1, 40,5);
		break;
	case Torus:
	//	frameOn = true;
	//	if(frameOn){drawWireFrame();}
		glColor3f(0,1,0);
		glutSolidTorus(0.2,0.6,30, 30);
		break;
	case Tetrahedron:
	//	frameOn = true;
	//	if(frameOn){drawWireFrame();}
		glColor3f(1,0,0);
		glutSolidTetrahedron();
		break;
	case Custom:
		//own mesh thing
		glColor3f(0,1,0);
		glutWireCube(2);
		break;
	}
}