/*
 * System.cpp
 *
 *  Created on: 22.7.2016
 *      Author: mmriera
 */

#include "System.h"

#include<cmath>

System::System() {

	CellNumber=0;
	x_min=0.0f;
	x_max=0.0f;
	y_min=0.0f;
	y_max=0.0f;
	length_x=0.0f;
	length_y=0.0f;

	GabrielScreeningCoefficient=0.0f; //this is used for the Gabriel screening
	EulerDelta=0.0f;

	std_cell_radius=0.0f;

	//SpaceGrid=0; //we cannot construct it until we have a proper list of cells
}

System::~System() {
	// TODO Auto-generated destructor stub
	//delete SpaceGrid;
}

///////////////////////////////////////////////////////////////////
void System::Init()
{
	//once the cells have been put into the system, some data structures need to be initialized
	std::cout <<"SystemInit::start with this shit\n";

	//Dimensions of the system (assuming only the position of existing cells define the boundaries of the system)
	//UpdateSystemDimensions();
	//std::cout <<"SystemInit::UpdateSystemDimensions---DONE\n";

	//The spatial grid container for cells
	//SpaceGrid=new SpaceGridContainer(VertexList,x_min,x_max,y_min,y_max,std_cell_radius);
	//std::cout <<"SystemInit::Construct CellCentreSpaceGrid---DONE \n";

	//Calculate cell neighborhoods
	//NeighborhoodBuildProximity();
	//std::cout <<"SystemInit::Neighborhood built by proximity---DONE\n";

	//neighborhood refinement: Gabriel graph
	//NeighborhoodGabrielRefinement();
	//std::cout <<"SystemXInit::Neighborhood refinement by Gabriel---DONE\n";

	//Create triangles from mesh
	//NeighborhoodTriangulation();
	//std::cout <<"SystemInit::Triangulation---DONE\n";

	//Set Some Initial Conditions
	InitialConditionsSingleCell();
	//std::cout <<"SystemInit::InitialConditions Routine ---DONE\n";

	//Dimensions of the system (assuming only the position of existing cells define the boundaries of the system)
	UpdateSystemDimensions();
	//std::cout <<"SystemInit::UpdateSystemDimensions---DONE\n";
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
void System::NeighborhoodTriangulation()
{
	//triangle vertices need to follow a clockwise order when constructed (ordering of new triangles can be guessed from contiguous ones (the shared edge will go on the opposite direction)
	//develop a triangle function that given a triangle vertex returns the following
	//method to quickly identify existing triangles. If you suspect that a triangle already exists in the position you want to build a triangle, ask to the triangle which vertex comes next
	//to a given vertex, if the second vertex coincides with the triangle you want to form then it already exists. (will probably require more work on the data structures)

	//Needs to be given the vertices of the first triangle on a clock-wise order
	std::list<Line*>* list1=new std::list<Line*>;
	std::list<Line*>* list2=new std::list<Line*>;
	std::list<Line*>* temp;


//    Cell2DInteractionX* intemp;
//    ListElementX<Cell2DInteractionX>* iit;
//    ListElementX<Cell2DInteractionX>* nita;
//    ListElementX<Cell2DInteractionX>* nitb;
//    Cell2DInteractionX* inte;
//    Cell2DCentreX* cella;
//    Cell2DCentreX* cellb;
//	Cell2DCentreX* cellc;
//	Cell2DCentreX* copposite;
//	Cell2DCentreX* ctemp;
//	Cell2DCentreX* clead;
//	Cell2DCentreX* ctail;
//	Cell2DCentreX* ccheck;
//	Cell2DTriangleX* tri_adjacent;
//	Cell2DTriangleX* tritemp;
//	bool found;
//	ListElementX<Cell2DTriangleX>* tit;
//	bool trifound;

    Line* intemp;
    Line* inte;
	std::list<Line*>::const_iterator iit;
	std::list<Line*>::const_iterator nita;
	std::list<Line*>::const_iterator nitb;
    Vertex* cella;
    Vertex* cellb;
    Vertex* cellc;
    Vertex* copposite;
    Vertex* ctemp;
    Vertex* clead;
    Vertex* ctail;
    Vertex* ccheck;
	Triangle* tri_adjacent;
	Triangle* tritemp;
	std::list<Triangle*>::const_iterator tit;
	bool found;
	bool trifound;


	//Starting creating the first triangle on an arbitrary position (first interaction on the list)

	std::cout <<"starting with the first triangle\n";

	inte=LineList.front();
	std::cout <<"CUT1\n";
	cella=inte->VertexA ; cellb=inte->VertexB;
	//nita=cella->InteractionList->GetListStart();
	std::cout <<"CUT2\n";
	found=false;
	std::cout <<"First triangle loop\n";
	for (nita = cella->LineList.begin(); nita != cella->LineList.end(); ++nita)
	{
		intemp=*nita;
		ctemp=intemp->GetOtherEnd(cella);

		for (nitb = cellb->LineList.begin(); nitb != cellb->LineList.end(); ++nitb)
		{
			intemp=*nitb;
			cellc=intemp->GetOtherEnd(cellb);
			if(cellc==ctemp)
			{
				found=true;
				break;
			}
		}
		if(found){break;}
	}
	std::cout <<"out of first triangle loop \n";//"<< cella->tag <<" "<< cellb->tag <<" "<< cellc->tag <<"\n";

    Triangle* tri= new Triangle(cella,cellb,cellc);
    //tri->EdgeAB->TriangleA=tri;
    //tri->EdgeBC->TriangleA=tri;
    //tri->EdgeCA->TriangleA=tri;

    intemp=tri->LineAB;
    if(tri->GetLead(cella,cellb)==intemp->VertexA)
    {intemp->TriangleA=tri;}
    else
    {intemp->TriangleB=tri;}

    intemp=tri->LineBC;
    if(tri->GetLead(cellb,cellc)==intemp->VertexA)
    {intemp->TriangleA=tri;}
    else
    {intemp->TriangleB=tri;}

    intemp=tri->LineCA;
    if(tri->GetLead(cellc,cella)==intemp->VertexA)
    {intemp->TriangleA=tri;}
    else
    {intemp->TriangleB=tri;}

    TriangleList.push_back(tri);

	std::cout <<"first triangle made and listed"<<"\n";
    ///////////////////////////////////////////

    list2->push_back(tri->LineAB);
    list2->push_back(tri->LineBC);
    list2->push_back(tri->LineCA);


	std::cout <<"initializing list2 now entering main loop"<<"\n";

	//this is a kind of crappy queue data structure using two switchable linked lists
    //objects processed in the first list create more objects to be processed that are stored in the second
    //then the first list is cleared and the lists are switched (the former first will act as second and the new objects will be processed as if
    //they were on the first list
    while(list2->size()!=0)
	{
		std::cout <<"main loop START"<<"\n";
		//switching lists
		list1->clear();
		temp=list1;
		list1=list2;
		list2=temp;
		std::cout <<"lists switched"<<"\n";
		//processing items on list1
		std::cout <<"entering list loop"<<"\n";
		for(iit=list1->begin(); iit != list1->end() ; ++iit)
		{
			std::cout <<"starting list loop"<<"\n";
			//we go edge by edge constructing new triangles if possible
			found=false;
			inte=*iit;
			std::cout <<"get interaction"<<"\n";
			cella=inte->VertexA;
			cellb=inte->VertexB;
			std::cout <<"get cells"<<"\n";
			tri_adjacent=inte->TriangleA;
			if(tri_adjacent==0){tri_adjacent=inte->TriangleB;}
			std::cout <<"get adjecent"<<"\n";
			clead=tri_adjacent->GetLead(cella,cellb);
			if(clead==cella){ctail=cellb;}else{ctail=cella;}
			std::cout <<"got lead"<<"\n";
			copposite=tri_adjacent->GetOppositeVertex(inte);

			//std::cout <<"building triangle from edge "<< cella->tag <<" "<< cellb->tag <<" into loop a"<<"\n";

			for(nita=cella->LineList.begin(); nita != cella->LineList.end() ; ++nita)
			{
				intemp=*nita;
				ctemp=intemp->GetOtherEnd(cella);
				//std::cout <<"checking from cella: cell "<<ctemp->tag<<"\n";
				if(ctemp==copposite || ctemp==cellb){continue;}

				for(nitb=cellb->LineList.begin(); nitb != cellb->LineList.end() ; ++nitb)
				{
					intemp=*nitb;
					cellc=intemp->GetOtherEnd(cellb);
					//std::cout <<"checking from cella: cell "<<ctemp->tag<<" checking from cellb: cell "<<cellc->tag<<"\n";
					if(cellc==copposite || cellc==cella){continue;}
					if(ctemp==cellc)
					{
						//we found a common neighbor
						found=true;

						//check if the triangle already exists
						std::cout <<"we found a match, now check whether the triangle already exists"<<"\n";

						trifound=false;
						for(tit=TriangleList.begin() ; tit != TriangleList.end() ; ++tit)
						{
							tritemp=*tit;

							//std::cout <<"checking triangle "<<tritemp->CellA->tag<<" "<<tritemp->CellB->tag<<" "<<tritemp->CellC->tag<<" "<<"\n";

							ccheck=tritemp->GetNextVertex(clead);

							//if(ccheck!=0){std::cout <<"entering clead "<<clead->tag<<" expecting ctail "<<ctail->tag<<" got "<<ccheck->tag<<"\n";}
							//else{std::cout <<"got nothing, clead doesn't belong to the triangle"<<"\n";}

							if(ccheck==ctail)
							{
								//the triangle already exist, don't create the triangle
								trifound=true;
								break;
							}

						}
						std::cout <<"out of the triangle search loop"<<"\n";

						if(!(trifound))
						{
							std::cout <<"it is a new triangle, creating \n";



						    tri= new Triangle(clead,ctail,cellc);

						    intemp=tri->LineAB;
						    if(tri->GetLead(clead,ctail)==intemp->VertexA)
						    {intemp->TriangleA=tri;}
						    else
						    {intemp->TriangleB=tri;}
						    intemp=tri->LineBC;
						    if(tri->GetLead(ctail,cellc)==intemp->VertexA)
						    {intemp->TriangleA=tri;}
						    else
						    {intemp->TriangleB=tri;}
						    intemp=tri->LineCA;
						    if(tri->GetLead(cellc,clead)==intemp->VertexA)
						    {intemp->TriangleA=tri;}
						    else
						    {intemp->TriangleB=tri;}

						    TriangleList.push_back(tri);

						    list2->push_back(tri->LineBC);
						    list2->push_back(tri->LineCA);

						    std::cout <<"triangle created and listed"<<"\n";

						}
						break;

					}
					if(found){break;}
				}
				if(found){break;}
			}
		}
	}


}
////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

//Cell2DCentreX* SystemX::NewCell(float x, float y)
//{
//	cell_number++;
//	Cell2DCentreX* temp= new Cell2DCentreX(x,y,cell_number);
//	CellCentreList->InsertItem(temp);
//	return temp;
//}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
void System::UpdateSystemDimensions()
{
	x_min=10000000.0f;
	x_max=-10000000.0f;
	y_min=10000000.0f;
	y_max=-10000000.0f;


	//look for the maximum dimensions of the system

	std::list<Vertex*>::const_iterator vit;
	Vertex* vertex;
	for(vit = VertexList.begin() ; vit !=VertexList.end() ; ++vit)
	{
		std::cout << "prehola \n";
		vertex=*vit;
		//std::cout << "Cell tag "<< it->tag << " cell x "<< it->x << " cell y "<< it->y << "\n";
		std::cout << "hola \n";
		if(vertex->x < x_min){ x_min=vertex->x;}
		if(vertex->x > x_max){ x_max=vertex->x;}
		if(vertex->y < y_min){ y_min=vertex->y;}
		if(vertex->y > y_max){ y_max=vertex->y;}
		std::cout << "posthola \n";

	}
	x_min=x_min-0.5f*std_cell_radius;
	x_max=x_max+0.5f*std_cell_radius;
	y_min=y_min-0.5f*std_cell_radius;
	y_max=y_max+0.5f*std_cell_radius;
	length_x=x_max-x_min;
	length_y=y_max-y_min;

	//std::cout << "Dimensions of the system minx "<< system_x_min << " maxx "<< system_x_max << " miny "<< system_y_min<<" maxy "<<system_y_max << "\n";

}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
void System::MechSolver()
{

}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
void System::TimeIterator(int n_steps)
{

	for (int iter=1 ; iter<=n_steps ; iter++)
	{
		//STUFF THAT NEEDS TO BE INITIALIZED EACH ITERATION
		//DisplayVectorList->MakeEmpty();

		//PUT SOLVERS HERE
		MechSolver();

		//std::cout<<"the tension applied on the system boundaries creates an assymetry that makes the system rotate, that's because the system is not symmetrical :( \n";

		///////////////////
		//PUT UPDATERS HERE

		//neighborhood calculations


		UpdateSystemDimensions();

		///////////////////
	}
}
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////

void System::InitialConditionsSingleCell()
{
	//Sets the initial spatial distribution of cells
	//Rectangular grid of cells distributed hexagonally


	std::cout<<"InitialConditionsSingleCell--START\n";

	//float vertex_distance=std_cell_radius;

	Cell* new_cell=new Cell;

	CellList.push_back(new_cell);

	//float disty=sqrt(pow(vertex_distance,2)-pow(0.5f*vertex_distance,2));

	//float cell_cortical_tension=1.0f;
	//float cell_turgency=1.0f;


	//System->std_cell_radius=1.0f;

	//int lx=3;
	//int ly=3;

	std::cout<<"InitialConditionsSingleCell--BLUILD THE MESH\n";

	//Creating the cell junctions
	Junction* ja=new Junction(-0.5f,-0.5f);
	VertexList.push_back(ja);
	new_cell->JunctionList.push_back(ja);
	Junction* jb=new Junction(-0.5f,0.5f);
	VertexList.push_back(jb);
	new_cell->JunctionList.push_back(jb);
	Junction* jc=new Junction(0.5f,0.5f);
	VertexList.push_back(jc);
	new_cell->JunctionList.push_back(jc);
	Junction* jd=new Junction(0.5f,-0.5f);
	VertexList.push_back(jd);
	new_cell->JunctionList.push_back(jd);
	//Creating the cell Centre
	Centre* ca= new Centre(0.0f,0.0f);
	VertexList.push_back(ca);
	new_cell->CellCentre=ca;

	//Now we connect with lines
	//Edges
	Edge* new_edge= new Edge(ja,jb);
	new_cell->EdgeList.push_back(new_edge);
	LineList.push_back(new_edge);
	new_edge= new Edge(jb,jc);
	new_cell->EdgeList.push_back(new_edge);
	LineList.push_back(new_edge);
	new_edge= new Edge(jc,jd);
	new_cell->EdgeList.push_back(new_edge);
	LineList.push_back(new_edge);
	new_edge= new Edge(jd,ja);
	new_cell->EdgeList.push_back(new_edge);
	LineList.push_back(new_edge);
	//Fibers
	Fiber* new_fiber= new Fiber(ja,ca);
	new_cell->FiberList.push_back(new_fiber);
	LineList.push_back(new_fiber);
	new_fiber= new Fiber(jb,ca);
	new_cell->FiberList.push_back(new_fiber);
	LineList.push_back(new_fiber);
	new_fiber= new Fiber(jc,ca);
	new_cell->FiberList.push_back(new_fiber);
	LineList.push_back(new_fiber);
	new_fiber= new Fiber(jd,ca);
	new_cell->FiberList.push_back(new_fiber);
	LineList.push_back(new_fiber);


	std::cout<<"InitialConditionsSingleCell--DONE WITH THE MESH\n";

	//THE MESH IS CONSTRUCTED, NOW LET'S BUILD THE TRIANGULATION

	NeighborhoodTriangulation();

	std::cout<<"Initial conditions constructed \n";

}
///////////////////////////////////////////////////////////////////
