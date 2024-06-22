#include "Triangular.h"

using namespace std;

#define EPSILON 0.01


		/*********************************************************************
		*									Constructor
		*
		* The first @param is the id of the cell
		* The second @param is the vector of edges
		* The third parameter is a NucleoBase object that defining its RNA.
		*/
		Triangular::Triangular(int a , const vector<Wall*>& b, const NucleoBase& nb):MicroOrganism(a, b){
			
			this->nb = new NucleoBase(nb);
		}
		/*********************************************************************
		*									Destructor
		*
		*/
		Triangular::~Triangular(){
			this->nb->~NucleoBase();
		}
		/*********************************************************************
		*									ConnectToCell
		*
		* See the base class explanation.
		*/
		void Triangular::ConnectToCell(Cell* const cell){
			this->cell = cell;
		}
		/*********************************************************************
		*									DoesFitInto
		*
		* See the base class explanation.
		*/
		bool Triangular::DoesFitInto(const Cell& c) const{
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
		*										React
		*
		* This type of microorganism kills the cell that it connects to.
		* Note that while you are deleting the cell, you should also make the
		* Tissue noticed that the corresponding cell was killed.
		*/
		void Triangular::React(){

		}
		/*********************************************************************
		*									GetRNA
		*
		* Special to this type of microorganism
		* @return the start node of the NucleoBase sequence which holds the RNA
		  of the microorganism
		*/
		const NucleoBase& Triangular::GetRNA() const{

		}
		/*********************************************************************
		*									Mutate
		*
		* Special to this type of microorganism
		* Mutate the RNA of this Triangular microorganism by crossing over with
		  RNA of the Triangular microorganism given in the @param.
		* Crossing over is done as follows:
		  Both RNA is compared in both ways: from the beginning to end and from
		  end to beginning. When they start to differ, the corresponding G-S
		  and A-U nucleobases in the differing part of both RNA are interchanged.
		  For example:
		  - Let RNA-1 be ASGAGGAUUGSUAGSSSAAG
		    (make readable: ASGAG GAUUGS UAGSSSAAG)
		  - Let RNA-2 be ASGAGSSGAUUUAGSSSAAG
		    (make readable: ASGAG SSGAUU UAGSSSAAG)
		  Since ASGAG part at the beginning and UAGSSSAAG part at the end are
		  the same in both RNA, those parts are held. For the parts remaining
		  in the middle, the corresponding G-S nucleobases and the corresponding
		  A-U nucleobases are interchanged. Other type of correspondences are
			removed from the chain (Deleted). At the end:
		  - RNA-1 becomes ASGAGSAUAGSSSAAG
		    (make readable: ASGAG SA UAGSSSAAG)
		  - RNA-2 becomes ASGAGGUUAGSSSAAG
		    (make readable: ASGAG GU UAGSSSAAG)
		* You can assume that at least 1 character from the beginning and the end
			will be the same for both RNA sequence (Just for you not to struggle
			with the so detailed implementation). Also, you can assume that at least
			1 character of RNAs will differ.
		*/
		void Triangular::Mutate(Triangular&){

		}
		/*********************************************************************/