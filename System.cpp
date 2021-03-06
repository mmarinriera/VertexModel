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


    Line* linetemp;
    Line* line;
	std::list<Line*>::const_iterator lit;
	std::list<Line*>::const_iterator lita;
	std::list<Line*>::const_iterator litb;
    Vertex* vert_a;
    Vertex* vert_b;
    Vertex* vert_c;
    Vertex* vert_opposite;
    Vertex* vert_temp;
    Vertex* vert_lead;
    Vertex* vert_tail;
    Vertex* vert_check;
	Triangle* tri_adjacent;
	Triangle* tritemp;
	std::list<Triangle*>::const_iterator tit;
	bool found;
	bool trifound;


	//Starting creating the first triangle on an arbitrary position (first interaction on the list)

	std::cout <<"starting with the first triangle\n";

	line=LineList.front();
//	std::cout <<"CUT1\n";
	vert_a=line->VertexA ; vert_b=line->VertexB;
	//lita=vert_a->InteractionList->GetListStart();
//	std::cout <<"CUT2\n";
	found=false;
//	std::cout <<"First triangle loop\n";
	for (lita = vert_a->LineList.begin(); lita != vert_a->LineList.end(); ++lita)
	{
		linetemp=*lita;
		vert_temp=linetemp->GetOtherEnd(vert_a);

		for (litb = vert_b->LineList.begin(); litb != vert_b->LineList.end(); ++litb)
		{
			linetemp=*litb;
			vert_c=linetemp->GetOtherEnd(vert_b);
			if(vert_c==vert_temp)
			{
				found=true;
				break;
			}
		}
		if(found){break;}
	}
//	std::cout <<"out of first triangle loop \n";//"<< vert_a->tag <<" "<< vert_b->tag <<" "<< vert_c->tag <<"\n";

    Triangle* tri= new Triangle(vert_a,vert_b,vert_c);
    //tri->EdgeAB->TriangleA=tri;
    //tri->EdgeBC->TriangleA=tri;
    //tri->EdgeCA->TriangleA=tri;

    linetemp=tri->LineAB;
    if(tri->GetLead(vert_a,vert_b)==linetemp->VertexA)
    {linetemp->TriangleA=tri;}
    else
    {linetemp->TriangleB=tri;}

    linetemp=tri->LineBC;
    if(tri->GetLead(vert_b,vert_c)==linetemp->VertexA)
    {linetemp->TriangleA=tri;}
    else
    {linetemp->TriangleB=tri;}

    linetemp=tri->LineCA;
    if(tri->GetLead(vert_c,vert_a)==linetemp->VertexA)
    {linetemp->TriangleA=tri;}
    else
    {linetemp->TriangleB=tri;}

    TriangleList.push_back(tri);

//	std::cout <<"first triangle made and listed"<<"\n";
    ///////////////////////////////////////////

    list2->push_back(tri->LineAB);
    list2->push_back(tri->LineBC);
    list2->push_back(tri->LineCA);


