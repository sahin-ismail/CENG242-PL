#include "Wall.h"

using namespace std;

#define EPSILON 0.01

		/*********************************************************************
		*									Constructor
		*
		* @param is the length of the Wall
		*/
		Wall::Wall(float x){
			w = 0;
			this->x = x;
			start = NULL;
			end = NULL;
		}
		/*********************************************************************
		*									Constructor
		*
		* The first @param is the start point of Wall
		* The second @param is the end point of Wall
		* The Wall object is defined in counterclockwise direction.
		*/
		Wall::Wall(const Particle& first, const Particle& second){
			w = 0;
			float tx,ty;			
			start = new Particle(first);
			end = new Particle(second);
			tx = ((*end).X()-(*start).X());
			ty = ((*end).Y()-(*start).Y());
			this->x = sqrt(tx*tx+ty*ty);
			
		}
		/*********************************************************************
		*									Copy constructor
		*
		* Deep copy
		*/
		Wall::Wall(const Wall& rhs){
			w = rhs.w;
			x = rhs.x;
			start = new Particle(*(rhs.start));
			end = new Particle(*(rhs.end)); 
		}
		/*********************************************************************
		*									GetInitialParticle
		*
		* @return the start point of Wall
		* This method will be called only for the walls construted with their start
		  and end points
		*/
		const Particle& Wall::GetInitialParticle() const{
			return *start;
		}
		/*********************************************************************
		*									GetFinalParticle
		*
		* @return the end point of Wall
		* This method will be called only for the walls construted with their start
		  and end points
		*/
		const Particle& Wall::GetFinalParticle() const{
			return *end;
		}
		/*********************************************************************
		*									FindAngleBetween
		*
		* @return the angle between this Wall object and the one given in the @param
		*/
		float Wall::FindAngleBetween(const Wall& rhs) const{
			float tx,rx,ty,ry,m12,m13,theta;
			tx = ((*end).X()-(*start).X());
			rx = (rhs.GetFinalParticle().X()-rhs.GetInitialParticle().X());
			ty = ((*end).Y()-(*start).Y());
			ry = (rhs.GetFinalParticle().Y()-rhs.GetInitialParticle().Y());
			m12 = sqrt(tx*tx+ty*ty);
			m13 = sqrt(rx*rx+ry*ry);
			theta = acos((tx*rx+ty*ry)/(m12*m13));
			return theta;

		}
		/*********************************************************************
		*									GetLength
		*
		* @return the length of Wall
		*/
		float Wall::GetLength() const{
			return this->x;
		}
		/*********************************************************************
		*									ComputeLength
		*
		* Computes the length of the Wall object
		*/
		void Wall::ComputeLength(){
			float tx,ty,length;
			tx = ((*end).X()-(*start).X());
			ty = ((*end).Y()-(*start).Y());
			length = sqrt(tx*tx+ty*ty);

		}
		/*********************************************************************
		*									Clone
		*
		* @return pointer to a copy of this Wall object
		*/
		Wall* Wall::Clone() const{
			Wall* p;
			if(start == NULL){
				p = new Wall(x);
				return p;
			}
			p = new Wall(*start,*end);
			return p;
		}
		/*********************************************************************
		*									IsContinuousLinear
		*
		* Checks whether the end points of this Wall object and the end points
		  of the Wall given in the @param are linear and the walls are continuous
		* @return true if they are linear and continuous, false otherwise
		* The method returns always false in case that the wall given in the
		  argument is a curvy wall
		* Two walls are linear only if they are straight walls and their slopes
		  are equal (Be cautious while calculating slope of the vertical lines!)
		* Two walls are continuous only if one starts at the point where the
		  other ends (the fact that which one of the two walls starts first is
		  not important.)
		* The walls to be combined will always be the ones constructed with
		  their start and end points (anomalous examples will not be tested.)
		*/
		bool Wall::IsContinuousLinear(const Wall& rhs) const{
			bool lin,con;
			int l1,l2;
			float m1,m2;
			l1 = l2 = 0;
			if(((*end).Y()-(*start).Y()) == 0){
				l1 = 1;
			}else{
				m1 = ((*end).X()-(*start).X())/((*end).Y()-(*start).Y());
			}
			if((rhs.GetFinalParticle().Y()-rhs.GetInitialParticle().Y()) == 0){
				l2 = 1;
			}else{
				m2 = (rhs.GetFinalParticle().X()-rhs.GetInitialParticle().X())/(rhs.GetFinalParticle().Y()-rhs.GetInitialParticle().Y());
			}
			if((l1==1)||(l2==1)){
				if(l1 == l2){
					lin = true;
				}
				else{
					lin = false;
				}
			}
			else{
				if(m1 == m2){
					lin = true;
				}
				else {
					lin = false;
				}
			}
			if(((*start).X() == rhs.GetFinalParticle().X())&&(((*start).Y()) == rhs.GetFinalParticle().Y())){
				con = true;
			}
			else if(((*end).X() == rhs.GetInitialParticle().X())&&(((*end).Y()) == rhs.GetInitialParticle().Y())){
				con = true;
			}
			else{
				con = false;
			}

			return lin&&con;
		}
		/*********************************************************************
		*									Operator overload
		*
		* Combines this Wall object with the Wall given in the @param
		* @return the combined wall
		* Two walls can be combined only if one of the two cases below are
		  satisfied:
			- They are both straight walls such that one starts at the point
			  where the other ends
			- They are both curvy walls such that one starts at the point where
		    the other ends and their center is common (coordinates of their
			  center points are the same)
		 	- On the other hand, the fact that which one of the two walls starts
			  first is not important. Similar to the fact that 3+5 = 5+3.
		* For the cases which do not satisfy above, the method should throw
		  ApplePearException which was defined in Exception.h.
		* The walls to be combined will always be the ones constructed with
		  their start and end points (anomalous examples will not be tested.)
		*/
		const Wall& Wall::operator+(const Wall& rhs) const{
			bool con;
			Wall* b;
			int a = -1;
			con = false;
			if(rhs.w == 1 ){
				throw ApplePearException();
			}

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

			if((con == true)&&(this->IsContinuousLinear(rhs))){
				if(a == 1){
					b = new Wall(*(rhs.start),*(this->end));
					return *b;
				}
				else{
					b = new Wall(*(this->start),*(rhs.end));
					return *b;

				}
			}
			else{
				throw ApplePearException();
			}
		}
		/*********************************************************************
		*									Destructor
		*
		*/
		Wall::~Wall(){
			delete start;
			delete end;

		}
		/********************************************************************/