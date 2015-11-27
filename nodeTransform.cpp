#include "nodeTransform.h"
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
 

//for gltranslate and gl scale
NodeTransform::NodeTransform(transformType whatType, Vector3D vec3){
	nodeType = transformation;
	transformationType = whatType;
	amount3 = vec3;
}

//for gl rotate
NodeTransform::NodeTransform(transformType whatType, Vector4D vec4){
	nodeType = transformation;
	transformationType = whatType;
	amount4 = vec4;
}

void NodeTransform::nodeSpecificCodeDown(){
	switch (transformationType){
	case Translate:
		glTranslatef(amount3.x, amount3.y, amount3.z);
		break;
	case Rotate:
		glRotatef(amount4.w, amount4.x, amount4.y, amount4.z);
		break;
	case Scale:
		glScalef(amount3.x, amount3.y, amount3.z);
		break;
	}
}
