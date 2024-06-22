#include "Particle.h"

using namespace std;

#define EPSILON 0.01


		/*********************************************************************
		*	Constructor
		*
		* The first @param is the x-coordinate of the point
		* The second @param is the y-coordinate of the point
		*/
		Particle::Particle(float x, float y){
			this->x = x;
			this->y = y; 
		}
		/*********************************************************************
		*	Copy constructor
		*
		*/
		Particle::Particle(const Particle& rhs){
			this->x = rhs.x;
			this->y = rhs.y;

		}
		/*********************************************************************
		*	X()
		*
		* @return x-coordinate of the point
		*/
		float Particle::X() const{
			return this->x;

		}
		/*********************************************************************
		*	Y()
		*
		* @return y-coordinate of the point
		*/
		float Particle::Y() const{
			return this->y;

		}
		/*********************************************************************
		*	FindDistance
		*
		* Computes the Eucledean distance of this 2D Particle object to another
		  particle given in the @param
		* @return the distance
		*/
		float Particle::FindDistance(const Particle& rhs) const{

			float x = this->x - rhs.x; //calculating number to square in next step
			float y = this->y - rhs.y;
			float dist;

			dist = pow(x, 2) + pow(y, 2);       //calculating Euclidean distance
			dist = sqrt(dist);                  

			return dist;

		}
		/*********************************************************************
		*	Operator Overload
		*
		* Checks whether the x and y coordinates of this 2D Particle object is
		  equal to those of the particle given in the @param
		* @return true if they are equal, @return false if not
		* Use EPSILON given in the macros to compare the float values.
		*/
		bool Particle::operator== (const Particle& rhs) const{
			float diff = (this->x - rhs.X());
			float diff1 = (this->y - rhs.Y());

   			bool a = (diff < EPSILON) && (-diff < EPSILON);
   			bool b = (diff1 < EPSILON) && (-diff1 < EPSILON);
   			return a & b;
		}
		/*********************************************************************
		*									Stream Operator
		* Prints particle coordinates
		* The format is: (p.x,p.y) where p is the particle in the @param
		* Do NOT add new line character "\n" to the end of the stream.
		*/
		ostream& operator<<(ostream& os , const Particle& rhs){
			os<<"("<<(rhs.x)<<","<<(rhs.y)<<")";
			return os;
		}
		/********************************************************************/