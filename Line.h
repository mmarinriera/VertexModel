/*
 * Line.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef LINE_H_
#define LINE_H_

#include "Vertex.h"
//#include "Junction.h"
//#include "Centre.h"
#include "Triangle.h"
#include "Vector2D.h"


class Line {
public:
	Line();
	Line(Vertex*,Vertex*);
	Line(Vertex*,Vertex*,Triangle*,Triangle*);
	virtual ~Line();

	Vertex* VertexA;
	Vertex* VertexB;
	Triangle* TriangleA;
	Triangle* TriangleB;


	Vector2D<float> VectorAB;
	float Length;

	//mechanical parameters
	float LineTensionCoef;

	//logical variables (to determine derived class type)
	bool IsEdge;
	bool IsFiber;

	int id;

	void UpdateLength();
	Vertex* GetOtherEnd(Vertex*);
	Triangle* GetOtherSide(Triangle*);
	void ConnectVertex(Vertex*,char);
	char GetVertexIndex(Vertex*);

	void UpdateVector();
	Vector2D<float> GetVectorByOrigin(Vertex*);

};

#endif /* LINE_H_ */
