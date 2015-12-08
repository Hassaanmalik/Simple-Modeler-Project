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
int SceneGraph::deleteThisNode(int i){
//	goToChild(i) ->isDrawable = true;
//	return goToChild(i) -> currentNode -> type;
	return 1;
	//TODO
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