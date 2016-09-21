/*
 * Junction.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Junction.h"

Junction::Junction() : Vertex()
{
	IsJunction=true;
}



Junction::Junction(float a, float b) : Vertex(a,b)
{
	IsJunction=true;
}

Junction::~Junction() {
	// TODO Auto-generated destructor stub
}

