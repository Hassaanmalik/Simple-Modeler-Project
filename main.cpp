/* CS 3GC3 - Texturing sample
 * by R. Teather
 */
#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <stdio.h>
 #include <stdlib.h>
 #include <math.h>

#include "structs.h"

float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;

int clickX, clickY, clickZ;

bool clicked = false;
// int turn = 0;

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

// return x y and z for node.cpp
int nodeX = 0, nodeY = 0, nodeZ = 0;
int getX (){
	return nodeX;
}
int getY (){
	return nodeY;
}
int getZ (){
	return nodeZ;
}
void setX (int x){
	nodeX = x;
}
void setY (int y){
	nodeY = y;
}
void setZ (int z){
	nodeZ = z;
}

int child = 0;
bool teapot = false, sphere = false, cube = false, cone = false, cylinder = false, torus = false, thedron = false;

double start[] ={0,0,0};
double endArray[]={1,1,1};

//sceneGraph
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"

SceneGraph *SG;
NodeTransform *T1;

NodeModel *M1 = new NodeModel(Teapot);
NodeModel *M2 = new NodeModel(Sphere);
NodeModel *M3 = new NodeModel(Cube);
NodeModel *M4 = new NodeModel(Cone);
NodeModel *M5 = new NodeModel(Cylinder);
NodeModel *M6 = new NodeModel(Torus);
NodeModel *M7 = new NodeModel(Tetrahedron);

Vector3D tempVec3;

//function which will populate a sample graph 
void initGraph(){
	//TRANSFORMATION
	//a tranlation transformation node
	//how much translation
	tempVec3.x = 1;
	tempVec3.y = 1;
	tempVec3.z = 1;
	//add the node as a child of root node
	T1 = new NodeTransform(Translate, tempVec3);
	//insert the node into the graph
	SG->insertChildNodeHere(T1);
	//go to the child node
	SG->goToChild(0);
}

void runGraph(){
	if (teapot){
		tempVec3.x = clickX;
		tempVec3.y = clickY;
		tempVec3.z = clickZ;
		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		teapot = false;
		SG->insertChildNodeHere(M1);
		tempVec3.x = 1; tempVec3.y = 1; tempVec3.z = 1;
	}
	else if (sphere){
		tempVec3.x = getX();
		tempVec3.y = getY();
		tempVec3.z = getZ();

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		sphere = false;
		SG->insertChildNodeHere(M2);
	}
	else if (cube){
		tempVec3.x = getX();
		tempVec3.y = getY();
		tempVec3.z = getZ();

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		cube = false;
		SG->insertChildNodeHere(M3);
	}
	else if (cone){
		tempVec3.x = getX();
		tempVec3.y = getY();
		tempVec3.z = getZ();

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		cone = false;
		SG->insertChildNodeHere(M4);
	}
	else if (cylinder){
		tempVec3.x = getX();
		tempVec3.y = getY();
		tempVec3.z = getZ();

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		cylinder = false;
		SG->insertChildNodeHere(M5);
	}
	else if (torus){
		tempVec3.x = getX();
		tempVec3.y = getY();
		tempVec3.z = getZ();

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		torus = false;
		SG->insertChildNodeHere(M6);
	}
	else if (thedron){
		tempVec3.x = getX();
		tempVec3.y = getY();
		tempVec3.z = getZ();

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		thedron = false;
		SG->insertChildNodeHere(M7);
	}

}

