/*
 * Centre.h
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#ifndef CENTRE_H_
#define CENTRE_H_

#include "Cell.h"

class Cell;

class Centre : public Vertex
{
public:
	Centre();
	Centre(float, float);
	virtual ~Centre();

	//Cell* cell;
};

#endif /* CENTRE_H_ */
