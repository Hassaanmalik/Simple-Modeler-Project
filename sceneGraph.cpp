#include "sceneGraph.h"
#include "node.h"
#include <stdio.h>
#include "structs.h"

int location = 0;

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
	if (i < currentNode->children->size() && i >= 0)
		currentNode = currentNode->children->at(i);
	else
		printf("child out of range");
	location = i;
}

void SceneGraph::goToParent(){
	if (currentNode->parent != 0)
		currentNode = currentNode->parent;
}

//inserts a child node into the current node
void SceneGraph::insertChildNodeHere(Node *node){
	 //add our parent to our child node
    node->parent = currentNode;
    //now lets add it to our children!
    currentNode->children->push_back(node);
}

//deletes the current node, relinking the children as necessary
void SceneGraph::deleteThisNode(){
	//TODO
}

int SceneGraph::returnChildNode(){
	return location;
}

//draw the scenegraph
void SceneGraph::draw(){
	rootNode->draw();
}