bool Intersect(int x, int y){
	printf("%i, %i\n", x, y);

	//allocate matricies memory
	double matModelView[16], matProjection[16]; 
	int viewport[4]; 

	//vectors


	//grab the matricies
	glGetDoublev(GL_MODELVIEW_MATRIX, matModelView); 
	glGetDoublev(GL_PROJECTION_MATRIX, matProjection); 
	glGetIntegerv(GL_VIEWPORT, viewport); 

	//unproject the values
	double winX = (double)x; 
	double winY = viewport[3] - (double)y; 

	// get point on the 'near' plane (third param is set to 0.0)
	gluUnProject(winX, winY, 0.0, matModelView, matProjection, 
         viewport, &start[0], &start[1], &start[2]); 

	// get point on the 'far' plane (third param is set to 1.0)
	gluUnProject(winX, winY, 1.0, matModelView, matProjection, 
         viewport, &endArray[0], &endArray[1], &endArray[2]); 


	printf("near point: %f,%f,%f\n", start[0], start[1], start[2]);
	printf("far point: %f,%f,%f\n", endArray[0], endArray[1], endArray[2]);


	if (clicked == true){
		setX(endArray[0]);
		setY(endArray[1]);
		setZ(endArray[2]);
		clicked = false;
	}
	//check for intersection against sphere!
	//hurray!

	double A, B, C;

	double R0x, R0y, R0z;
	double Rdx, Rdy, Rdz;

	R0x = start[0];
	R0y = start[1];
	R0z = start[2];

	Rdx = endArray[0] - start[0];
	Rdy = endArray[1] - start[1];
	Rdz = endArray[2] - start[2];

	//magnitude!
	double M = sqrt(Rdx*Rdx + Rdy*Rdy + Rdz* Rdz);

	//unit vector!
	Rdx /= M;
	Rdy /= M;
	Rdz /= M;

	//A = Rd dot Rd
	A = Rdx*Rdx + Rdy*Rdy + Rdz*Rdz;

	double Btempx, Btempy, Btempz;
	Btempx = R0x;
	Btempy =  R0y;
	Btempz =  R0z;

	B = Btempx * Rdx + Btempy * Rdy + Btempz *Rdz;
	B *= 2.0;

	C = R0x*R0x + R0y*R0y + R0z* R0z - 1;


	double sq = B*B  - 4*A*C;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * B + sqrt(sq))/(2*A);
		t1 = ((-1) * B - sqrt(sq))/(2*A);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
	}


	return false; //else returns false
}


//callbacks
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'q':
		case 27:
			exit (0);
			break;
		case 'a':
		case 'A':
			teapot = true;
			break;
		case 's':
		case 'S':
			sphere = true;
			break;
		case 'd':
		case 'D':
			cube = true;
			break;		
		case 'f':
		case 'F':
			cone = true;
			break;
		case 'g':
		case 'G':
			cylinder = true;
			break;
		case 'h':
		case 'H':
			torus = true;
			break;
		case 'j':
		case 'J':
			thedron = true;
			break;
		case 'm':
			Vector3D tempVec3;

			//TRANSFORMATION
			//a tranlation transformation node
			//how much translation
			tempVec3.x = 5;
			tempVec3.y = 5;
			tempVec3.z = 5;
			//add the node as a child of root node
			T1 = new NodeTransform(Translate, tempVec3);
			//insert the node into the graph
			SG->insertChildNodeHere(T1);
			//go to the child node
			SG->goToChild(SG -> returnChildNode());

			//insert the node into the graph
			SG->insertChildNodeHere(T1);
			//go to the child node
			SG->goToChild(4);


	}
	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch(key)
	{
		case GLUT_KEY_LEFT:
			camPos[0]-=0.1;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+=0.1;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 0.1;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 0.1;
			break;
		
		case GLUT_KEY_HOME:
			camPos[1] += 0.1;
			break;

		case GLUT_KEY_END:
			camPos[1] -= 0.1;
			break;

	}
	glutPostRedisplay();
}

void drawAxis()
{
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex3f(0,0,0);
	glVertex3f(50,0,0);
//	glColor3f(0,1,0);
	glVertex3f(0,0,0);
	glVertex3f(0,50,0);
//	glColor3f(0,0,1);
	glVertex3f(0,0,0);
	glVertex3f(0,0,50);
	glEnd();
}

void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		clicked = true;
		Intersect(x,y);
		clickX = getX();
		clickY = getY();
		clickZ = getZ();
	}

}

void init(void)
{	GLuint id = 1;

	glEnable(GLUT_DEPTH);

	//glClearColor(0, 0, 0, 0);
	glClearColor(1, 1, 0.9, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);

	//init our scenegraph
	SG = new SceneGraph();

	//add various nodes
	//initializing our world
	initGraph();
}


/* display function - GLUT display callback function
 *		clears the screen, sets the camera position, draws the ground plane and movable box
 */
void display(void)
{
	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 0.9, 0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	drawAxis();
	glColor3f(1,1,1);

	printf("near point: %f,%f,%f\n", getX, getY, getZ);

	//if (clicked){
	//	clicked = false;
		//draw the sceneGraph
		SG->draw();
		runGraph();
	//}

	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("SimpleSceneGraph");	//creates the window

	
	glClearColor(1, 1, 0.5, 0.5);
	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	init();

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}