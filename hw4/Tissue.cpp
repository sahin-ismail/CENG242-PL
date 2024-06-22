#include "Tissue.h"

using namespace std;

#define EPSILON 0.01



		/*********************************************************************
		*									Constructor
		*
		*/
		Tissue::Tissue(){

		}
		/*********************************************************************
		*									Constructor
		*
		* The first @param is the minimum x border
		* The second @param is the maximum x border
		* The third @param is the minimum y border
		* The fourth @param is the maximum y border
		* The tissue is the region residing among those coordinates.
		*/
		Tissue::Tissue(float a, float b, float c, float d){
			this->min_x = a;
			this->max_x = b;
			this->min_y = c;
			this->max_y = d;   

		}
		/*********************************************************************
		*								Copy Constructor
		*
		* Shallow copy
		*/
		Tissue::Tissue(const Tissue& rhs){
			this->min_x = rhs.min_x;
			this->max_x = rhs.max_x;
			this->min_y = rhs.min_y;
			this->max_y = rhs.max_y;  
		}
		/*********************************************************************
		*									Destructor
		*
		*/
		Tissue::~Tissue(){

		}
		/*********************************************************************
		*									GetCoordinates
		*
		* @return the coordinates of minimum x border, maximum x border,
		  minimum y border and maximum y border in an array with the stated
			order.
		*/
		float* Tissue::GetCoordinates(){
			float* arr = new float[4];
			arr[0] = this->min_x;
			arr[1] = this->max_x;
			arr[2] = this->min_y;
			arr[3] = this->max_y;
			return arr;
		}
		/*********************************************************************
		*									AddCell
		*
		* Adds the actual reference of the cell given in the @param to storage
		  of cells belonging to this Tissue object.
		*/
		void Tissue::AddCell(Cell& rhs){
			this->c.push_back(new Cell(rhs));

		}
		/*********************************************************************
		*									RemoveCell
		*
		* Deletes the cell given in the @param and removes it from the storage
		  of cells belonging to this Tissue object.
		* Do the necessary operation that your own implementation requires.
			(Whatever it is: Like decreasing the number of cells, or erasing from
			storage that you used to hold the cells, or anything else...)
		*/
		void Tissue::RemoveCell(Cell& rhs){
			for(int i = 0; i<c.size(); i++){
				if(rhs.GetCellID() == c[i]->GetCellID()){
					c[i]->~Cell();
					c[i] = NULL;
					break;
				}
			}
		}
		/*********************************************************************
		*									GetCell
		*
		* @return the cell whose id is given in the @param
		* If the cell whose id is given does not exit, in other words it is a
		  dead cell, then the method should throw DeadCellException which was
			defined in Exception.h.
		*/
		const Cell& Tissue::GetCell(int a) const{
			for(int i = 0; i<c.size(); i++){
				if(a == c[i]->GetCellID()){
				return *(c[i]);
				}
			}
			throw DeadCellException();
		}
		/*********************************************************************
		*									Interact
		*
		* This method makes the cells interacting with the microorganisms in
		  the @param. For each microorganism a compatible cell is found.
		  Input will be given satisfying that each microorganism fits into a cell.
		*/
		void Tissue::Interact(const vector<MicroOrganism*>& m){
			int i,j,k;
			vector<int> v;
			for(i = 0; i<m.size(); i++){
				for(j = 0; j<c.size();j++){
					for(k = 0; k<v.size();k++){
						if(v[k] == j){
							k = -1;
							break;
						}
					}
					if(k == -1){
						continue;
					}

					if(m[i]->DoesFitInto(*(c[j]))){
						cout<<"adfasdf"<<endl;

						m[i]->ConnectToCell(c[j]);
						v.push_back(j);
						return;
						break;
					}
				}
			}



		}
		/*********************************************************************
		*          THIS METHOD WILL NOT BE GRADED. YOU CAN LEAVE IT EMPTY! 
		*
		*									CreatePartitions
		*
		* Creates an R-Tree hierarchy as follows:
			- Each microorganism given in the @param is put into minimum 
			  bounding rectangle.
			- At the bottom level of tree the individual bounding rectangles 
			  of the microorganisms will be placed into the leaves.
			- On one level up, the overlapping bounding rectangles at the lower 
			  level are bounded with a minimum bounding rectangle and these 
			  larger rectangles are put into the nodes. Note that there may be 
			  more than two rectangles overlapping at the lower level and these 
			  may not be overlapped all each other. Namely, bounding rectangle 
			  A may be overlap with rectangle B, and B may overlap with rectangle 
			  C, but A may not overlap with C. Still, A, B and C all will be 
			  bounded with the same minimum rectangle, say D, and this embracing 
			  rectangle D will be put into one level up of A, B, C. Hierarchically, 
			  D will be parent, and A, B and C will be children of D.
			- At the higher levels the same procedure is applied. Finally, in 
			  the root, there will be the the largest Tissue object embracing all.
			- Attention to the following!: Let A, B, C, D, E, F and G be in the
			  same level of the tree. Let A, B, and C overlap somehow, call the 
			  minimum bounding rectangle of those as X. Similarly, let D, E, F
			  and G overlap and call the minimum bounding rectangle of those as Y.
			  Assume that none of A, B and C overlaps with any of D, E, F and G.
			  However, the resulting bounding rectangles X and Y may overlap. In
			  this case, the overlap of X and Y are handled in one level up!
			  (Namely, we do NOT take the minimum bounding rectangle of A, B, C, D,
			  E, F and G directly. We first take those of A, B, C (which is X)
			  and those of D, E, F and G  (which is Y) separately while going up
			  to one level up. Then, we take the minimum bounding rectangle of X 
			  and Y in the next level while going up to one more level up.)
			- It may happen that a rectangle may not overlap/intersect with any 
			  other rectangle at some level. In this case, you should put it into
			  a minimum bounding rectangle of the same size with itself in one
			  level up. Only, in the highest level, if X, Y, ... and Z are the
			  rectangle nodes which are never intersecting with each other, you
			  should put them all in a single bounding rectangle R, and terminate
			  by making R root.
		*/
		void Tissue::CreatePartitions(const vector<MicroOrganism*>&){

		}
		/*********************************************************************
		*          THIS METHOD WILL NOT BE GRADED. YOU CAN LEAVE IT EMPTY!
		*
		*									Cure By Plasma
		*
		* This method takes an other Tissue object as @param ( a tissue taken
		  from a person getting well after Covid-19) and replaces the corresponding 
		  part of this Tissue object with that tissue. Hence, all the harmful 
		  microorganisms, including the Covid-19, will have been removed through 
		  this plasma treatment! :)
		* The tissue given in the @param will always be a subset of the current
		  tissue. Namely, the pattern of tissue taken will comply with the
		  tissue of the sick person.
		*/
		void Tissue::TreatByPlasma(Tissue){
			
		}
		/*********************************************************************/
