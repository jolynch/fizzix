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
#include <stdexcept>

//LibFizzix includes
#include "quaternion.h"
#include "gen_structs.h"
#include "matrix.h"

/** @class FizObject fizobject.h "libfizzix/src/fizengine.h"
 *  @brief This class represents an object in space
 *
 *  The FizObject class is the fundamental object class, meaning that
 *  it is used to represent every 3d rigid body in the world as far
 *  as FizEngine is concerned.  Each object has properties such as mass
 *  and an inertia tensor, along with methods to access, change, or 
 *  interact with other FizObjects
 */
class FizObject 
{
	private:
		std::map<std::string, fizdatum> props;
		/** Time dependant properties
		 */
		vec3 pos;
		vec3 vel;
		vec3 acc;
		vec3 ome;
		vec3 alp;
		
		/** List of the bounding triangles
		 */
		std::vector<triangle> vertices;

		/** Rotation specific members
		 */

		Quaternion quaternion;
		vec3 inertiaTensor;
		vec3 inertiaTensorInv;
		
		//Unless we need it
		//Matrix rotation

		/** Other properties
		 */
		double mass;
		std::string name;

		/** Calculate COM, Inertia Tensor, and relative masses of triangles
		 *  @note This will redefine the pos, inertiaTensor, and the triangles
		 */
		void compute();

		/** Knowing the mass and the volume, now calculate the correct masses of triangles 
		 */

		void adjustMasses(double volume);
	public:
	
		/** Default Constructor
		 */
		FizObject(std::string newname);
		
		/** Constructor that inits the vertices
		 */
		FizObject(std::string newname, std::vector<triangle> init);

		/** Return a property given the key, so this["mass"] should return a result
		 *  @param key A string name for the property, mass would be "mass", center of mass "COM", etc ...
		 *  @return a result_t struct containing any values if found (otherwise 0,NULL,NULL)
		 */
		const fizdatum operator[](const std::string& key);

		bool contains(const std::string& key);
		
		/** Time dependant property access and modification 
		 */
		const vec3 getPos();
		vec3& rgetPos(); 
		void setPos(vec3 newpos);
			
		const vec3 getVel(); 
		vec3& rgetVel(); 
		void setVel(vec3 newvel); 

		const vec3 getAcc();
		vec3& rgetAcc(); 
		void setAcc(vec3 newacc);	
	
		const vec3 getOme(); 
		vec3& rgetOme(); 
		void setOme(vec3 newome); 	
		
		const vec3 getAlp(); 	
		vec3& rgetAlp();	
		void setAlp(vec3 newalp);			
			
		/** List of the bounding triangles access and modification
		 */
		const std::vector<triangle> getVertices();	
		std::vector<triangle>& rgetVertices(); 	
		void setVertices(std::vector<triangle> newvertices);
		
		/** Rotation specific members
		 */

		const Quaternion getQuaternion();
		Quaternion& rgetQuaternion();
		void setQuaternion(Quaternion newquat);

		const vec3 getInertiaTensor();
		vec3& rgetInertiaTensor();
		void setInertiaTensor(vec3 newtensor);
                
		const vec3 getInertiaTensorInv();
		vec3& rgetInertiatensor();
		void setInertiaTensorInv(vec3 newtensor);
		
		/** Other properties
		 */
		double getMass();
		double& rgetMass();
		void setMass(double newmass);

		std::string getName();
		void setName(std::string newname);

		/** User defined properties
		 */
		fizdatum getProperty(std::string key);
		void setProperty(std::string key, fizdatum);

};

#endif



