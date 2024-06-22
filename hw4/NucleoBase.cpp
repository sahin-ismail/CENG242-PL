#include "NucleoBase.h"

using namespace std;

#define EPSILON 0.01

		/*********************************************************************
		*									Constructor
		*
		* The first @param is the whole RNA sequence
		* The second parameter is a NucleoBase pointer addressing the previous
		  NucleoBase object. For the initial nucleobase this is NULL.
		*/
		NucleoBase::NucleoBase(string s, NucleoBase* nb){
			this->s = s;
			this->nb = nb; 
		}
		/*********************************************************************
		*								Copy Constructor
		*
		* Deep copy
		*/
		NucleoBase::NucleoBase(const NucleoBase& rhs){
			this->s = rhs.s;
			this->nb = rhs.nb;
		}
		/*********************************************************************
		*									Destructor
		*
		*/
		NucleoBase::~NucleoBase(){
			this->nb = NULL;
		}
		/*********************************************************************
		*									GetLast
		*
		* @return pointer to the last element of NucleoBase chain.
		*/
		NucleoBase* NucleoBase::GetLast(){

		}
		/*********************************************************************
		*									Stream Operator
		* Prints the data in NucleoBase chain.
		* Prints the char data of each NucleoBase object starting from the
		  given NucleoBase in the @param upto the last element of the chain.
		* Do NOT add new line character "\n" to the end of the stream.
		*/
		ostream& operator<<(ostream&, const NucleoBase&){
			
		}
		/********************************************************************/