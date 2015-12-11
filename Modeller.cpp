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

GLfloat fogColor[4] = {1.0f,1.0f,1.0f,1.0f}; 

float pos[] = {0,1,0};
float camPos[] = {2.5, 2.5, 5};
float angle = 0.0f;


//node ids
int masterID = 0;
int getID(){
	return masterID++;
}

Vector3D locationArray[100];
int numberOfObjects = 0;

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

int getNumber(){
	return numberOfObjects;
}

bool fog = false;

// lighting 
float light_pos0[] = {0.0,10.0,0,1.0};
float light_pos1[] = {10.0,10.0,-10,1.0};
int l = 0;

//material
float m_amb [] ={0.25f, 0.25f, 0.25f, 1.0f  };
float m_dif []={0.4f, 0.4f, 0.4f, 1.0f };
float m_spec [] ={0.774597f, 0.774597f, 0.774597f, 1.0f };
float shiny = 76.8;

int child = 0;
bool teapot = false, sphere = false, cube = false, cone = false, cylinder = false, torus = false, thedron = false;
int objectType = 0;

double start[] ={0,0,0};
double endArray[]={1,1,1};

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
NodeTransform *S1;
NodeTransform *R1;

Vector3D tempVec3, vec3S;
Vector4D vec4R;

//function which will populate a sample graph 
void initGraph(){
	NodeGroup *G1 = new NodeGroup();
	//insert the node into the graph
	SG->insertChildNodeHere(G1);
	SG->goToChild(0);
}

