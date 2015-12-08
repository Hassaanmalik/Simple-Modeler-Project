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

// lighting 
float light_pos0[] = {0.0,10.0,0,1.0};
float light_pos1[] = {10.0,10.0,-10,1.0};
int l = 0;

int child = 0;
bool teapot = false, sphere = false, cube = false, cone = false, cylinder = false, torus = false, thedron = false;
int objectType = 0;

double start[] ={0,0,0};
double endArray[]={1,1,1};

Vector3D locationArray[100];
int numberOfObjects = -1;

float px, py, pz;
float intX, intY, intZ;
int selected;
// faces for the cube
int indices[6][4] = { {1, 2, 6, 5}, {1, 5, 4, 0}, {5, 6, 7, 4}, {2, 6, 7, 3}, {0, 4, 7, 3}, {1, 0, 3, 2} };


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
	tempVec3.x = 0;
	tempVec3.y = 0;
	tempVec3.z = 0;

	if (objectType== 1){
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
	else if (objectType == 2){
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
	else if (objectType == 3){
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
	else if (objectType == 4){
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
	else if (objectType== 5){
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
	else if (objectType== 6){
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
	else if (objectType == 7){

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
//	printf("number of objects %i\n", numberOfObjects);
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

	
	px = start[0];
	py = start[1];
	pz = start[2];


	double A, B, C, D;

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

	// calculate distance from the origin for D
	D = (-1)*A*R0x + (-1)*B*R0y + (-1)*C*R0z;

	// calculates t
	double tN = -(A*R0x + B*R0y + C*R0z + D);
	double tD = A*Rdx + B*Rdy + C*Rdz;
	double t = tN / tD;


	//check for intersection against sphere!
	//hurray!
	// will find the first top item meeting the criteria
	for(int i = numberOfObjects; i >=0; i--){
		selected = i;
		printf("enter loop\n");

		intX = locationArray[i].x;
		intY = locationArray[i].y;
		intZ = locationArray[i].z;
		
		double flipX = -1* endArray[0];
		double flipY = -1* endArray[1];
		double flipZ = -1* endArray[2];

		double xMin = intX -2, xMax = intX+2;
		double yMin = intY - 2, yMax = intY+3;
		double zMin = intZ - 3, zMax = intZ+3;

		start[0] = abs(start[0]);
		start[1] = abs(start[1]);
		start[2] = abs(start[2]);

		printf("x: %f, y: %f,z: %f \n",intX,intY,intZ );
		printf("xMin: %f, xMax: %f\n",xMin, xMax);
		printf("yMin: %f, yMax: %f\n",yMin, yMax);
		printf("zMin: %f, zMax: %f\n",zMin, zMax);
		if ((yMin <= start[1]) && (start[1] <= yMax) && (zMin <= start[2]) && (start[2] <= zMax)){
			printf("hit X\n");
			return true;
		}
		if ((xMin <= start[0]) && (start[0] <= xMax) && (zMin <= start[2]) && (start[2] <= zMax)){
			printf("hit Y\n");
			return true;
		}
		if ((xMin <= start[0]) && (start[0] <= xMax) && (yMin <= start[1]) && (start[1] <= yMax)){
			printf("hit Z\n");
			return true;
		}
		return false;
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

void insertItem(){
	if (objectType == 1){ 
		NodeModel *A = new NodeModel(Teapot);
		SG->insertChildNodeHere(A); 
	}
	else if (objectType == 2){
		NodeModel *B = new NodeModel(Sphere);
		SG->insertChildNodeHere(B);
	}
	else if (objectType == 3){
		NodeModel *C = new NodeModel(Cube);
		SG->insertChildNodeHere(C);
	}
	else if (objectType == 4){
		NodeModel *D = new NodeModel(Cone);
		SG->insertChildNodeHere(D);
	}
	else if (objectType == 5){
		NodeModel *E = new NodeModel(Cylinder);
		SG->insertChildNodeHere(E);
	}
	else if (objectType == 6){
		NodeModel *F = new NodeModel(Torus);
		SG->insertChildNodeHere(F);
	}
	else if (objectType == 7){
		NodeModel *G = new NodeModel(Tetrahedron);
		SG->insertChildNodeHere(G);
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
		case 'A':		// for teapot
			objectType = 1;
			runGraph();
			glutPostRedisplay();
			break;
		case 's':		// for sphere
		case 'S':
			objectType = 2;
			runGraph();
			glutPostRedisplay();
			break;
		case 'd':		// for cube
		case 'D':
			objectType = 3;
			runGraph();
			glutPostRedisplay();
			break;		
		case 'f':		// for cone
		case 'F':
			objectType = 4;
			runGraph();
			glutPostRedisplay();
			break;
		case 'g':
		case 'G':		// for cylinder
			objectType = 5;
			runGraph();
			glutPostRedisplay();
			break;
		case 'h':
		case 'H':		// for torus
			objectType = 6;
			runGraph();
			glutPostRedisplay();
			break;
		case 'j':
		case 'J':		// for tetrehedron
			objectType = 7;
			runGraph();
			glutPostRedisplay();
			break;
		case 't':		// translate
			Vector3D transform;
			transform.x = 1;
			transform.y = 1;
			transform.z = 1;
			//add the node as a child of root node
			selected = SG -> returnChildNode();
			objectType= SG -> returnType();
			SG -> deleteThisNode(selected);
		//	printf("selected:%i\n", type);
			T1 = new NodeTransform(Translate, transform);
			SG->goToChild(selected);
			SG->insertChildNodeHere(T1);
			SG->goToChild(SG -> returnChildNode());
			insertItem();			

			// need to delete old item after
			// update locations array
			
			transform.x -=1;
			transform.y -=1;
			transform.z -=1;
			glutPostRedisplay(); 
			break;
		case 'r':		//rotate
			Vector4D rotate;
			rotate.w = 10;
			rotate.x = 1;
			rotate.y = 1;
			rotate.z = 1;
			//add the node as a child of root node
			selected = SG -> returnChildNode();
			objectType= SG -> returnType();
			SG -> deleteThisNode(selected);
		//	printf("selected:%i\n", type);
			T1 = new NodeTransform(Rotate, rotate);
			SG->goToChild(selected);
			SG->insertChildNodeHere(T1);
			insertItem();			

			// need to delete old item after
			// update locations array
			
			rotate.w -=1;
			rotate.x -=1;
			rotate.y -=1;
			rotate.z -=1;
			glutPostRedisplay(); 
			break;
		case 'y':		// scale
			Vector3D scale;
			scale.x = 1.5;
			scale.y = 1.5;
			scale.z = 1.5;
			//add the node as a child of root node
			selected = SG -> returnChildNode();
			objectType= SG -> returnType();
			SG -> deleteThisNode(selected);
		//	printf("selected:%i\n", type);
			T1 = new NodeTransform(Scale, scale);
			SG->goToChild(selected);
			SG->insertChildNodeHere(T1);
			insertItem();			

			// need to delete old item after
			// update locations array
			
			scale.x -=1;
			scale.y -=1;
			scale.z -=1;
			glutPostRedisplay(); 
			break;
		case 'l':
		case 'L':
			l++;
			if (l % 2 == 0)	{				
				glDisable(GL_LIGHTING);
			}			
			else{
				glEnable(GL_LIGHTING);
			}
			glutPostRedisplay();
			break;
		   // if 'j' -> decrease light 1 position
        case 'n':
        case 'N':
            light_pos0[0] -= 3;
            light_pos1[0] -= 3;
            glutPostRedisplay();
            break;
            // if 'u' -> increase light 1 position
        case 'u':
        case 'U':
            light_pos0[0] += 3;
            light_pos1[0] += 3;
            glutPostRedisplay();
            break;
            // if 'h' -> increase light 2 position
        case 'k':
        case 'K':
            light_pos0[2] += 3;
            light_pos1[2] += 3;
            glutPostRedisplay();
            break;
            // if 'k' -> decrease light 2 position
        case 'I':
            light_pos0[2] -= 3;
            light_pos1[2] -= 3;
            glutPostRedisplay();
            break;
		default: break;
		glutPostRedisplay();

	}
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

// draws the cube for each point which has a wall
void drawWireFrame(float x, float y, float z){
	// the vertices as computed from the x and z coordinates
	printf("px: %f, py: %f, pz: %f\n",x,y,z);
	float n = 1;
	float verts [8][3] = {{x-n,y-n,z+n},{x-n,y+n,z+n},{x+n,y+n,z+n},{x+n,y-n, z+n},{x-n,y-n,z-n},{x-n,y+n,z-n},{x+n,y+n,z-n},{x+n,y-n,z-n}};
//	float verts[8][3] = { {-0.5,-0.5,0.5},{-0.5,0.5,0.5}, {0.5,0.5,0.5}, {0.5,-0.5,0.5}, {-0.5,-0.5,-0.5}, {-0.5,0.5,-0.5}, {0.5,0.5,-0.5}, {0.5,-0.5,-0.5} };

	for (int i = 0; i < 8; i++){
		printf("px: %f, py: %f, pz: %f\n",verts[i][0],verts[i][1],verts[i][2]);
	}
	// for each face
	glColor3f(0,1,0);
			glutSolidCube(1);
	for (int index = 0; index < 6; index ++){
		glBegin(GL_POLYGON);	
			// for each four corners of a face
			for(int i = 0; i < 4; i++){		
				int vIndex = indices[index][i]; 
				float a = verts[vIndex][0];
				float b = verts[vIndex][1];
				float c = verts[vIndex][2];
			//	printf("px: %i\n",vIndex);
		//		printf("px: %f, py: %f, pz: %f\n",a,b,c);
				glVertex3fv(verts[vIndex]);
			}
		glEnd();
	}
	glFlush(); 
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y){
	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		bool hit = Intersect(x,y);
		printf("hit\n");
		hit = true;
		intX = 1; intY = 1; intZ = 1;
		if (hit){
		//	printf("px: %f, pz: %f\n",px, pz);
		//	drawWireFrame(intX, intY, intZ);
			drawWireFrame(1,1,1);
	}
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

	// enable two light soruces
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// set first values
	float amb0[4] = {1, 1, 1, 1};
	float diff0[4] = {1, 0, 0, 1};
	float spec0[4] = {1, 1, 1, 1};

	// set the values for the first light source
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diff0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec0);

	// set the second values
	float amb1[4] = {1, 1, 1, 1};
	float diff1[4] = {1, 0, 0, 1};
	float spec1[4] = {1, 1, 1, 1};

	// set the values for the second light source
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diff1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, amb1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, spec1);

	// turn on backface culling
    glCullFace(GL_BACK);
   	glEnable(GL_CULL_FACE);

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
	// set lighting values
	float m_amb [] ={0.25f, 0.25f, 0.25f, 1.0f  };
	float m_dif []={0.4f, 0.4f, 0.4f, 1.0f };
	float m_spec [] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
	float shiny = 76.8;

	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 0.9, 0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	drawAxis();
	glColor3f(1,1,1);

	SG->draw();
	runGraph();

	// apply light
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);

	glutSwapBuffers();
	//glutPostRedisplay();
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