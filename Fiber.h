/*
 * Fiber.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef FIBER_H_
#define FIBER_H_

//#include "Vertex.h"
//#include "Junction.h"
//#include "Centre.h"
//#include "Triangle.h"
#include "Line.h"

//class Vertex;
//class Line;
//class Triangle;


class Fiber : public Line
{
public:
	Fiber();
	Fiber(Vertex*, Vertex*);
	Fiber(Vertex*, Vertex*, Triangle*, Triangle*);
	virtual ~Fiber();

	Cell* cell;
};

#endif /* FIBER_H_ */
