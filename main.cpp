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

int type;

int getType(){
	return type;
}
void setType (int t){
	type = t;
}

int child = 0;
bool teapot = false, sphere = false, cube = false, cone = false, cylinder = false, torus = false, thedron = false;

double start[] ={0,0,0};
double endArray[]={1,1,1};

Vector3D locationArray[100];
int numberOfObjects = -1;

//sceneGraph
#include "sceneGraph.h"
#include "nodeGroup.h"
#include "nodeModel.h"
#include "nodeTransform.h"

SceneGraph *SG;
NodeTransform *T1;

Vector3D tempVec3;

//function which will populate a sample graph 
void initGraph(){
	//TRANSFORMATION
	//a tranlation transformation node
	//how much translation
	tempVec3.x = 1;
	tempVec3.y = 0;
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
		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		teapot = false;
		setType(1);
		NodeModel *M1 = new NodeModel(Teapot);
		SG->insertChildNodeHere(M1);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (sphere){

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		sphere = false;
		setType(2);
		NodeModel *M2 = new NodeModel(Sphere);
		SG->insertChildNodeHere(M2);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (cube){

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		cube = false;
		setType(3);
		NodeModel *M3 = new NodeModel(Cube);
		SG->insertChildNodeHere(M3);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (cone){

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		cone = false;
		setType(4);
		NodeModel *M4 = new NodeModel(Cone);
		SG->insertChildNodeHere(M4);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (cylinder){

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		cylinder = false;
		setType(5);
		NodeModel *M5 = new NodeModel(Cylinder);
		SG->insertChildNodeHere(M5);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (torus){

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		torus = false;
		setType(6);
		NodeModel *M6 = new NodeModel(Torus);
		SG->insertChildNodeHere(M6);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (thedron){

		T1 = new NodeTransform(Translate, tempVec3);
		SG->insertChildNodeHere(T1);
		SG->goToChild(SG -> returnChildNode());
		thedron = false;
		setType(7);
		NodeModel *M7 = new NodeModel(Tetrahedron);
		SG->insertChildNodeHere(M7);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}

}

void GetOGLPos(int x, int y){
	tempVec3.x = 0;
 	tempVec3.y = 0;
 	tempVec3.z = 0;

    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLdouble winX, winY, winZ;
    GLdouble posX, posY, posZ;
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (double)x;
    winY = (double)viewport[3] - (double)y;
    glReadPixels( x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );
 
    gluUnProject( winX, winY, 0.8, modelview, projection, viewport, &posX, &posY, &posZ);
 
 	tempVec3.x = posX;
 	tempVec3.y = posY;
 	tempVec3.z = posZ;

 	printf("click point: %d,%d,%d\n", &posX, &posY, &posZ);

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

	double px, py, pz;
	px = start[0];
	py = start[1];
	pz = start[2];


	double A, B, C, D;

	double R0x, R0y, R0z;
	double Rdx, Rdy, Rdz;

	float intX = locationArray[numberOfObjects].x;
	float intY = locationArray[numberOfObjects].y;
	float intZ = locationArray[numberOfObjects].z;

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

	// calculate distance from the origin for D
	D = (-1)*A*R0x + (-1)*B*R0y + (-1)*C*R0z;

	// calculates t
	double tN = -(A*R0x + B*R0y + C*R0z + D);
	double tD = A*Rdx + B*Rdy + C*Rdz;
	double t = tN / tD;


	//check for intersection against sphere!
	//hurray!
	for(int i = 0; i <=numberOfObjects; i++){
		printf("enter loop\n");
/*		// check if N*Rd == 0 then no hit
		if (tD == 0){
			printf("missed");
			return false;
		}
		else {
			double P = (R0x + R0y + R0z) + t*(Rdx + Rdy + Rdz);
			printf("Intersection at: P = %f\n", P);
			return true;
		}*/
		double flipX = -1* endArray[0];
		double flipY = -1* endArray[1];
		double flipZ = -1* endArray[2];
		printf("x: %f, y: %f,z: %f \n",intX,intY,intZ );
		if (start[1] < intY < flipY && start[2] < intZ < flipZ){
			printf("hit X\n");
			return true;
		}
		if (start[0] < intX < flipX && start[2] < intZ < flipZ){
			printf("hit Y\n");
			return true;
		}
		if (start[0] < intX < flipX && start[1] < intY < flipY){
			printf("hit Z\n");
			return true;
		}
	}

	

	/*// N*Rd = 
	// or t = ((-N*R0 + D)/N*Rd)

	double sq = B*B  - 4*A*C;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * B + sqrt(sq))/(2*A);
		t1 = ((-1) * B - sqrt(sq))/(2*A);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
	}


	return false; //else returns false */

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
			runGraph();
			break;
		case 's':
		case 'S':
			sphere = true;
			runGraph();
			break;
		case 'd':
		case 'D':
			cube = true;
			runGraph();
			break;		
		case 'f':
		case 'F':
			cone = true;
			runGraph();
			break;
		case 'g':
		case 'G':
			cylinder = true;
			runGraph();
			break;
		case 'h':
		case 'H':
			torus = true;
			runGraph();
			break;
		case 'j':
		case 'J':
			thedron = true;
			runGraph();
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
			camPos[0]-=1;
			break;

		case GLUT_KEY_RIGHT:
			camPos[0]+=1;
			break;

		case GLUT_KEY_UP:
			camPos[2] -= 1;
			break;

		case GLUT_KEY_DOWN:
			camPos[2] += 1;
			break;
		
		case GLUT_KEY_HOME:
			camPos[1] += 1;
			break;

		case GLUT_KEY_END:
			camPos[1] -= 1;
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
		Intersect(x,y);
	}
	glutPostRedisplay();
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