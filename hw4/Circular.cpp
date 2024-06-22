#include "Circular.h"

using namespace std;

#define EPSILON 0.01		

		/*********************************************************************
		*									Constructor
		*
		* The first @param is the id of the cell
		* The second @param is the radius of the boundary
		*/
		Circular::Circular(int a, float b):MicroOrganism(a){
			this->r = b;
		}
		/*********************************************************************
		*									Destructor
		*
		*/
		Circular::~Circular(){
			
		}
		/*********************************************************************
		*									ConnectToCell
		*
		* See the base class explanation.
		*/
		void Circular::ConnectToCell(Cell* const){
			
		}
		/*********************************************************************
		*									DoesFitInto
		*
		* See the base class explanation.
		*/
		bool Circular::DoesFitInto(const Cell&) const{
			
		}
		/*********************************************************************
		*										React
		*
		* This type of microorganism makes the size of the cell get two times
		  larger without changing the center of the cell.
		* As an effect of the enlarging, you should renew the cell walls.
		* The microorganism size does not change.
		*/
		void Circular::React(){
			
		}
		/*********************************************************************
		*									DoesContain
		*
		* Special to this type of microorganism
		* Checks whether the given Particle in the @param is inside the
		  this microorganism, or not.
		* @return true if the particle is inside, false otherwise.
		*/
		bool Circular::DoesContain(const Particle&) const{
			
		}
		/*********************************************************************/