#include "Cell.h"

using namespace std;

#define EPSILON 0.01



		/*********************************************************************
		*									Constructor
		*
		* The first @param is the id of the cell
		* The second @param is the cell wall which defines the shape of the cell
		* The third @param is the Tissue that cell belongs to
		*/
		Cell::Cell(int id, const vector<Wall*>& vec, Tissue* t){
			int i;
			i = 0;
			this->id = id;
			this->t = t;
			while(i<vec.size()){
				(this->vec).push_back((vec[i])->Clone());
				i++;
			}

		}
		/*********************************************************************
		*									Copy Constructor
		*
		* Deep copy
		*/
		Cell::Cell(const Cell& rhs){
			int i;
			this->id = rhs.id;
			this->t = rhs.t;
			i = 0;
			while(i<(rhs.vec).size()){
				
				(this->vec).push_back(((rhs.GetCellWall())[i])->Clone()); //hata burada.....
				
				i++;
			}


		}
		/*********************************************************************
		*									GetCellID
		*
		* @return the cell id
		*/
		int Cell::GetCellID() const{
			return this->id;
		}
		/*********************************************************************
		*									GetCellID
		*
		* @return pointer for the tissue that this cell belongs to.
		*/
		Tissue* Cell::GetTissue() const{
			return this->t;

		}
		/*********************************************************************
		*									GetCellWall
		*
		* @return the cell wall
		*/
		const vector<Wall*>& Cell::GetCellWall() const{
			return this->vec;

		}
		/*********************************************************************
		*									RenewCellWall
		*
		* Replaces the current cell wall with the one given in the argument
		*/
		void Cell::RenewCellWall(vector<Wall*>& rhs){
			int i = 0;
			while(i<(this->vec).size()){
				(this->vec)[i]->~Wall();
				(this->vec).erase((this->vec).begin());
				i++;
			}	
			i = 0;
			while(i<vec.size()){
				(this->vec).push_back(new Wall(*(vec[i])));
				i++;
			}
		}
		/*********************************************************************
		*									StrengthenCellWall
		*
		* Creates a new cell wall by connecting the partial walls which can
		  be added with + operator
		* Replaces the old cell wall with the new one
		*/
		void Cell::StrengthenCellWall(){
			
			vector<Wall*> tmp;
			Wall* p;
			Wall *l;
			const Wall *r;
			Wall *res;
			int i,k,j;
			k = 0;
			if((this->vec).size()!=1){
				while(k == 0){

					for(i = 0; i<(this->vec).size();i++){
						j = i+1;
						if(j == (this->vec).size()){
							j = 0;
						}
					    try {
							p = new Wall(*((this->vec)[i])+*((this->vec)[j]));
					    } catch (ApplePearException& e) {
					      continue;
					    }
							(this->vec)[i]->~Wall();

						    (this->vec)[i] = p;
						    p = NULL;
						    (this->vec)[j]->~Wall();
						    (this->vec).erase((this->vec).begin()+j);
					}
					if(i == 1&&j ==1){
						k = 1;
					}
					if(j == 0){
						k = 1;
					}
				}
			}
				

		}
		/*********************************************************************
		*									Destructor
		*
		*/
		Cell::~Cell(){
			int i = 0;
			while(i<(this->vec).size()){
				(this->vec)[i]->~Wall();
				(this->vec).erase((this->vec).begin());
				i++;
			}
			this->t = NULL; //delete t ???? 

		}
		/*********************************************************************
		*									Stream Operator
		*
		* Prints cell wall
		* The format is: (p1.x,p1.y) - (p2.x,p2.y) - ... - (pn.x,pn.y)
		  where p1, p2, ..., pn are the the particles on the cell wall.
		* Do NOT add new line character "\n" to the end of the stream.
		*/
		ostream& operator<<(ostream& os, const Cell& rhs){
			int i;
			i = 0;
			while(i<(rhs.vec).size()){
				os<<"("<<(rhs.vec)[i]->GetInitialParticle().X()<<","<<(rhs.vec)[i]->GetInitialParticle().Y()<<")";
				if((rhs.vec).size() -1 != i){
					os<<"-";
				}
				i++;
			}
			return os;
		}
		/********************************************************************/