/*
 * main.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */


#include <cairo/cairo.h>
#include <cairo/cairo-xlib.h>
#include <X11/Xlib.h>

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include "System.h"
//#include "Vertex.h"
//#include "Junction.h"
//#include "Centre.h"
//#include "Line.h"
//#include "Edge.h"
//#include "Fiber.h"
//#include "Triangle.h"
//#include "Cell.h"

#define SIZEX 500
#define SIZEY 500

///////////////////////////////////////////////////////////////////
void paint(cairo_surface_t *cs, System* my_system)
{
	std::cout << "paint--START" << "\n";
	cairo_t *c;

	std::cout << "paint--1" << "\n";

	c=cairo_create(cs);

	bool draw_vertices=true;
	bool draw_lines=true;
	bool draw_triangles=true;
	//bool draw_centres=true;
	bool draw_origin=false;
	//bool draw_vectors=true;

	float vertex_radius=10.0f;
	float line_thickness=0.5f;
	float triangle_thickness=0.4f;

	float syst_min_x=my_system->x_min;
	//float syst_max_x=my_system->system_x_max;
	float syst_min_y=my_system->y_min;
	//float syst_max_y=my_system->system_y_max;

	float length_x=my_system->length_x;
	float length_y=my_system->length_y;;
	float ratio=length_y/length_x;

	int canvas_x,canvas_y;
	if(ratio>1)
	{
		canvas_x=SIZEY/ratio;
		canvas_y=SIZEY;
	}
	else
	{
		canvas_x=SIZEX;
		canvas_y=SIZEX*ratio;
	}

	std::cout << "paint--2" << "\n";

	//std::cout << "syst dimensions "<< syst_max_x<<" " <<syst_min_x<<" "<< syst_max_y<<" " <<syst_min_y << "\n";
	//std::cout << "length "<< length_x<<" " <<length_y<< "\n";
	//std::cout << "ratio "<< ratio <<" canvas "<< canvas_x <<" "<<canvas_y << "\n";

	cairo_rectangle(c, 0.0, 0.0, canvas_x, canvas_y);
	cairo_set_source_rgb(c, 1.0, 1.0, 1.0);
	cairo_fill(c);

    int draw_x,draw_y;//,cell_radius;
	cairo_set_line_width(c, 2.5);

	std::cout << "paint--3" << "\n";

	if(draw_origin)
	{
		cairo_set_source_rgb(c, 0.0, 0.0, 0.0);
		cairo_set_line_width(c, 5.0);
		draw_x=canvas_x*(0.0f - syst_min_x)/length_x ;
		draw_y=canvas_y-canvas_y*(0.0f - syst_min_y)/length_y ;

		cairo_move_to(c, draw_x, draw_y);

		draw_x=canvas_x*(0.0f - syst_min_x)/length_x ;
		draw_y=canvas_y-canvas_y*(1.0f - syst_min_y)/length_y ;

		cairo_line_to(c, draw_x, draw_y);

		cairo_translate(c, draw_x, draw_y);
		cairo_arc(c, 0, 0, 10, 0, 2 * M_PI);
		cairo_stroke(c);
		cairo_translate(c, -draw_x, -draw_y);


		draw_x=canvas_x*(0.0f - syst_min_x)/length_x ;
		draw_y=canvas_y-canvas_y*(0.0f - syst_min_y)/length_y ;

		cairo_move_to(c, draw_x, draw_y);

		draw_x=canvas_x*(1.0f - syst_min_x)/length_x ;
		draw_y=canvas_y-canvas_y*(0.0f - syst_min_y)/length_y ;

		cairo_line_to(c, draw_x, draw_y);

		cairo_translate(c, draw_x, draw_y);
		cairo_arc(c, 0, 0, 10, 0, 2 * M_PI);
		cairo_stroke(c);
		cairo_translate(c, -draw_x, -draw_y);


	}


	std::cout << "paint--4" << "\n";

	if(draw_vertices)
	{
		//ListElementX<Cell2DCentreX>* cit=my_system->CellCentreList->GetListStart();
		//Cell2DCentreX* cell;
		std::list<Vertex*>::const_iterator vit;
		Vertex* vertex;
		std::cout << "paint--4.1 "<< my_system->VertexList.size() << "\n";
		for(vit=my_system->VertexList.begin() ; vit!=my_system->VertexList.end() ; ++vit)
		{
			std::cout << "paint--4.1.1" << "\n";
			vertex=*vit;
			//vertex=my_system->iterVertexGet();
			std::cout << "paint--4.2" << "\n";
			draw_x=canvas_x*(vertex->x - syst_min_x)/length_x ;
			draw_y=canvas_y-canvas_y*(vertex->y - syst_min_y)/length_y ;
			std::cout << "paint--4.3" << "\n";
			//cell_radius=canvas_x*(0.5f*my_system->std_cell_radius)/length_x;
			//cell_radius=canvas_x*(0.5f*cell->EqSurf)/length_x;
			//cell_radius=canvas_x*(0.5f*cell->CellSurf)/length_x;

			//cell_radius=SIZEX/20;
			//		std::cout << "canvas_x "<< canvas_x<<" length_x " <<length_x << "\n";
			//		std::cout << "cell_radius "<< cell_radius<<" std " <<my_system->std_cell_radius << "\n";
			//		std::cout << "draw_centre "<< draw_x<<" " <<draw_y << "\n";


			cairo_set_source_rgb(c, 1.0, 0.0, 1.0);


			cairo_translate(c, draw_x, draw_y);
			cairo_arc(c, 0, 0, vertex_radius, 0, 2 * M_PI);
			cairo_stroke(c);
			std::cout << "paint--4.4" << "\n";
			//cairo_stroke_preserve(c);

			//cairo_set_source_rgb(c, 0.3, 0.4, 0.6);
			//cairo_fill(c);
			cairo_translate(c, -draw_x, -draw_y);

			std::cout << "paint--4.5" << "\n";
			//cit=my_system->CellCentreList->IteratorNext();
			//cit=cit->next;
		}
	}

	std::cout << "paint--5 "<<my_system->LineList.size() << "\n";

	//draw the lines
	cairo_set_line_width(c, line_thickness);

	if(draw_lines)
	{
		std::list<Line*>::iterator lit;
		Line* line;
		for(lit=my_system->LineList.begin() ; lit!=my_system->LineList.end() ; ++lit)
		{
			std::cout << "paint--5.1" << "\n";
			line=*lit;
			std::cout << "paint--5.2" << "\n";
			draw_x=canvas_x*(line->VertexA->x - syst_min_x)/length_x ;
			draw_y=canvas_y-canvas_y*(line->VertexA->y - syst_min_y)/length_y ;

			if(line->TriangleA==0 || line->TriangleB==0)
			{
				cairo_set_source_rgb(c, 0.0, 1.0, 1.0);
			}
			else
			{
				cairo_set_source_rgb(c, 0.0, 0.0, 1.0);
			}

			cairo_move_to(c, draw_x, draw_y);
			//cairo_set_source_rgb(c, 0.0, 0.0, 1.0);

			draw_x=canvas_x*(line->VertexB->x - syst_min_x)/length_x ;
			draw_y=canvas_y-canvas_y*(line->VertexB->y - syst_min_y)/length_y ;
			cairo_line_to(c, draw_x, draw_y);

			cairo_stroke(c);

			//std::cout << "draw_2 "<< draw_x<<" " <<draw_y << "\n";

			//iit=my_system->CellInteractionList->IteratorNext();
			//iit=iit->next;

		}
	}

	std::cout << "paint--6" << "\n";

	if(draw_triangles)
	{
		cairo_set_line_width(c, triangle_thickness);

		std::list<Triangle*>::const_iterator tit;
		Triangle* tri;
		float xa,ya,xb,yb,xc,yc,x,y;

		std::cout << "paint--6.1 "<< my_system->TriangleList.size() << "\n";

		for(tit=my_system->TriangleList.begin() ; tit!=my_system->TriangleList.end() ; ++tit)
		{
			std::cout << "paint--6.2" << "\n";
			tri=*tit;
			std::cout << "paint--6.3" << "\n";
			//A
			xa=tri->VertexA->x + 0.5f*(tri->CentroidX - tri->VertexA->x);
			ya=tri->VertexA->y + 0.5f*(tri->CentroidY - tri->VertexA->y);

			std::cout << "paint--6.4" << "\n";
			draw_x=0.1f+canvas_x*(xa - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(ya - syst_min_y)/length_y ;

			cairo_move_to(c, draw_x, draw_y);
			cairo_set_source_rgb(c, 0.0, 1.0, 0.0);

			xb=tri->VertexB->x + 0.5f*(tri->CentroidX - tri->VertexB->x);
			yb=tri->VertexB->y + 0.5f*(tri->CentroidY - tri->VertexB->y);

			draw_x=0.1f+canvas_x*(xb - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(yb - syst_min_y)/length_y ;
			cairo_line_to(c, draw_x, draw_y);
			//B
			//draw_x=0.1f+canvas_x*(xb - syst_min_x)/length_x ;
			//draw_y=0.1f+canvas_y-canvas_y*(yb - syst_min_y)/length_y ;


			cairo_move_to(c, draw_x, draw_y);
			cairo_set_source_rgb(c, 0.0, 1.0, 0.0);

			xc=tri->VertexC->x + 0.5f*(tri->CentroidX - tri->VertexC->x);
			yc=tri->VertexC->y + 0.5f*(tri->CentroidY - tri->VertexC->y);

			draw_x=0.1f+canvas_x*(xc - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(yc - syst_min_y)/length_y ;
			cairo_line_to(c, draw_x, draw_y);
			//C
			//draw_x=0.1f+canvas_x*(xc - syst_min_x)/length_x ;
			//draw_y=0.1f+canvas_y-canvas_y*(yc - syst_min_y)/length_y ;

			cairo_move_to(c, draw_x, draw_y);
			cairo_set_source_rgb(c, 0.0, 1.0, 0.0);

			draw_x=0.1f+canvas_x*(xa - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(ya - syst_min_y)/length_y ;
			cairo_line_to(c, draw_x, draw_y);

			cairo_stroke(c);

			//we mark the orientation of the edges

			x=xa+0.75f*(xb-xa);
			y=ya+0.75f*(yb-ya);
			draw_x=0.1f+canvas_x*(x - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(y - syst_min_y)/length_y ;
			cairo_translate(c, draw_x, draw_y);
			cairo_arc(c, 0, 0, 5, 0, 2 * M_PI);
			cairo_stroke(c);
			cairo_translate(c, -draw_x, -draw_y);

			x=xb+0.75f*(xc-xb);
			y=yb+0.75f*(yc-yb);
			draw_x=0.1f+canvas_x*(x - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(y - syst_min_y)/length_y ;
			cairo_translate(c, draw_x, draw_y);
			cairo_arc(c, 0, 0, 5, 0, 2 * M_PI);
			cairo_stroke(c);
			cairo_translate(c, -draw_x, -draw_y);

			x=xc+0.75f*(xa-xc);
			y=yc+0.75f*(ya-yc);
			draw_x=0.1f+canvas_x*(x - syst_min_x)/length_x ;
			draw_y=0.1f+canvas_y-canvas_y*(y - syst_min_y)/length_y ;
			cairo_translate(c, draw_x, draw_y);
			cairo_arc(c, 0, 0, 5, 0, 2 * M_PI);
			cairo_stroke(c);
			cairo_translate(c, -draw_x, -draw_y);


			//std::cout << "draw_2 "<< draw_x<<" " <<draw_y << "\n";

			//iit=my_system->CellInteractionList->IteratorNext();
			//tit=tit->next;

		}
	}

	std::cout << "paint--END" << "\n";

}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
void showxlib(System* my_system)
{
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	cairo_surface_t *cs;

	std::cout << "showxlib--START" << "\n";

	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		return ;
	}

	std::cout << "showxlib--1" << "\n";

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	//float syst_min_x=my_system->system_x_min;
	//float syst_max_x=my_system->system_x_max;
	//float syst_min_y=my_system->system_y_min;
	//float syst_max_y=my_system->system_y_max;

	//float length_x=syst_max_x-syst_min_x;
	//float length_y=syst_max_y-syst_min_y;
	//float ratio=length_y/length_x;

	std::cout << "showxlib--2" << "\n";

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0,
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	std::cout << "showxlib--3" << "\n";

	XStoreName(dpy, win, "VerteX");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);

	std::cout << "showxlib--4" << "\n";

	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	std::cout << "showxlib--5" << "\n";

	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs, my_system);
		} else if(e.type==ButtonPress) break;
	}

	std::cout << "showxlib--6" << "\n";

	cairo_surface_destroy(cs);
	XCloseDisplay(dpy);

	std::cout << "showxlib--END" << "\n";
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//void InitialConditionsHexagonalGrid(System* System, int lx, int ly, float cell_separation)
//{
//	//Sets the initial spatial distribution of cells
//	//Rectangular grid of cells distributed hexagonally
//
//	Cell2DCentreX* new_cell;
//	float disty=sqrt(pow(cell_separation,2)-pow(0.5f*cell_separation,2));
//
//	float cell_cortical_tension=1.0f;
//	float cell_turgency=1.0f;
//
//
//	//System->std_cell_radius=1.0f;
//
//    float cellx,celly;
//	for(int i=1 ; i<=ly ; i++)
//	{
//		for(int j=1 ; j<=lx ; j++)
//		{
//			if(i%2==0){ cellx=cell_separation*(j-1); }
//			else      { cellx=0.5f*cell_separation+cell_separation*(j-1); }
//			celly=disty*(i-1);
//
//			new_cell=System->NewCell(cellx,celly);
//
//			//calculate cell equilibrium surface based on the initial cell separation
//			float h;
//			h=sqrt(pow(cell_separation,2)-pow(cell_separation*0.5,2));
//			//new_cell->EqSurf=cell_separation*h;
//			new_cell->CorticalTensionCoef=cell_cortical_tension;
//			new_cell->TurgencyCoef=cell_turgency;
//			new_cell->EqSurf=cell_separation*h;
//
//			if(i==1 || i==ly || j==1 || j==lx) //we already define the borders of the system
//			{
//				new_cell->IsBorder=true;
//			}
//
//		}
//	}
//}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//void InitialConditionsHexagonalGridSymmetricBorders(SystemX* System, int lx, int ly, float cell_separation)
//{
//	//Sets the initial spatial distribution of cells
//	//Rectangular grid of cells distributed hexagonally
//
//	Cell2DCentreX* new_cell;
//	float disty=sqrt(pow(cell_separation,2)-pow(0.5f*cell_separation,2));
//
//	float cell_cortical_tension=1.0f;
//	float cell_turgency=5.0f;
//
//
//	int lrow;
//
//	//System->std_cell_radius=1.0f;
//
//    float cellx,celly;
//	for(int i=1 ; i<=ly ; i++)
//	{
//		if(i%2!=0){lrow=lx-1;}else{lrow=lx;}
//		for(int j=1 ; j<=lrow ; j++)
//		{
//			if(i%2!=0){ cellx=cell_separation+cell_separation*(j-1); }
//			else      { cellx=0.5f*cell_separation+cell_separation*(j-1); }
//			celly=disty*(i-1);
//
//			new_cell=System->NewCell(cellx,celly);
//
//			//calculate cell equilibrium surface based on the initial cell separation
//			float h;
//			h=sqrt(pow(cell_separation,2)-pow(cell_separation*0.5,2));
//			//new_cell->EqSurf=cell_separation*h;
//			new_cell->CorticalTensionCoef=cell_cortical_tension;
//			new_cell->TurgencyCoef=cell_turgency;
//			new_cell->EqSurf=cell_separation*h;
//
//			if(i==1 || i==ly || j==1 || j==lrow) //we already define the borders of the system
//			{
//				new_cell->IsBorder=true;
//
//				if((i==1 || i==ly) && (j==1 || j==lrow))
//				{
//					new_cell->EqSurf=(2.0f/6.0f)*cell_separation*h;
//				}
//				else if (i==1 || i==ly)
//				{
//					new_cell->EqSurf=(3.0f/6.0f)*cell_separation*h;
//				}
//				else if (j==1 || j==lrow)
//				{
//					if(i%2==0)
//					{
//						new_cell->EqSurf=(2.0f/6.0f)*cell_separation*h;
//					}
//					else
//					{
//						new_cell->EqSurf=(4.0f/6.0f)*cell_separation*h;
//					}
//				}
//			}
//
//
//		}
//	}
//}
///////////////////////////////////////////////////////////////////

//void InitialConditionsSingleCell(System* my_system)
//{
//	//Sets the initial spatial distribution of cells
//	//Rectangular grid of cells distributed hexagonally
//
//
//	std::cout<<"InitialConditionsSingleCell--START\n";
//
//	//float vertex_distance=std_cell_radius;
//
//	Cell* new_cell=new Cell;
//
//	my_system->CellList.push_back(new_cell);
//
//	//float disty=sqrt(pow(vertex_distance,2)-pow(0.5f*vertex_distance,2));
//
//	//float cell_cortical_tension=1.0f;
//	//float cell_turgency=1.0f;
//
//
//	//System->std_cell_radius=1.0f;
//
//	//int lx=3;
//	//int ly=3;
//
//	std::cout<<"InitialConditionsSingleCell--BLUILD THE MESH\n";
//
//	//Creating the cell junctions
//	Junction* ja=new Junction(-0.5f,-0.5f);
//	my_system->VertexList.push_back(ja);
//	new_cell->JunctionList.push_back(ja);
//	Junction* jb=new Junction(-0.5f,0.5f);
//	my_system->VertexList.push_back(jb);
//	new_cell->JunctionList.push_back(jb);
//	Junction* jc=new Junction(0.5f,0.5f);
//	my_system->VertexList.push_back(jc);
//	new_cell->JunctionList.push_back(jc);
//	Junction* jd=new Junction(0.5f,-0.5f);
//	my_system->VertexList.push_back(jd);
//	new_cell->JunctionList.push_back(jd);
//	//Creating the cell Centre
//	Centre* ca= new Centre(0.0f,0.0f);
//	my_system->VertexList.push_back(ca);
//	new_cell->CellCentre=ca;
//
//	//Now we connect with lines
//	//Edges
//	Edge* new_edge= new Edge(ja,jb);
//	new_cell->EdgeList.push_back(new_edge);
//	my_system->LineList.push_back(new_edge);
//	new_edge= new Edge(jb,jc);
//	new_cell->EdgeList.push_back(new_edge);
//	my_system->LineList.push_back(new_edge);
//	new_edge= new Edge(jc,jd);
//	new_cell->EdgeList.push_back(new_edge);
//	my_system->LineList.push_back(new_edge);
//	new_edge= new Edge(jd,ja);
//	new_cell->EdgeList.push_back(new_edge);
//	my_system->LineList.push_back(new_edge);
//	//Fibers
//	Fiber* new_fiber= new Fiber(ja,ca);
//	new_cell->FiberList.push_back(new_fiber);
//	my_system->LineList.push_back(new_edge);
//	new_fiber= new Fiber(jb,ca);
//	new_cell->FiberList.push_back(new_fiber);
//	my_system->LineList.push_back(new_edge);
//	new_fiber= new Fiber(jc,ca);
//	new_cell->FiberList.push_back(new_fiber);
//	my_system->LineList.push_back(new_edge);
//	new_fiber= new Fiber(jd,ca);
//	new_cell->FiberList.push_back(new_fiber);
//	my_system->LineList.push_back(new_edge);
//
//	std::cout<<"InitialConditionsSingleCell--DONE WITH THE MESH\n";
//
//	//THE MESH IS CONSTRUCTED, NOW LET'S BUILD THE TRIANGULATION
//
//	my_system->NeighborhoodTriangulation();
//	my_system->UpdateSystemDimensions();
//
//	std::cout<<"Initial conditions constructed \n";
//
//}



///////////////////////////////////////////////////////////////////
int main (int argc, char** argv)
{

//	std::cout << "This program creates a System with a number of 2D cells and stores them in a linked list" << "\n";

	//int number_of_cells=20;


	System* MySystem=new System();
	//System* MySystem=new System();

	//rows and columns of cells for the initial conditions
	//int ic_lx=1; int ic_ly=1;
	//initialize system parameters
	MySystem->std_cell_radius=1.5f;
	MySystem->GabrielScreeningCoefficient=1.00f;
	MySystem->EulerDelta=0.01f;
	//System->IsotropicOuterForceModulus=2.5f;


    int length_time_interval=1;
    int n_time_intervals=1;


	//Setting the initial conditions and initializing
	//InitialConditionsHexagonalGridSymmetricBorders(System,ic_lx,ic_ly,1.0f);
	MySystem->Init();

	//InitialConditionsSingleCell(MySystem);
	//MySystem->InitialConditionsSingleCell();

	std::cout << "System constructed" << "\n";


	//my_system time progress is calculated every length_time_interval and displayed, n_time_interval times
	//for (int i=1 ; i<=n_time_intervals ; i++)
	//{
		MySystem->TimeIterator(length_time_interval);
		//std::cout << "CUT1" << "\n";
		showxlib(MySystem);
	//}
	std::cout << "PROGRAM--DONE" << "\n";

	std::cout << "TEST PRINT -- We're done here" << "\n";

	return 0;
}


