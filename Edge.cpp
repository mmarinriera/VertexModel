/*
 * Edge.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Edge.h"

Edge::Edge() : Line() {}
//	VertexA=0;
//	VertexB=0;
//	TriangleA=0;
//	TriangleB=0;
//
//	Length=UpdateLength();
//
//
//}

Edge::Edge(Vertex* va, Vertex* vb) : Line(va,vb) {}
//	//VertexA=va;
//	//VertexB=vb;
//	ConnectVertex(va,'a');
//	ConnectVertex(vb,'b');
//	TriangleA=0;
//	TriangleB=0;
//
//	Length=UpdateLength();
//
//
//}

Edge::Edge(Vertex* va, Vertex* vb, Triangle* ta, Triangle* tb) : Line(va,vb,ta,tb) {}
//	//VertexA=va;
//	//VertexB=vb;
//	ConnectVertex(va,'a');
//	ConnectVertex(vb,'b');
//	TriangleA=ta;
//	TriangleB=tb;
//
//	Length=UpdateLength();
//
//}


Edge::~Edge() {
	// TODO Auto-generated destructor stub
}

