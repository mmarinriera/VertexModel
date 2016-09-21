/*
 * Line.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "Line.h"
#include <cmath>
#include <iostream>


Line::Line() {
	VertexA=0;
	VertexB=0;
	TriangleA=0;
	TriangleB=0;

	Length=0.0f;

	LineTensionCoef=0.0f;

	IsEdge=false;
	IsFiber=false;


}

Line::Line(Vertex* va, Vertex* vb) {
	//VertexA=va;
	//VertexB=vb;
	ConnectVertex(va,'a');
	ConnectVertex(vb,'b');
	TriangleA=0;
	TriangleB=0;

	UpdateLength();

	LineTensionCoef=0.0f;

	IsEdge=false;
	IsFiber=false;

}

Line::Line(Vertex* va, Vertex* vb, Triangle* ta, Triangle* tb) {
	//VertexA=va;
	//VertexB=vb;
	ConnectVertex(va,'a');
	ConnectVertex(vb,'b');
	TriangleA=ta;
	TriangleB=tb;

	UpdateLength();

	LineTensionCoef=0.0f;

	IsEdge=false;
	IsFiber=false;

}

Line::~Line() {
	// TODO Auto-generated destructor stub
}

void Line::UpdateLength()
{
	Length=sqrt(pow(VertexA->x - VertexB->x,2)+pow(VertexA->y - VertexB->y,2));
}

Vertex* Line::GetOtherEnd(Vertex* OneEnd)
{
	if(OneEnd==VertexA)
	{
		return VertexB;
	}
	else if(OneEnd==VertexB)
	{
		return VertexA;
	}
	else
	{
		std::cout << "Line::GetOtherEnd --> VERTEX DOESN'T BELONG TO LINE" << "\n";
		return 0;
	}
}

Triangle* Line::GetOtherSide(Triangle* OneSide)
{
	if(OneSide==TriangleA)
	{
		return TriangleB;
	}
	else if(OneSide==TriangleB)
	{
		return TriangleA;
	}
	else
	{
		std::cout << "Line::GetOtherSide --> TRIANGLE DOESN'T BELONG TO LINE" << "\n";
		return 0;
	}
}

void Line::ConnectVertex(Vertex* vert,char pos)
{
	//This subroutine initializes the corresponding data on both line and vertex object in order to connect them
	//argument pos tells the line whether the vertex is in position A (1) or B (2)

	if(pos=='a')
	{
		VertexA=vert;
	}
	else if(pos=='b')
	{
		VertexB=vert;
	}
	else
	{
		std::cout << "Line::ConnectVertex --> BAD POSITION FOR VERTEX 1 for A, 2 for B" << "\n";
		return;
	}

	std::list<Line*>::const_iterator iit;
	Line* line;
	for(iit=vert->LineList.begin() ; iit!=vert->LineList.end() ; ++iit)
	{
		line=*iit;
		if(line==this)
		{
			std::cout << "Line::ConnectVertex --> ALREADY CONNECTED" << "\n";
			return;
		}
	}
	vert->LineList.push_back(this);
	return;
}

char Line::GetVertexIndex(Vertex* vert)
{
	//this function takes a vertex as argument and tells whether this one is set as position A or B in the Line object
	//(as long as the vertex is actually connected to the line
	if(vert==VertexA)
	{
		return 'a';
	}
	else if (vert==VertexB)
	{
		return 'b';
	}
	else
	{
		std::cout << "Line::GetVertexIndex --> VERTEX NOT CONNECTED TO LINE" << "\n";
		return '0';
	}
}

