/************************************************************************************************
This file is a part of libfizzix backend to the Fizzix project.
The website for this project is http://code.google.com/p/fizzix .
Copyright (C) 2009
	Joseph Lynch
	Anton Frolenkov
	Purnima Balakrishnan
	Daniel Stiles
	Eric Van Albert

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
************************************************************************************************/
#ifndef FIZOBJECT_H
#define FIZOBJECT_H

//Standard includes
#include <iostream>
#include <string>
#include <vector>
#include <map>

//LibFizzix includes
#include "quaternion.h"
#include "geometricshapes.h"
/*When Finished
#include "matrix.h"
*/
class Matrix;

/** @class FizObject fizobject.h "libfizzix/src/fizengine.h"
 *  @brief This class represents an object in space
 *
 *  The FizObject class is the fundamental object class, meaning that
 *  it is used to represent every 3d rigid body in the world as far
 *  as FizEngine is concerned.  Each object has properties such as mass
 *  and an inertia tensor, along with methods to access, change, or 
 *  interact with other FizObjects
 */
class FizObject: 
{
	private:
		std::map<std::string, double> userProps;
		
		/** Time dependant properties
		 */
		std::vector<double> pos;
		std::vector<double> vel;
		std::vector<double> acc;
		std::vector<double> ome;
		std::vector<double> alp;
			
		/** List of the bounding triangles
		 */
		std::vector<triangle> vertices;

		/** Rotation specific members
		 */

		Quaternion quaternion;
		Matrix inertiaTensor;
		Matrix inertiaTensorInv;
		
		//Unless we need it
		//Matrix rotation

		/** Other properties
		 */
		double mass;

	public:
	
		/** Default Constructor
		 */
		FizObject();

		/** Return a property given the key, so this["mass"] should return a result
		 *  @param key A string name for the property, mass would be "mass", center of mass "COM", etc ...
		 *  @return a result_t struct containing any values if found (otherwise 0,NULL,NULL)
		 */
		double operator[](std::string key) 
		{
			map<std::string, double>::iterator it1 = userProps.find(key);
			if(it1 != map::end) return *it1;
			return 0.0;
		}
		
		/** Time dependant property access and modification 
		 */
		const std::vector<double> pos() 	{ return pos; }
		std::vector<double>& rpos() 		{ return pos; }
		void spos(std::vector<double> newpos)	{ pos = newpos; }
			
		const std::vector<double> vel() 	{ return vel; }
		std::vector<double>& rvel() 		{ return vel; }
		void svel(std::vector<double> newvel) 	{ vel = newvel; }

		const std::vector<double> acc() 	{ return acc; }
		std::vector<double>& racc() 		{ return acc; }
		void sacc(std::vector<double> newacc) 	{ acc = newacc; }
	
		const std::vector<double> ome() 	{ return ome; }
		std::vector<double>& rome() 		{ return ome; }
		void some(std::vector<double> newome) 	{ vel = newome; }

		const std::vector<double> alp() 	{ return alp; }
		std::vector<double>& ralp() 		{ return alp; }
		void salp(std::vector<double> newalp) 	{ vel = newalp; }
			
		/** List of the bounding triangles access and modification
		 */
		const std::vector<triangle> vertices() 	{ return vertices; }
		std::vector<triangle>& rvertices() 	{ return vertices; }
		void svertices(std::vector<double> newvertices) { vertices = newvertices; }
		
		/** Rotation specific members
		 */

		const Quaternion quaternion() 		{ return quaternion; }
		Quaternion& rquaternion()		{ return quaternion; }
		void squaternion(Quaternion newquat)	{ quaternion = newquat; }
		
		const Matrix inertiaTensor()		{ return inertiaTensor; }
		Matrix& rinertiaTensor()		{ return inertiaTensor; }
		void sinertiaTensor(Matrix newtensor)	{ inertiaTensor = newtensor; }
                
		const Matrix inertiaTensorInv()            { return inertiaTensor; }
		Matrix& rinertiatensor()                { return inertiaTensorInv; }
		void sinertiaTensorInv(Matrix newtensor)   { inertiaTensorInv = newtensor; }

		
		//Unless we need it
		//Matrix rotation

		/** Other properties
		 */
		double mass;


};

#endif




