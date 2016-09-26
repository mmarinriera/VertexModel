/*
 * Vertex.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Vertex.h"

Vertex::Vertex() {
	x=0;
	y=0;

	id=0;

	IsJunction=false;
	IsCentre=false;

	IsFixed=false;

}

Vertex::Vertex(float a,float b) {
	x=a;
	y=b;

	id=0;

	IsJunction=false;
	IsCentre=false;

	IsFixed=false;

}

Vertex::~Vertex() {
	// TODO Auto-generated destructor stub
}

