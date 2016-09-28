/*
 * Triangle.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vertex.h"
//#include "Junction.h"
//#include "Centre.h"

#include "Line.h"
//#include "Cell.h"
//#include "Edge.h"
//#include "Fiber.h"

//class Vertex;
//class Junction;
//class Centre;
//class Line;
//class Edge;
//class Fiber;

class Cell;

class Triangle {
public:

	Triangle();
	Triangle(Vertex*,Vertex*,Vertex*);
	Triangle(Vertex*,Line*,Line*,Line*);
	Triangle(Vertex*,Vertex*,Vertex*,Line*,Line*,Line*);

	//the vertices of the triangle are ordered in clock-wise sense (A-B-C-A)
	Vertex* VertexA;
	Vertex* VertexB;
	Vertex* VertexC;
	Line* LineAB;
	Line* LineBC;
	Line* LineCA;

	Cell* cell;

	float CentroidX,CentroidY;
	float SurfaceArea; //,SurfacePartialA,SurfacePartialB,SurfacePartialC; We don't need surface partials, I think

	static const float OneThird=1.0f/3.0f;

	int id;

	Vertex* GetOppositeVertex(Line*);
	Line* GetOppositeLine(Vertex*);
	Line* GetAdjacentLine(Vertex*, Line*);
	Vertex* GetLead(Vertex*,Vertex*);
	void UpdateCentroid();
	void UpdateSurfaceArea();
	virtual ~Triangle();

	Vertex* GetNextVertex(Vertex*);
	Line* GetNextLine(Line*);

};

#endif /* TRIANGLE_H_ */
