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
#include "quaternion.h"

/* TODO
 * - default property - color (texture?), possibly a struct
 * - bool smooth 
 */


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
		double maxrad; //radius of the bounding sphere - if two objects' spheres overlap, check for collision
		triangle comtriangle; //center of mass triangle - at the COM, with massp of 1;
		
		/** Rotation specific members
		 */

		Quaternion quaternion;
		//xx,yy,zz,xy,yz,xz
		std::vector<double> inertiaTensor;
		//xx,yy,zz,xy,yz
		std::vector<double> inertiaTensorInv;
		
		//Unless we need it
		//Matrix rotation

		/** Other properties
		 */
		double mass;
		std::string name;
		bool comapprox; //whether the object can be approximated as it's center of mass

	protected:
		/** Initialize the Object by calling init_object, compute and adjustMasses
		 */
		void init(std::string name, vec3 color, const std::vector<triangle>& new_vertices);
		
		/** Initialize the object with info passed into constructors
		 */
		virtual void init_object(std::string name, vec3 color, const std::vector<triangle>& new_vertices);
		
		/** Calculate COM, Inertia Tensor, and relative masses of triangles
		 *  @note This will/should redefine the pos, inertiaTensor, and the triangles
		 *  @
		 */
		virtual void compute();

		/** Knowing the mass and the volume, now calculate the correct masses of triangles 
		 */
		void adjustMasses();

		void computeBounds();

	public:

		/** Default Constructor
		 */
		FizObject();

		/** Constructor that inits the name
		 */
		FizObject(std::string newname);
		
		/** Constructor that inits the name, color and possibly the smoothity
		 */
		FizObject(std::string newname, vec3 color);

		/** Constructor that inits the name and triangles
		 */	
		FizObject(std::string newname, std::vector<triangle> init);

		/** Constructor that inits the vertices, color, and triangles
		 */
		FizObject(std::string newname, vec3 color, std::vector<triangle> init);

		/** Return a property given the key, so this["mass"] should return a result
		 *  @param key A string name for the property, mass would be "mass", center of mass "COM", etc ...
		 *  @return a result_t struct containing any values if found (otherwise 0,NULL,NULL)
		 */
		const fizdatum operator[] (const std::string& key) const;

		bool contains(const std::string& key) const;
		
		/** Time dependant property access and modification 
		 */
		const vec3 getPos() const;
		vec3& rgetPos(); 
		void setPos(vec3 newpos);
			
		const vec3 getVel() const; 
		vec3& rgetVel(); 
		void setVel(vec3 newvel); 

		const vec3 getAcc() const;
		vec3& rgetAcc(); 
		void setAcc(vec3 newacc);	
	
		const vec3 getOme() const; 
		vec3& rgetOme(); 
		void setOme(vec3 newome); 	
		
		const vec3 getAlp() const; 	
		vec3& rgetAlp();	
		void setAlp(vec3 newalp);			
			
		/** List of the bounding triangles access and modification
		 */
		const std::vector<triangle> getVertices() const;	
		std::vector<triangle>& rgetVertices(); 	
		void setVertices(std::vector<triangle> newvertices);
		
		const triangle getCOMTriangle() const;
		triangle& rgetCOMTriangle();
		void setCOMTriangle(triangle tri);
		
		/** Rotation specific members
		 */

		const Quaternion getQuaternion() const;
		Quaternion& rgetQuaternion();
		void setQuaternion(Quaternion newquat);

		const std::vector<double> getInertiaTensor() const;
		std::vector<double>& rgetInertiaTensor();
		void setInertiaTensor(std::vector<double> newtensor);
                
		const std::vector<double> getInertiaTensorInv() const;
		std::vector<double>& rgetInertiaTensorInv();
		void setInertiaTensorInv(std::vector<double> newtensor);
		
		/** Other properties
		 */
		double getMass() const;
		double& rgetMass();
		void setMass(double newmass);

		const std::string getName() const;
		void setName(std::string newname);

		/** User defined properties
		 */
		fizdatum getProperty(std::string key) const;
		void setProperty(std::string key, fizdatum);
		//Returns the number of elements removed (0 for none, 1 for one ...)	
		int removeProperty(std::string key);
			
		bool comApprox();

};

#endif




