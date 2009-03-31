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
#ifndef FIZOBJECT_CPP
#define FIZOBJECT_CPP

//LibFizzix includes
#include "fizobject.h"

//Default Constructor 
FizObject::FizObject() 
{
	vec3 color = {64.0, 64.0, 64.0};
	this->init("UnNamed", color, true, std::vector<triangle>());
}
	
//Constructor that inits the name
FizObject::FizObject(std::string newname) 
{
	vec3 color = {64.0,64.0,64.0};
	this->init(newname, color, true, std::vector<triangle>());
}

//Constructor that inits the name, color and possibly the smoothity
FizObject::FizObject(std::string newname, vec3 color, bool smooth)
{
	this->init(newname,color,smooth, std::vector<triangle>());
}

// Constructor that inits the name and vertices and possibly the smoothity
FizObject::FizObject(std::string newname, std::vector<triangle> init, bool smooth) 
{
	vec3 color = {64.0, 64.0, 64.0};
	this->init(newname,color,smooth,init);
}

// Constructor that inits the vertices, color, and smoothity
FizObject::FizObject(std::string newname, vec3 color, std::vector<triangle> init, bool smooth)
{
	this->init(newname, color, smooth, init);
}

// Init the object
void FizObject::init(std::string name, vec3 color, bool smooth, std::vector<triangle> tinit)
{
	this->init_object(name,color,smooth, tinit);
	this->compute();
	this->adjustMasses(1.0);
}

/** Initialized the structure, used by constructors
 */
void FizObject::init_object(std::string name, vec3 color, bool smooth, std::vector<triangle> tinit) 
{
	this->name = name;
	vertices = tinit;
	fizdatum col = {0.0, color, VECTOR};
	props["color"] = col;
	fizdatum smo = {(double)smooth, {0.0,0.0,0.0},SCALAR};
	props["smooth"] = smo;
}

/** Next two methods complements to Game Physics, 2nd Edition, by David H Elberly,
 *  Chapter 2.5, Momenta
 *
 *  These formulas found on pg 75 - 79
 */

//NOT A MEMBER OF FIZOBJECT. helper
void sub_compute(const double& w0, const double& w1, const double& w2, 
		 double& f1, double& f2, double& f3,
	       	 double& g0, double& g1, double& g2) 
{
	double temp0 = w0 + w1;
	f1 = temp0 + w2;
	double temp1 = w0 * w0;
	double temp2 = temp1 + w1 * temp0;
	f2 = temp2 + w2 * f1;
	f3 = w0 * temp1 + w1 * temp2 + w2 * f2;
	g0 = f2 + w0 * (f1 + w0);
	g1 = f2 + w1 * (f1 + w1);
	g2 = f2 + w2 * (f1 + w2);
}

//div_consts
// Compute the COM, etc
void FizObject::compute() 
{
	double integral[10] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	double f1x, f2x, f3x, g0x, g1x, g2x;
	double f1y, f2y, f3y, g0y, g1y, g2y;
	double f1z, f2z, f3z, g0z, g1z, g2z;
	point p0,p1,p2;
	for(int i = 0; i < vertices.size(); i++) 
	{
		const triangle& t = vertices[i];
		sub_compute(t[0][0], t[1][0], t2[0], f1x, f2x, f3x, g0x, g1x, g2x);
		sub_compute(t[0][1], t[1][1], t2[1], f1y, f2y, f3y, g0y, g1y, g2y);
		sub_compute(t[0][2], t[1][2], t2[2], f1z, f2z, f3z, g0z, g1z, g2z);
		
	}
}

const fizdatum FizObject::operator[](const std::string& key) 
{
	if(contains(key))
	{
		return props.find(key)->second;
	}	
	else 
	{
		throw std::out_of_range("Key does not exist");
	}
}

bool FizObject::contains(const std::string& key) 
{ 
	return props.count(key) != 0; 
}

//Getters and setters
const vec3 FizObject::getPos() 				{ return pos; }
vec3& FizObject::rgetPos() 				{ return pos; }
void FizObject::setPos(vec3 newpos)			{ pos = newpos; 
							  fizdatum data = {0.0, pos, VECTOR};
							  props["position"] = data; 
							}

const vec3 FizObject::getVel() 				{ return vel; }
vec3& FizObject::rgetVel() 				{ return vel; }
void FizObject::setVel(vec3 newvel) 			{ vel = newvel; 
							  fizdatum data = {0.0, vel, VECTOR};
							  props["velocity"] = data;
							}

const vec3 FizObject::getAcc() 				{ return acc; }
vec3& FizObject::rgetAcc() 				{ return acc; }
void FizObject::setAcc(vec3 newacc)			{ acc = newacc; 
							  fizdatum data = {0.0, acc, VECTOR};	
						          props["acceleration"] = data;
							}

const vec3 FizObject::getOme() 				{ return ome; }
vec3& FizObject::rgetOme() 				{ return ome; }
void FizObject::setOme(vec3 newome) 			{ ome = newome; 
							  fizdatum data = {0.0, ome, VECTOR};
							  props["angular_velocity"] = data; 
							}

const vec3 FizObject::getAlp() 				{ return alp; }
vec3& FizObject::rgetAlp() 				{ return alp; }
void FizObject::setAlp(vec3 newalp)			{ alp = newalp; 
							  fizdatum data = {0.0, alp, VECTOR};
							  props["angular_acceleration"] = data;
							}
	
const std::vector<triangle> FizObject::getVertices()		{ return vertices; }
std::vector<triangle>& FizObject::rgetVertices() 		{ return vertices; }
void FizObject::setVertices(std::vector<triangle> newvertices) 	{ vertices = newvertices; }
		

const Quaternion FizObject::getQuaternion() 		{ return quaternion; }
Quaternion& FizObject::rgetQuaternion()			{ return quaternion; }
void FizObject::setQuaternion(Quaternion newquat)	{ quaternion = newquat;	}
		
const vec3 FizObject::getInertiaTensor()		{ return inertiaTensor; }
vec3& FizObject::rgetInertiaTensor()			{ return inertiaTensor; }
void FizObject::setInertiaTensor(vec3 newtensor)	{ inertiaTensor = newtensor; }
                
const vec3 FizObject::getInertiaTensorInv()    	       	{ return inertiaTensor; }
vec3& FizObject::rgetInertiatensor()                	{ return inertiaTensorInv; }
void FizObject::setInertiaTensorInv(vec3 newtensor)  	{ inertiaTensorInv = newtensor;}

		
double FizObject::getMass()				{ return mass; }
double& FizObject::rgetMass()				{ return mass; }
void FizObject::setMass(double newmass)			{ mass = newmass; 
							  fizdatum data = {mass, {0.0,0.0,0.0}, SCALAR};
      						          props["mass"] = data;
							}

std::string FizObject::getName()			{ return name; }
void FizObject::setName(std::string newname)		{ name = newname;}

fizdatum FizObject::getProperty(std::string key) 
{
	if(contains(key))
	{
		return props.find(key)->second;
	}
	else
	{
		throw std::out_of_range("Key does not exist");
	}
}

void FizObject::setProperty(std::string key, fizdatum value) 
{
//	if(key == "positionX")

	props[key] = value;
}

#endif