//	std::cout <<"initializing list2 now entering main loop"<<"\n";

	//this is a kind of crappy queue data structure using two switchable linked lists
    //objects processed in the first list create more objects to be processed that are stored in the second
    //then the first list is cleared and the lists are switched (the former first will act as second and the new objects will be processed as if
    //they were on the first list
    while(list2->size()!=0)
	{
//		std::cout <<"main loop START"<<"\n";
		//switching lists
		list1->clear();
		temp=list1;
		list1=list2;
		list2=temp;
//		std::cout <<"lists switched"<<"\n";
		//processing items on list1
//		std::cout <<"entering list loop"<<"\n";
		for(lit=list1->begin(); lit != list1->end() ; ++lit)
		{
//			std::cout <<"starting list loop"<<"\n";
			//we go edge by edge constructing new triangles if possible
			found=false;
			line=*lit;
//			std::cout <<"get lines"<<"\n";
			vert_a=line->VertexA;
			vert_b=line->VertexB;
//			std::cout <<"get vertices"<<"\n";
			tri_adjacent=line->TriangleA;
			if(tri_adjacent==0){tri_adjacent=line->TriangleB;}
//			std::cout <<"get adjecent"<<"\n";
			vert_lead=tri_adjacent->GetLead(vert_a,vert_b);
			if(vert_lead==vert_a){vert_tail=vert_b;}else{vert_tail=vert_a;}
//			std::cout <<"got lead"<<"\n";
			vert_opposite=tri_adjacent->GetOppositeVertex(line);

			//std::cout <<"building triangle from edge "<< vert_a->tag <<" "<< vert_b->tag <<" into loop a"<<"\n";

			for(lita=vert_a->LineList.begin(); lita != vert_a->LineList.end() ; ++lita)
			{
				linetemp=*lita;
				vert_temp=linetemp->GetOtherEnd(vert_a);
				//std::cout <<"checking from vert_a: cell "<<vert_temp->tag<<"\n";
				if(vert_temp==vert_opposite || vert_temp==vert_b){continue;}

				for(litb=vert_b->LineList.begin(); litb != vert_b->LineList.end() ; ++litb)
				{
					linetemp=*litb;
					vert_c=linetemp->GetOtherEnd(vert_b);
					//std::cout <<"checking from vert_a: cell "<<vert_temp->tag<<" checking from vert_b: cell "<<vert_c->tag<<"\n";
					if(vert_c==vert_opposite || vert_c==vert_a){continue;}
					if(vert_temp==vert_c)
					{
						//we found a common neighbor
						found=true;

						//check if the triangle already exists
//						std::cout <<"we found a match, now check whether the triangle already exists"<<"\n";

						trifound=false;
						for(tit=TriangleList.begin() ; tit != TriangleList.end() ; ++tit)
						{
							tritemp=*tit;

							//std::cout <<"checking triangle "<<tritemp->CellA->tag<<" "<<tritemp->CellB->tag<<" "<<tritemp->CellC->tag<<" "<<"\n";

							vert_check=tritemp->GetNextVertex(vert_lead);

							//if(vert_check!=0){std::cout <<"entering vert_lead "<<vert_lead->tag<<" expecting vert_tail "<<vert_tail->tag<<" got "<<vert_check->tag<<"\n";}
							//else{std::cout <<"got nothing, vert_lead doesn't belong to the triangle"<<"\n";}

							if(vert_check==vert_tail)
							{
								//the triangle already exist, don't create the triangle
								trifound=true;
								break;
							}

						}
//						std::cout <<"out of the triangle search loop"<<"\n";

						if(!(trifound))
						{
//							std::cout <<"it is a new triangle, creating \n";



						    tri= new Triangle(vert_lead,vert_tail,vert_c);

						    linetemp=tri->LineAB;
						    if(tri->GetLead(vert_lead,vert_tail)==linetemp->VertexA)
						    {linetemp->TriangleA=tri;}
						    else
						    {linetemp->TriangleB=tri;}
						    linetemp=tri->LineBC;
						    if(tri->GetLead(vert_tail,vert_c)==linetemp->VertexA)
						    {linetemp->TriangleA=tri;}
						    else
						    {linetemp->TriangleB=tri;}
						    linetemp=tri->LineCA;
						    if(tri->GetLead(vert_c,vert_lead)==linetemp->VertexA)
						    {linetemp->TriangleA=tri;}
						    else
						    {linetemp->TriangleB=tri;}

						    TriangleList.push_back(tri);

						    list2->push_back(tri->LineBC);
						    list2->push_back(tri->LineCA);

//						    std::cout <<"triangle created and listed"<<"\n";

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
//		std::cout << "prehola \n";
		vertex=*vit;
		//std::cout << "Cell tag "<< it->tag << " cell x "<< it->x << " cell y "<< it->y << "\n";
//		std::cout << "hola \n";
		if(vertex->x < x_min){ x_min=vertex->x;}
		if(vertex->x > x_max){ x_max=vertex->x;}
		if(vertex->y < y_min){ y_min=vertex->y;}
		if(vertex->y > y_max){ y_max=vertex->y;}
//		std::cout << "posthola \n";

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
