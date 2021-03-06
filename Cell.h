/*
 * Cell.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef CELL_H_
#define CELL_H_

#include <list>
#include "Vertex.h"
#include "Junction.h"
#include "Centre.h"
#include "Line.h"
#include "Edge.h"
#include "Fiber.h"
#include "Triangle.h"

//class Vertex;
//class Junction;
class Centre;
//class Line;
//class Edge;
//class Fiber;
//class Triangle;

class Cell {
public:
	Cell();
	Cell(Centre*,int);
	virtual ~Cell();

	Centre* CellCentre; //The cell centre vertex

	std::list<Junction*> JunctionList; //List of junction vertices
	std::list<Edge*> EdgeList; //List of edge lines
	std::list<Fiber*> FiberList; //List of fiber lines
	std::list<Triangle*> TriangleList; //List of triangles

	int id;

	float CellSurfArea; //actual cell surface
	float CellEqSurf;   //equilibrium surface
	float CellContractilityCoef;

//	bool IsBorder; //tells if the cell is located at the border of the system
//	bool IsFixed; //tells if the cell is fixed in space
//	bool HasOuterForce; //tells if an outer force is applied onto the cell (usually for a cell in the border
//	float OuterForceModulus;
//	float OuterForceVX;
//	float OuterForceVY;

};

#endif /* CELL_H_ */
