#ifndef __NODEGROUP_H__	//guard against cyclic dependancy
#define __NODEGROUP_H__

#include "node.h"

class NodeGroup: public Node{
public:
	NodeGroup();	//constructor

	virtual void nodeSpecificCodeDown();
	virtual void nodeSpecificCodeUp();
};

#endif