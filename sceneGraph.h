#ifndef __SCENEGRAPH_H__	//guard against cyclic dependancy
#define __SCENEGRAPH_H__

#include "node.h"
#include "structs.h"
class SceneGraph{
public:
	SceneGraph();	//constructor
	void runGraph();
	//Scene Graph Navigation
	void goToRoot();
	void goToChild(int i);
	void goToParent();
	void insertChildNodeHere(Node *node);
	void deleteThisNode();

	//Scene Graph Draw
	void draw();
	int returnChildNode();

private:
	Node *currentNode;
	Node *rootNode;
};

#endif