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

//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

int child = 0;
bool teapot = false, sphere = false, cube = false, cone = false, cylinder = false, torus = false, thedron = false;

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

//function which will populate a sample graph 
void initGraph(){
	//temporary place which holds out values
	Vector3D tempVec3;


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


	//MODEL
	//we will now add a teapot model to the graph as a child of the
	//transformation node
//	NodeModel *M1 = new NodeModel(Teapot);
//	NodeModel *M2 = new NodeModel(Sphere);
//	NodeModel *M3 = new NodeModel(Cube);
//	NodeModel *M4 = new NodeModel(Cone);
//	NodeModel *M5 = new NodeModel(Cylinder);
//	NodeModel *M6 = new NodeModel(Torus);
//	NodeModel *M7 = new NodeModel(Tetrahedron);

	
	//insert the node into the graph
//	SG->insertChildNodeHere(M2);
//	SG->insertChildNodeHere(M3);
//	SG->insertChildNodeHere(M4);
//	SG->insertChildNodeHere(M5);
//	SG->insertChildNodeHere(M6);
//	SG->insertChildNodeHere(M7);

	//THE SAME FLOW CAN BE USED TO DYNAMICALLY ADD NODES
	//DURING RUNTIME
}

void runGraph(){
	//temporary place which holds out values
	Vector3D tempVec3;


	//TRANSFORMATION
	//a tranlation transformation node
	//how much translation
	tempVec3.x = 1000;
	tempVec3.y = 10;
	tempVec3.z = 10;
	T1 = new NodeTransform(Translate, tempVec3);


	//add the node as a child of root node
//	T1 = new NodeTransform(Translate, tempVec3);
//	//insert the node into the graph
//	SG->insertChildNodeHere(T1);
//	//go to the child node
//	SG->goToChild(0);


	//MODEL
	//we will now add a teapot model to the graph as a child of the
	//transformation node
//	NodeModel *M1 = new NodeModel(Teapot);
//	NodeModel *M2 = new NodeModel(Sphere);
//	NodeModel *M3 = new NodeModel(Cube);
//	NodeModel *M4 = new NodeModel(Cone);
//	NodeModel *M5 = new NodeModel(Cylinder);
//	NodeModel *M6 = new NodeModel(Torus);
//	NodeModel *M7 = new NodeModel(Tetrahedron);



//	SG->insertChildNodeHere(M2);
//	
//	SG->insertChildNodeHere(M4);
//	SG->insertChildNodeHere(M5);
//	SG->insertChildNodeHere(M6);
//	SG->insertChildNodeHere(M7);

	//THE SAME FLOW CAN BE USED TO DYNAMICALLY ADD NODES
	//DURING RUNTIME */
	if (teapot){
		teapot = false;
		SG->insertChildNodeHere(M1);
	}
	else if (sphere){
		sphere = false;
		SG->insertChildNodeHere(M2);
	}
	else if (cube){
		cube = false;
		SG->insertChildNodeHere(M3);
	}
	else if (cone){
		cone = false;
		SG->insertChildNodeHere(M4);
	}
	else if (cylinder){
		cylinder = false;
		SG->insertChildNodeHere(M5);
	}
	else if (torus){
		torus = false;
		SG->insertChildNodeHere(M6);
	}
	else if (thedron){
		thedron = false;
		SG->insertChildNodeHere(M7);
	}

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


	//draw the sceneGraph
	SG->draw();
	runGraph();

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

	init();

	glutMainLoop();				//starts the event loop
	return(0);					//return may not be necessary on all compilers
}