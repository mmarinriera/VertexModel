/*
 * Junction.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef JUNCTION_H_
#define JUNCTION_H_

#include "Vertex.h"

//class Line;
//class Triangle;

class Cell;


class Junction : public Vertex {
public:
	Junction();
	Junction(float, float);
	virtual ~Junction();

	// List of cells
	std::list<Cell*> CellList;
};

#endif /* JUNCTION_H_ */
