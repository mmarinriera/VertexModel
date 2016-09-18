/*
 * Cell.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Cell.h"

Cell::Cell() {

	id=0;
	CellCentre=0;

	CellSurfArea=0.0f;
	CellEqSurf=0.0f;
	CellContractilityCoef=0.0f;

}

Cell::Cell(Centre* c, int b) {

	id=0;
	CellCentre=c;

	CellSurfArea=0.0f;
	CellEqSurf=0.0f;
	CellContractilityCoef=0.0f;

}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

