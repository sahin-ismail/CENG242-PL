#include "MicroOrganism.h"

using namespace std;

#define EPSILON 0.01

		/*********************************************************************
		*									Constructor
		*
		* The first @param is the microorganism id
		* The second @param is the edges of Wall type
		  The given edges will have been constructed by their lengths and radius
		  (without a definite location)
		*/
		MicroOrganism::MicroOrganism(int id, const vector<Wall*>& edges){
			int i;
			i = 0;
			this->id = id;
			this->loc = 0;

			while(i<edges.size()){

				
				(this->vec).push_back((edges[i])->Clone());
				i++;
			}

		}
		/*********************************************************************
		*									Stream Operator
		*
		* Prints the location of the microorganism
		* If it is located in a cell, print in the following format:
		  "The microorganism <id1> was successfully placed into the cell <id2>."
		  where id1 is the microorganism id and id2 is the cell id.
		  If the microorganism is not located into any cell, then print:
		  "The microorganism <id> could not be placed into any cell!"
		* Do NOT add new line character "\n" to the end of the stream.
		*/
		ostream& operator<<(ostream& os, const MicroOrganism& rhs){
			if(rhs.loc == 0){
				os<<"The microorganism "<<rhs.id<<" could not be placed into any cell!";
			}
			else{
				os<<"The microorganism "<<rhs.id<<" was successfully placed into the cell "<<rhs.cell->GetCellID()<<".";
			}

		}
		/*********************************************************************
		*									DoesFitInto
		*
		* Checks whether the microorganism fits into the cell given in
		  the @param.
		* @return true if it fits, false otherwise.
		* A microorganism fits into a cell only if their boundary are the same
		  (the same type like triangle, circle or square and the same size).
		* Note that boundary of a cell is always given in counterclockwise, yet
		  edges of a microorganism do not have an order since it is not located
		  until connecting to a compatible cell. Therefore, a triangular
		  microorganism whose edges of length 3, 5, 4 units respectively may
		  connect to a triangle cell whose cell wall is defined with the walls
		  of length 3, 4, 5. You can consider it as turning the other face of
		  the microorganism to the front.
		* Also, do not forget to check the angels between the edges of a cell
		  while trying to place Squadratics. Checking only the edge lengths
		  is not sufficient since edges of equilateral quadrangles are also
		  equal, yet the inner angles are not 90 degrees.
		* Hint: Strengthen cell walls before checking its edges and angles.
		*/
		bool MicroOrganism::DoesFitInto(const Cell& c) const{
			int i,j,k;
			bool isin;
			Cell* ce = new Cell(c);

			ce->StrengthenCellWall();
			vector<int> v;
			vector<Wall*> cc = ce->GetCellWall();
			int count = 0;
			isin = false;

			if(cc.size() != this->vec.size()){
				return false;
			}  
			else{
				for(i = 0; i<cc.size();i++){
					for(j = 0; j<cc.size();j++){
						isin = false;
						for(k = 0; k<v.size();k++){
							if(j == v[k]){
								isin = true;
							}
						}
						if(isin){
							continue;
						}	
						if((cc[j]->GetLength() - (this->vec)[i]->GetLength())<EPSILON && ( (this->vec)[i]->GetLength() - cc[j]->GetLength())<EPSILON){
							v.push_back(j);


							continue;
						}
					}
				}
			}

			if(v.size() == cc.size()){
				ce->~Cell();
				ce = NULL;
				return true;
			}
			ce->~Cell();
			ce = NULL;
			return false;

		}
		/*********************************************************************
		*									ConnectToCell
		*
		* Connects the microorganism to the cell given in the @param
		* It is assummed that cell-microorganism comptability was checked
		  before calling this method, and the cell is compatible with
		  the microorganism.
		* Saves the cell pointer.
		* After connection, microorganism has a definite position which is
		  the same location the cell is on. It is your call to save other
		  connection effects like updating the walls/edges of the microorganism
		  with the definitely-located walls or defining vertices of it.
		*/
		void MicroOrganism::ConnectToCell(Cell* const cell){
			this->cell = cell;
		}
		/*********************************************************************
		*									React
		*
		* Functions depending on the microorganism type.
		* Results affect the microorganism and the cell that it connects to.
		* React method is called only when the microorganism is inside a cell.
		*/
		void MicroOrganism::React(){

		}
		/*********************************************************************
		*									Destructor
		*
		*/
		MicroOrganism::~MicroOrganism(){
		cell = NULL;
		for (int i = 0; i < vec.size(); ++i)
		{
			vec[i]->~Wall();
			vec[i] = NULL;
		}
			
		}
		/*********************************************************************/