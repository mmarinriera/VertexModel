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

	SurfAreaConservationCoef=0.0f;
	SurfArea=0.0f;
	EqSurfArea=0.0f;
	PerimeterTensionCoef=0.0f;
	Perimeter=0.0f;

}

Cell::Cell(Centre* c, int b) {

	id=0;
	CellCentre=c;

	SurfAreaConservationCoef=0.0f;
	SurfArea=0.0f;
	EqSurfArea=0.0f;
	PerimeterTensionCoef=0.0f;
	Perimeter=0.0f;

}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}

