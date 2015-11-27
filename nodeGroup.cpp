#include "nodeGroup.h"
#include <stdio.h> //needed for printf command
#include <gl/glut.h>

NodeGroup::NodeGroup(){
	nodeType = group;
}

void NodeGroup::nodeSpecificCodeDown(){
	glPushMatrix();
}

void NodeGroup::nodeSpecificCodeUp(){
	glPopMatrix();
}