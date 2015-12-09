#include "node.h"
#include <stdio.h>
#include "structs.h"
Node::Node(){	//constructor
	ID = getID();
	nodeType = root; //base class will be only really our root node, so lets do that
	isDrawable = false;
	children = new vector<Node*>();
	parent = 0;
	currentChild = 0;
	coordinates.x = getX(), coordinates.y = getY(), coordinates.z = getZ();
	type = getType();
	frameOn = false;

	//printf("node init done\n");
}

//==================================================================
//function which does all the heavy lifting
void Node::draw(){
	//printf("nodeModel: %i\n", model);
	//we entered node, so execute the commands
	//ie. push matrix, apply material, draw geometry, etc.
	nodeSpecificCodeDown();

	//recursively call our children
	const int numberOfChildren = children->size();
	if (numberOfChildren > 0){
		for (int i = 0; i < numberOfChildren; i++){
			children->at(i)->draw();

		}
	}

	//we are exiting the node, so execute the commands
	//ie. pop matrix, etc.
	nodeSpecificCodeUp();
}

//====================================================================
//FUNCTION THAT DOES THE ACTUAL STUFF IN 
//DERIVED CLASSES

//TO BE OVERRIDDEN IN CHILD CLASSES AS NEEDED
//code where we add what the node will do when moving down the tree
void Node::nodeSpecificCodeDown(){}

//code where we add what the node will do when moving up the tree
void Node::nodeSpecificCodeUp(){}