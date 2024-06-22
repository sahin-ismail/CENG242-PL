#include "CurvyWall.h"

using namespace std;

#define EPSILON 0.01

		/*********************************************************************
		*									Constructor
	 	*
		* The first @param is the length of the CurvyWall
		* The second @param is the radius of the CurvyWall
	 	*/
		CurvyWall::CurvyWall(float x, float y): Wall(x){
			w = 1;
			this->r = y;
		}
		/*********************************************************************
		*									Constructor
		*
		* The first @param is the start point of CurvyWall
		* The second @param is the end point of CurvyWall
		* The third @param is the center point of CurvyWall
		* The CurvyWall object is defined in counterclockwise direction.
	 	*/
		CurvyWall::CurvyWall(const Particle& first, const Particle& second, const Particle& third): Wall(first,second){
			w = 1;
			this->center = new Particle(third);
		}
		/*********************************************************************
		*									Copy Constructor
	 	*
		* Deep copy
	 	*/
		CurvyWall::CurvyWall(const CurvyWall& rhs): Wall(rhs){
			w = rhs.w;
			center = new Particle(*(rhs.center));
		}
		/*********************************************************************
	 	*									GetRadius
		*
		* @return the radius of CurvyWall
	 	*/
		float CurvyWall::GetRadius() const{
			return r;

		}
		/*********************************************************************
	 	*									GetCenter
		*
		* @return the center point of CurvyWall
	 	*/
		const Particle& CurvyWall::GetCenter() const{
			return *center;
		}
		/*********************************************************************
		*									ComputeLength
		*
		* Computes the length of the CurvyWall object
		* Use PI defined in the macros in case that you need
		*/
		void CurvyWall::ComputeLength(){
			float tx,rx,ty,ry,m12,m13,theta,len;
			tx = ((*center).X()-(*start).X());
			rx = ((*end).X()-(*center).X());
			ty = ((*center).Y()-(*start).Y());
			ry = ((*end).Y()-(*center).Y());
			m12 = sqrt(tx*tx+ty*ty);
			m13 = sqrt(rx*rx+ry*ry);
			theta = acos((tx*rx+ty*ry)/(m12*m13));
			len = 2*PI*r*(theta/6.28318531);
		}
		/*********************************************************************
		*									Clone
		*
		* @return pointer to a copy of this Wall object
		*/
		Wall* CurvyWall::Clone() const{
			Wall* p;
			if(start==NULL){
				p = new CurvyWall(this->x,this->r);
				return p;
			}
			p = new CurvyWall(*(this->start),*(this->end),*(this->center));
			return p;
		}
		/*********************************************************************
		*									IsContinuousLinear
		*
	 	* @return false always
	 	*/
		bool CurvyWall::IsContinuousLinear(const Wall& rhs) const{
			return false;
		}
		/*********************************************************************
		*									Operator overload
		*
		* Combines this CurvyWall object with the Wall given in the @param
		* @return the combined wall
		*	- The combination can be done only if the wall given in the argument
		    is also a CurvyWall such that one wall starts at the point where
			  the other ends and their center is common (coordinates of their
			  center points are the same)
			- On the other hand, the fact that which one of the two walls starts
			  first is not important. Similar to the fact that 3+5 = 5+3.
		* For the cases which do not satisfy above, the method should throw
		  ApplePearException which was defined in Exception.h.
		* The walls to be combined will always be the ones constructed with
		  their start and end points (anomalous examples will not be tested.)
	 	*/
		const Wall& CurvyWall::operator+(const Wall& rhs) const{
			bool con;
			int a = -1;
			con = false;
			const CurvyWall* p;
			Wall* res;
			if(rhs.w != 1){
				throw ApplePearException();
			}
			else{
				p = dynamic_cast<const CurvyWall*>(&rhs);

				if((p->GetCenter()) == (this->GetCenter())){
					if(((*start).X() == rhs.GetFinalParticle().X())&&(((*start).Y()) == rhs.GetFinalParticle().Y())){
						con = true;
						a = 1;
					}
					else if(((*end).X() == rhs.GetInitialParticle().X())&&(((*end).Y()) == rhs.GetInitialParticle().Y())){
						con = true;
						a = 2;
					}
					else{
						con = false;
					}
					if(con == true){
						if(a == 1){
							res = new CurvyWall(*(rhs.start),*(this->end),*(this->center)); ///r,w,... değerler eklenecek.
							return *res;
						}
						else{
							res = new CurvyWall(*(this->start),*(rhs.end),*(this->center));
							return *res;

						}
					}
					else{
						throw ApplePearException();
					}
						}
				else{
					throw ApplePearException();
				}
			}

		}
		/*********************************************************************
		*									Destructor
		*
	 	*/
		CurvyWall::~CurvyWall(){
		
			delete center;

		}
		/********************************************************************/