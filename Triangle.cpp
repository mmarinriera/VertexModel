/*
 * Triangle.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Triangle.h"
#include "Vertex.h"
#include "Junction.h"
#include "Centre.h"
#include "Line.h"
#include "Edge.h"
#include "Fiber.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

Triangle::Triangle()
{
	VertexA=0;
	VertexB=0;
	VertexC=0;
	LineAB=0;
	LineBC=0;
	LineCA=0;
	CentroidX=0.0f;
	CentroidY=0.0f;
	SurfaceArea=0.0f;
}

Triangle::Triangle(Vertex* va, Vertex* vb, Vertex* vc)
{
	VertexA=va;
	VertexB=vb;
	VertexC=vc;

	//Getting the triangle edges from the centres
	std::list<Line*>::const_iterator lit;
	Line* line;
	for (lit = VertexA->LineList.begin(); lit != VertexA->LineList.end(); ++lit)
	{
		line=*lit;
		if(line->GetOtherEnd(VertexA)==VertexB)
		{
			LineAB=line; break;
		}
	}
	for (lit = VertexB->LineList.begin(); lit != VertexB->LineList.end(); ++lit)
	{
		line=*lit;
		if(line->GetOtherEnd(VertexB)==VertexC)
		{
			LineBC=line;
		}
	}
	for (lit = VertexC->LineList.begin(); lit != VertexC->LineList.end(); ++lit)
	{
		line=*lit;
		if(line->GetOtherEnd(VertexC)==VertexA)
		{
			LineCA=line;
		}
	}

	//Initialize the Quantitative variables
	UpdateCentroid();
	UpdateSurfaceArea();
}

Triangle::Triangle(Vertex* va, Line* lab, Line* lbc, Line* lca)
{
	LineAB=lab;
	LineBC=lbc;
	LineCA=lca;

	//Getting the triangle Vertices from the Edges
    VertexA=va;
    VertexB=LineAB->GetOtherEnd(VertexA);
    VertexC=LineBC->GetOtherEnd(VertexB);

	//Initialize the Quantitative variables
	UpdateCentroid();
	UpdateSurfaceArea();
}

Triangle::Triangle(Vertex* va, Vertex* vb, Vertex* vc, Line* lab, Line* lbc, Line* lca)
{
    VertexA=va;
    VertexB=vb;
    VertexC=vc;

	LineAB=lab;
	LineBC=lbc;
	LineCA=lca;

	//Initialize the Quantitative variables
	UpdateCentroid();
	UpdateSurfaceArea();

}

Vertex* Triangle::GetNextVertex(Vertex* vert)
{
	//std::cout << "Triangle::GetNextVertex --> check-1" << "\n";
	if(vert==VertexA)
	{
		//std::cout << "Triangle::GetNextVertex --> check0" << "\n";
		return VertexB;
	}
	else if(vert==VertexB)
	{
		//std::cout << "Triangle::GetNextVertex --> check1" << "\n";
		return VertexC;
	}
	else if(vert==VertexC)
	{
		//std::cout << "Triangle::GetNextVertex --> check2" << "\n";
		return VertexA;
	}
	else
	{
		//std::cout << "Triangle::GetNextVertex --> VERTEX DOESN'T BELONG TO TRIANGLE" << "\n";
		return 0;
	}
}

Vertex* Triangle::GetOppositeVertex(Line* line)
{
	if(line==LineAB)
	{
		return VertexC;
	}
	else if(line==LineBC)
	{
		return VertexA;
	}
	else if(line==LineCA)
	{
		return VertexB;
	}
	else
	{
		std::cout << "Triangle::GetOppositeVertex --> EDGE DOESN'T BELONG TO TRIANGLE" << "\n";
		return 0;
	}
}

Line* Triangle::GetOppositeLine(Vertex* vert)
{
	if(vert==VertexA)
	{
		return LineBC;
	}
	else if(vert==VertexB)
	{
		return LineCA;
	}
	else if(vert==VertexC)
	{
		return LineAB;
	}
	else
	{
		std::cout << "Triangle::GetOppositeLine --> VERTEX DOESN'T BELONG TO TRIANGLE" << "\n";
		return 0;
	}
}

Vertex* Triangle::GetLead(Vertex* va,Vertex* vb)
{
	Vertex* temp;
	//std::cout << "Triangle::GetLead --> check0" << "\n";
	temp=GetNextVertex(va);
	//std::cout << "Triangle::GetLead --> check1" << "\n";
	if(temp==vb)
	{
		return vb;
		//std::cout << "Triangle::GetLead --> check2" << "\n";
	}
	else
	{
		temp=GetNextVertex(vb);
		//std::cout << "Triangle::GetLead --> check3" << "\n";
		if(temp==va)
		{
			//std::cout << "Triangle::GetLead --> check4" << "\n";
			return va;
		}
		else
		{
			std::cout << "Triangle::GetLead --> EDGE DOESN'T BELONG TO TRIANGLE" << "\n";
			return 0;
		}
	}
}

void Triangle::UpdateCentroid()
{
	CentroidX=OneThird*(VertexA->x + VertexB->x + VertexC->x);
	CentroidY=OneThird*(VertexA->y + VertexB->y + VertexC->y);
}

void Triangle::UpdateSurfaceArea()
{
	//Uses a fancy formula to calculate surface area of any triangle based on the positions of vertices
	float dab = sqrt(pow(VertexA->x - VertexB->x, 2) + pow(VertexA->y - VertexB->y, 2));
	float dbc = sqrt(pow(VertexB->x - VertexC->x, 2) + pow(VertexB->y - VertexC->y, 2));
	float dca = sqrt(pow(VertexC->x - VertexA->x, 2) + pow(VertexC->y - VertexA->y, 2));
	float s = 0.5f*(dab+dbc+dca);
	SurfaceArea = sqrt(s*(s-dab)*(s-dbc)*(s-dca));
}

Triangle::~Triangle() {
	//TODO Auto-generated destructor stub
	//TODO If there is any kind of dynamic memory allocated it should be freed manually (e.g. linked lists)
}
