#include "NodeModel.h"
#include <stdio.h> //needed for printf command
#include <gl\glut.h>

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
		glutSolidSphere(1, 12, 10);
		break;
	case Cube:
		glutSolidCube(1);
		break;
	case Teapot:
		glutSolidTeapot(1);
		break;
	case Cone:
		glutSolidCone(1,2,40,1);
		break;
	case Cylinder:
		glutSolidCone(1,3,30, 10);
		break;
	case Torus:
		glutSolidTorus(0.5,1,30, 30);
		break;
	case Tetrahedron:
		glutWireTetrahedron();
		break;
	case Custom:
		//own mesh thing
		break;
	}
}