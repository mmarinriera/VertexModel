/*
 * System.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <list>
#include <iostream>
#include "Vertex.h"
#include "Junction.h"
#include "Centre.h"
#include "Line.h"
#include "Edge.h"
#include "Fiber.h"
#include "Triangle.h"
#include "Cell.h"

class System {
public:
	System();
	virtual ~System();

	int CellNumber;
	float x_min;
	float x_max;
	float y_min;
	float y_max;
	float length_x;
	float length_y;
	float std_cell_radius; //dumb variable, we have to remove it

	float GabrielScreeningCoefficient; //this is used for the Gabriel screening
	float EulerDelta;

	void Init();
	//void NeighborhoodBuildProximity();
	void NeighborhoodTriangulation();
	//void NeighborhoodGabriel();

	//solvers

	void MechSolver();

	/////////////////////////////////////
	Cell* NewCell(float,float);
	void UpdateSystemDimensions();
	void TimeIterator(int);

	void InitialConditionsSingleCell();

	//////////////////////////////////////////

	//TODO create interfaces between the system and the outside world, this means create functions that extract informations from
	//system objects and functions that run through object lists that can be called from the outside world.

	//std::list::const_iterator<Cell*> iterCell;
	//std::list<Vertex*>::const_iterator iterVertex;
	//std::list::const_iterator<Line*> iterLine;
	//std::list::const_iterator<Triangle*> iterTriangle;

	std::list<Cell*> CellList; //List of cells
	std::list<Vertex*> VertexList; //List of cells
	std::list<Line*> LineList; //List of cells
	std::list<Triangle*> TriangleList; //List of cells

	//SpaceGridContainer* SpaceGrid; //the space grid is not necessary, we have to remove it


};

#endif /* SYSTEM_H_ */
