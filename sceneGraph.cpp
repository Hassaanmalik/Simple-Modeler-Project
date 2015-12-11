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

#include "sceneGraph.h"
#include "node.h"
#include <stdio.h>
#include "structs.h"


int location = 0;
int typeItem; 



SceneGraph::SceneGraph(){
	rootNode = new Node();
	currentNode = rootNode;
	//printf("scene graph init done\n");
}

void SceneGraph::runGraph(){
//	rootNode = new Node();
	//currentNode = ->children->push_back(node);
	//printf("scene graph init done\n");
}

//Scene Graph Navigation
//resets the current node to the root of the graph
void SceneGraph::goToRoot(){
	currentNode = rootNode;
}


//moves to a child node i
void SceneGraph::goToChild(int i){
	if (i < currentNode->children->size() && i >= 0){
		currentNode = currentNode->children->at(i);
		typeItem = currentNode -> type;
	}
	else
		printf("child out of range");
	if (i > location){location = i+1;}
	//i = location;
}

void SceneGraph::goToParent(){
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
//	printf("nodeType: %i\n", node->nodeType->whatType);
	 //add our parent to our child node
    node->parent = currentNode;
    //now lets add it to our children!
    currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
//	currentNode->children->erase(currentNode->children->begin()+0);
	if (!currentNode->children->empty()){//} && currentNode -> frameOn == true){
	//	goToParent();
		currentNode->children->pop_back();
	} 
	//goToParent();
	//currentNode = current
	//currentNode->children->erase(currentNode->children->begin()+0);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteAllNodes(){
	goToParent();
  	while(!currentNode->children->empty()){
    	currentNode->children->pop_back();
  	}
}

int SceneGraph::returnType(){
	return typeItem;
}

int SceneGraph::returnChildNode(){
	return location;
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
}

void SceneGraph::wireOn(){
	printf("on\n");
	currentNode -> frameOn = true;
	//currentNode -> nodeModel -> drawWireFrame();
	//drawWireFrame();
//	currentNode -> drawWireFrame();
//	currentNode -> nodeType -> whatType;
//	currentNode -> drawWireFrame();
}
void SceneGraph::wireOff(){
	printf("off\n");
//	node->nodeType->whatType;
//	currentNode -> nodeModel;
	currentNode -> frameOn = false;
}

bool SceneGraph::compareNode(int id){
	if (currentNode ->ID == id){
		temp = currentNode;
		return true;
	}
	else{

	}
}
bool SceneGraph::goToNode(int id){
	int nodeCount = 0;
	for (int i = 0; i <= currentNode -> numberOfObjects - 1; i++){
		try{
			goToRoot();
			compareNode(id);
			goToChild(0);
			compareNode(id);
			goToChild(nodeCount);
			compareNode(id);
			goToChild(0);
			compareNode(id);
			goToChild(0);
			compareNode(id);
			goToChild(0);
			compareNode(id);
		}
		catch(...){
			// do nothing
		}
		nodeCount+= 1;
	} 
	if (temp != 0){
		currentNode = temp;
		temp = 0;
		return true;
	}
	else{
		return false;
	}
}