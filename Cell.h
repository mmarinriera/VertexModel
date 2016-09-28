/*
 * Cell.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef CELL_H_
#define CELL_H_

#include <list>

#include "Centre.h"
#include "Junction.h"
#include "Edge.h"
#include "Line.h"
#include "Fiber.h"
#include "Triangle.h"

//#include "Edge.h"
//#include "Vertex.h"

//class Vertex;
//class Junction;
//class Centre;
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

	//Mechanical parameters
	float SurfAreaConservationCoef;
	float SurfArea; //actual cell surface
	float EqSurfArea;   //equilibrium surface
	float PerimeterTensionCoef;
	float Perimeter;

	//temporal storage for calculated variables (this avoids repeating the same calculation in the MechSolver
	float SurfAreaConservationProduct;
	float PerimeterTensionProduct;

	void UpdateCalculations();


//	bool IsBorder; //tells if the cell is located at the border of the system
//	bool IsFixed; //tells if the cell is fixed in space
//	bool HasOuterForce; //tells if an outer force is applied onto the cell (usually for a cell in the border
//	float OuterForceModulus;
//	float OuterForceVX;
//	float OuterForceVY;

};

#endif /* CELL_H_ */
