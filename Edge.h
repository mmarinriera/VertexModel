/*
 * Edge.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef EDGE_H_
#define EDGE_H_


//#include "Vertex.h"
//#include "Junction.h"
//#include "Centre.h"
//#include "Triangle.h"
#include "Line.h"

//class Vertex;
class Line;
//class Triangle;

class Edge : public Line {
public:
	Edge();
	Edge(Vertex*, Vertex*);
	Edge(Vertex*, Vertex*, Triangle*, Triangle*);
	virtual ~Edge();
};

#endif /* EDGE_H_ */
