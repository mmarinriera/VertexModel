/*
 * Edge.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Edge.h"

Edge::Edge() : Line()
{
	IsEdge=true;
}


Edge::Edge(Vertex* va, Vertex* vb) : Line(va,vb)
{
	IsEdge=true;
}


Edge::Edge(Vertex* va, Vertex* vb, Triangle* ta, Triangle* tb) : Line(va,vb,ta,tb)
{
	IsEdge=true;
}

Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

