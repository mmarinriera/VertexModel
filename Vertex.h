/*
 * Vertex.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include<list>

class Line;
class Triangle;

class Vertex
{
public:
	Vertex();
	Vertex(float,float);
	virtual ~Vertex();

	float x;
	float y;

	std::list<Triangle*> TriangleList;
	std::list<Line*> LineList;

};

#endif /* VERTEX_H_ */
