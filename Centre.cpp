/*
 * Centre.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Centre.h"
//#include "Cell.h"

Centre::Centre() : Vertex()
{
	IsCentre=true;
	//cell=0;
}


Centre::Centre(float a, float b) : Vertex(a,b)
{
	IsCentre=true;
	//cell=c;
}

Centre::~Centre() {
	// TODO Auto-generated destructor stub
}

