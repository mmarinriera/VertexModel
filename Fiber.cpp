/*
 * Fiber.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Fiber.h"

Fiber::Fiber() : Line()
{
	IsFiber=true;
}

Fiber::Fiber(Vertex* va, Vertex* vb) : Line(va,vb)
{
	IsFiber=true;
}


Fiber::Fiber(Vertex* va, Vertex* vb, Triangle* ta, Triangle* tb) : Line(va,vb,ta,tb)
{
	IsFiber=true;
}


Fiber::~Fiber() {
	// TODO Auto-generated destructor stub
}