void runGraph(){
	tempVec3.x = 0;
	tempVec3.y = 0;
	tempVec3.z = 0;

	vec3S.x = 1;
	vec3S.y = 1;
	vec3S.z = 1;

	vec4R.w = 1;
	vec4R.x = 1;
	vec4R.y = 1;
	vec4R.z = 1;

	if (teapot){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		teapot = false;
		setType(1);
		NodeModel *M1 = new NodeModel(Teapot);
		SG->insertChildNodeHere(M1);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (objectType == 2){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		sphere = false;
		setType(2);
		NodeModel *M2 = new NodeModel(Sphere);
		SG->insertChildNodeHere(M2);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (objectType == 3){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		setType(3);
		NodeModel *M3 = new NodeModel(Cube);
		SG->insertChildNodeHere(M3);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (objectType == 4){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		cone = false;
		setType(4);
		NodeModel *M4 = new NodeModel(Cone);
		SG->insertChildNodeHere(M4);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (objectType== 5){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		cylinder = false;
		setType(5);
		NodeModel *M5 = new NodeModel(Cylinder);
		SG->insertChildNodeHere(M5);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (objectType== 6){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		torus = false;
		setType(6);
		NodeModel *M6 = new NodeModel(Torus);
		SG->insertChildNodeHere(M6);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	else if (objectType == 7){
		T1 = new NodeTransform(Translate, tempVec3);
		S1 = new NodeTransform(Scale, vec3S);
		R1 = new NodeTransform(Rotate, vec4R);
		SG->goToRoot();
		SG->goToChild(0);
		SG->insertChildNodeHere(T1);
		SG->goToChild(numberOfObjects);
		SG->insertChildNodeHere(S1);
		SG->goToChild(0);
		SG->insertChildNodeHere(R1);
		SG->goToChild(0);
		thedron = false;
		setType(7);
		NodeModel *M7 = new NodeModel(Tetrahedron);
		SG->insertChildNodeHere(M7);
		numberOfObjects +=1;
		locationArray[numberOfObjects] = tempVec3;
	}
	glutPostRedisplay();
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
/*	for(int i = numberOfObjects; i >=0; i--){
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
	} */

	

	//// N*Rd = 
	// or t = ((-N*R0 + D)/N*Rd)

	double sq = B*B  - 4*A*C;

	double t0 = 0, t1 = 0;

	if(sq < 0)
		printf("no Intersection!!!\n");
	else{
		t0 = ((-1) * B + sqrt(sq))/(2*A);
		t1 = ((-1) * B - sqrt(sq))/(2*A);

		printf("Intersection at: t = %f, and t = %f\n", t0, t1);
		return true;
	}


	return false; //else returns false 

}

bool locateNode(int id){
	return SG -> goToNode(id);
	printf("did not find");
}


void transformObject(int ObjNumber, int x, int y, int z){
	Vector3D v;
	v.x = x; v.y = y; v.z = z;
	// may need to initialize a new translate node
	T1 = new NodeTransform(Translate, v);
	int nodeNum = (4 * ObjNumber) + 2;
	bool exists = locateNode(nodeNum);
	if (exists){
		SG->insertChildNodeHere(T1);
		glutPostRedisplay();
	}
}

void rotateObject(int ObjNumber, int w, int x, int y, int z){
	Vector4D v;
	v.w = w; v.x = x; v.y = y; v.z = z;
	R1 = new NodeTransform(Rotate, v);
	int nodeNum = (4 * ObjNumber) + 4;
	SG->insertChildNodeHere(R1);
	glutPostRedisplay();
//	SG->goToChild(SG -> returnChildNode());
}

void scaleObject(int ObjNumber, int x, int y, int z){
	Vector3D v;
	v.x = x; v.y = y; v.z = z;
	S1 = new NodeTransform(Scale, vec3S);
//	int nodeNum = (4 * ObjNumber) + 3;
//	bool exists = locateNode(nodeNum);
//	if (exists){
		SG->insertChildNodeHere(S1);
		glutPostRedisplay();
//	}
//	SG->goToChild(SG -> returnChildNode());
}

//callbacks
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case '1':
			m_amb[0] = 0.25f;m_amb[1] = 0.25f;m_amb[2] = 0.25f;m_amb[3] = 1.0f;
			m_dif[0] = 0.4f;m_dif[1] = 0.4f;m_dif[2] = 0.4f;m_dif[3] = 1.0f;
			m_spec[0] = 0.774597f;m_spec[1] = 0.774597f;m_spec[2] = 0.774597f;m_spec[3] = 1.0f;
			shiny = 76.8;
			break;
		case '2':
			m_amb[0] = 0.329412f;m_amb[1] = 0.223529f;m_amb[2] = 0.027451f;m_amb[3] = 1.0f;
			m_dif[0] = 0.780392f;m_dif[1] = 0.568627f;m_dif[2] = 0.113725f;m_dif[3] = 1.0f;
			m_spec[0] = 0.992157f;m_spec[1] = 0.941176f;m_spec[2] = 0.807843f;m_spec[3] = 1.0f;
			shiny = 27.8974f;
			break;
		case '3':
			m_amb[0] = 0.1745f;m_amb[1] = 0.01175f;m_amb[2] = 0.01175f;m_amb[3] = 0.55f;
			m_dif[0] = 0.61424f;m_dif[1] = 0.04136f;m_dif[2] = 0.04136f;m_dif[3] = 0.55f;
			m_spec[0] = 0.727811f;m_spec[1] = 0.626959f;m_spec[2] = 0.626959f;m_spec[3] = 0.55f;
			shiny = 76.8f;
			break;
		case '4':
			m_amb[0] = 0.0215f;m_amb[1] = 0.1745f;m_amb[2] = 0.0215f;m_amb[3] = 0.55f;
			m_dif[0] = 0.07568f;m_dif[1] = 0.61424f;m_dif[2] = 0.07568f;m_dif[3] = 0.55f;
			m_spec[0] = 0.633f;m_spec[1] = 0.727811f;m_spec[2] = 0.626959f;m_spec[3] = 0.55f;
			shiny = 76.8f;
			break;
		case '5':
			m_amb[0] = 0.24725f;m_amb[1] = 0.1995f;m_amb[2] = 0.0745f;m_amb[3] = 0.55f;
			m_dif[0] = 0.75164f;m_dif[1] = 0.60648f;m_dif[2] = 0.22648f;m_dif[3] = 0.55f;
			m_spec[0] = 0.628281f;m_spec[1] = 0.555802f;m_spec[2] = 0.366065f;m_spec[3] = 0.55f;
			shiny = 51.2f;
			break;
		case 'q':
		case 27:
			exit (0);
			break;
		case '6':// for teapot
			objectType = 1;
			teapot = true;
			runGraph();
			glutPostRedisplay();
			break;
		case '7':		// for sphere
			objectType = 2;
			runGraph();
			glutPostRedisplay();
			break;
		case '8':		// for cube
			objectType = 3;
			runGraph();
			glutPostRedisplay();
			break;		
		case '9':		// for cone
			objectType = 4;
			runGraph();
			glutPostRedisplay();
			break;
		case '0':		// for cylinder
			objectType = 5;
			runGraph();
			glutPostRedisplay();
			break;
		case '-':	// for torus
			objectType = 6;
			runGraph();
			glutPostRedisplay();
			break;
		case '=':	// for tetrehedron
			objectType = 7;
			runGraph();
			glutPostRedisplay();
			break;
		case 'v':		// translate on +x 
		//	Vector3D transform;
			transformObject(0, 1,0,0);
		case 'w':		// translate on -x
		//	Vector3D transform;
			transformObject(0, -1,0,0);
			break;
		case 'e':		// translate on + y
		//	Vector3D transform;
			transformObject(0, 0,1,0);
			break;
		case 'a':		// translate on -y
		//	Vector3D transform;
			transformObject(0, 0,-1,0);
			break;
		case 't':		// translate on +z
		//	Vector3D transform;
			transformObject(0, 0,0,1);
			break;
		case 'y':		// translate on -z
		//	Vector3D transform;
			transformObject(0, 0,0,-1);
			break;
		case 'z':		//rotate on x
			rotateObject(0,10,1,0,0);
			break;
		case 'x':		//rotate on y
			rotateObject(0,10,0,1,0);
			break;
		case 'c':		//rotate on z
			rotateObject(0,10,0,0,1);
			break;
		case 'p':		// scale
			vec3S.x = 1.2;
			vec3S.y = 1.2;
			vec3S.z = 1.2;			
			scaleObject(1,1.2,1.2,1.2);
			break;
		case 'o':		// scale
			vec3S.x = 0.8;
			vec3S.y = 0.8;
			vec3S.z = 0.8;			
			scaleObject(1,0.8,0.8,0.8);
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
        case 'r':		// reset
            SG -> deleteAllNodes();
            glutPostRedisplay();
            break;
        case 'f':		// fog
        	if (fog){
				glEnable(GL_FOG); 
				fog = false;
			}
			else{
				glDisable(GL_FOG);
				fog = true;
			}
            glutPostRedisplay();
            break;
        case 'd':
       		 NodeModel *Test;
			Test->drawWireFrame();
			break;
		default: 
		break;
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


void mouse(int button, int state, int x, int y){
	bool hit = Intersect(x,y);
//	if(button ==  GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		//hit = true;
		intX = 1; intY = 1; intZ = 1;
		if (hit==true){
			printf("hit\n");
		//	SG -> wireOn();
		//	SG -> draw();
			NodeModel *Test;
			Test->drawWireFrame();
			glutPostRedisplay();
		} 
		else{
			SG -> wireOff();
			glutPostRedisplay();
		}
	//} 
	if (button ==  GLUT_RIGHT_BUTTON && state == GLUT_DOWN){	
	//	int objectNumber = 0;
	//	int number = (4*objectNumber)+1;
	//	locateNode(number);	
		SG -> deleteThisNode();
		//SG -> deleteAllNodes();
	//	SG -> delete();
		numberOfObjects --;
	}
	//bool temp = SG->deleteNode();
	//temp = false;
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

	float density = 0.3; //fog density
	float fogColor[4] = {0.5, 0.5, 0.5, 1.0};


//	glEnable (GL_FOG); 
	glFogi (GL_FOG_MODE, GL_EXP2); 
	glFogfv (GL_FOG_COLOR, fogColor); 
	glFogf (GL_FOG_DENSITY, density); 
	glHint (GL_FOG_HINT, GL_NICEST); 


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
void display(void){

	float origin[3] = {0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 0.9, 0.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], 0,0,0, 0,1,0);
	drawAxis();
	glColor3f(1,1,1);

	SG->draw();
	printf("End of iteration\n");
//	runGraph();

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