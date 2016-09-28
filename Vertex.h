/*
 * Vertex.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef VERTEX_H_
#define VERTEX_H_

#include<list>
#include<vector>


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

	float dx;  //motion differential (dx,dy)
	float dy;

	//logical variables (to determine derived class type)
	bool IsJunction;
	bool IsCentre;

	bool IsFixed; //This will fix the vertex in space so it doesn't move (e.g. in the borders of the system

	int id;

	std::list<Triangle*> TriangleList;
	std::list<Line*> LineList;

};

#endif /* VERTEX_H_ */
