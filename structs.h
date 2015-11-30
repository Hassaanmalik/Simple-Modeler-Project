#ifndef __STRUCTS_H__	//guard against cyclic dependancy
#define __STRUCTS_H__
#include "structs.h"

typedef struct{
	float x, y, z;
}Vector3D;

typedef struct{
	float x, y, z, w;
}Vector4D;
#endif