/*
 * Fiber.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Fiber.h"

Fiber::Fiber() : Line() {}
//	VertexA=0;
//	VertexB=0;
//	TriangleA=0;
//	TriangleB=0;
//
//	Length=UpdateLength();
//
//
//}

Fiber::Fiber(Vertex* va, Vertex* vb) : Line(va,vb) {}
//	//VertexA=va;
//	//VertexB=vb;
//	ConnectVertex(va,'a');
//	ConnectVertex(vb,'b');
//	TriangleA=0;
//	TriangleB=0;
//
//	Length=UpdateLength();
//
//}

Fiber::Fiber(Vertex* va, Vertex* vb, Triangle* ta, Triangle* tb) : Line(va,vb,ta,tb) {}
//	//VertexA=va;
//	//VertexB=vb;
//	ConnectVertex(va,'a');
//	ConnectVertex(vb,'b');
//	TriangleA=ta;
//	TriangleB=tb;
//
//	//Length=UpdateLength();
//
//}


Fiber::~Fiber() {
	// TODO Auto-generated destructor stub
}

