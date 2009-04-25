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
	vec3 color(64.0, 64.0, 64.0);
	this->init("UnNamed", color, true, std::vector<triangle>());
}
	
//Constructor that inits the name
FizObject::FizObject(std::string newname) 
{
	vec3 color(64.0,64.0,64.0);
	this->init(newname, color, std::vector<triangle>());
}

//Constructor that inits the name, color and possibly the smoothity
FizObject::FizObject(std::string newname, vec3 color)
{
	this->init(newname,color,std::vector<triangle>());
}

// Constructor that inits the name and vertices and possibly the smoothity
FizObject::FizObject(std::string newname, std::vector<triangle> init,) 
{
	vec3 color(64.0, 64.0, 64.0);
	this->init(newname,color,init);
}

// Constructor that inits the vertices, color, and smoothity
FizObject::FizObject(std::string newname, vec3 color, std::vector<triangle> init)
{
	this->init(newname, color, init);
}

// Init the object
void FizObject::init(std::string name, vec3 color, const std::vector<triangle>& tinit)
{
	this->init_object(name,color,tinit);
	this->compute();
	this->adjustMasses(1.0);
	this->computeBounds();
}

/** Initialized the structure, used by constructors
 */
void FizObject::init_object(std::string name, vec3 color, const std::vector<triangle>& tinit) 
{
	this->name = name;
	vertices = tinit;
	props["color"] = fizdatum(0.0, color, VECTOR);
}

/** Next two methods complements to Game Physics, 2nd Edition, by David H Elberly,
 *  Chapter 2.5, Momenta
 *:q

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
		triangle& t = vertices[i];
		sub_compute(t[0][0], t[1][0], t[2][0], f1x, f2x, f3x, g0x, g1x, g2x);
		sub_compute(t[0][1], t[1][1], t[2][1], f1y, f2y, f3y, g0y, g1y, g2y);
		sub_compute(t[0][2], t[1][2], t[2][2], f1z, f2z, f3z, g0z, g1z, g2z);
		const vec3& d = t.normal;
		t.mass = d[0] * f1x;
		integral[0] += d[0] * f1x;
		integral[1] += d[0] * f2x;
		integral[2] += d[1] * f2y;
		integral[3] += d[2] * f2z;
		integral[4] += d[0] * f3x;
		integral[5] += d[1] * f3y;
		integral[6] += d[2] * f3z;
		integral[7] += d[0] * (t[0][1] * g0x + t[1][1] * g1x + t[2][1] * g2x);
		integral[8] += d[1] * (t[0][2] * g0y + t[1][2] * g1y + t[2][2] * g2y);
		integral[9] += d[2] * (t[0][0] * g0z + t[1][0] * g1z + t[2][0] * g2z);
	}

	integral[0] *= div_consts[0];
	integral[1] *= div_consts[1];
	integral[2] *= div_consts[1];
	integral[3] *= div_consts[1];
	integral[4] *= div_consts[2];
	integral[5] *= div_consts[2];
	integral[6] *= div_consts[2];
	integral[7] *= div_consts[3];
	integral[8] *= div_consts[3];
	integral[9] *= div_consts[3];

	setMass(integral[0]);
	setPos(vec3(integral[1]/mass, integral[2]/mass, integral[3]/mass));
	
	//xx,yy,zz,xy,yz,xz
	double * tempI = new double[6];
	double * tempIi = new double[6];
	double detI;

	//Relative to world coords
	tempI[0] = integral[5] + integral[6];
	tempI[1] = integral[4] + integral[6];
	tempI[2] = integral[4] + integral[5];
	tempI[3] = -1 * integral[7];
	tempI[4] = -1 * integral[8];
	tempI[5] = -1 * integral[9];


	tempI[0] -= mass * (pos[1] * pos[1] + pos[2] * pos[2]);
	tempI[1] -= mass * (pos[2] * pos[2] + pos[0] * pos[0]);
	tempI[2] -= mass * (pos[0] * pos[0] + pos[1] * pos[1]);
	tempI[3] += mass * pos[0] * pos[1];
	tempI[4] += mass * pos[1] * pos[2];
	tempI[5] += mass * pos[2] * pos[0];

	detI = 	tempI[0] * (tempI[1]*tempI[2] - tempI[4]*tempI[4]) +
	      	tempI[3] * (tempI[5]*tempI[4] - tempI[3]*tempI[2]) +
		tempI[5] * (tempI[3]*tempI[4] - tempI[5]*tempI[1]);
	
	tempIi[0] = (tempI[1]*tempI[2] - tempI[4]*tempI[4]) / detI;
	tempIi[1] = (tempI[0]*tempI[2] - tempI[5]*tempI[5]) / detI;
	tempIi[2] = (tempI[0]*tempI[1] - tempI[3]*tempI[3]) / detI;
	tempIi[3] = (tempI[5]*tempI[4] - tempI[3]*tempI[2]) / detI;
	tempIi[4] = (tempI[3]*tempI[5] - tempI[0]*tempI[4]) / detI;
	tempIi[5] = (tempI[3]*tempI[4] - tempI[5]*tempI[1]) / detI;
	
	setInertiaTensor(tempI);
	setInertiaTensorInv(tempIi);
}

void FizObject::computeBounds()
{
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			double r = sqrt(vertices[i][j][0]^2 + vertices[i][j][1]^2 + verticecs[i][j][2]^2);
			if (r > maxrad) maxrad = r;
		}
	}
}

const fizdatum FizObject::operator[](const std::string& key) 
{
	return getProperty(key);
}

bool FizObject::contains(const std::string& key) 
{ 
	return props.count(key) != 0; 
}

//Getters and setters
const vec3 FizObject::getPos() 				{ return pos; }
vec3& FizObject::rgetPos() 				{ return pos; }
void FizObject::setPos(vec3 newpos)			{ pos = newpos; 
							  props["position"] = fizdatum(0.0, pos, VECTOR); 
							}

const vec3 FizObject::getVel() 				{ return vel; }
vec3& FizObject::rgetVel() 				{ return vel; }
void FizObject::setVel(vec3 newvel) 			{ vel = newvel; 
							  props["velocity"] = fizdatum(0.0, vel, VECTOR);
							}

const vec3 FizObject::getAcc() 				{ return acc; }
vec3& FizObject::rgetAcc() 				{ return acc; }
void FizObject::setAcc(vec3 newacc)			{ acc = newacc; 
						          props["acceleration"] = fizdatum(0.0, acc, VECTOR);
							}

const vec3 FizObject::getOme() 				{ return ome; }
vec3& FizObject::rgetOme() 				{ return ome; }
void FizObject::setOme(vec3 newome) 			{ ome = newome; 
							  props["angular_velocity"] = fizdatum(0.0, ome, VECTOR); 
							}

const vec3 FizObject::getAlp() 				{ return alp; }
vec3& FizObject::rgetAlp() 				{ return alp; }
void FizObject::setAlp(vec3 newalp)			{ alp = newalp; 
							  props["angular_acceleration"] = fizdatum(0.0, alp, VECTOR);
							}
	
const std::vector<triangle> FizObject::getVertices()		{ return vertices; }
std::vector<triangle>& FizObject::rgetVertices() 		{ return vertices; }
void FizObject::setVertices(std::vector<triangle> newvertices) 	{ vertices = newvertices; }
		

const Quaternion FizObject::getQuaternion() 		{ return quaternion; }
Quaternion& FizObject::rgetQuaternion()			{ return quaternion; }
void FizObject::setQuaternion(Quaternion newquat)	{ quaternion = newquat;	}
		
const double[] FizObject::getInertiaTensor()		{ return inertiaTensor; }
double[] FizObject::rgetInertiaTensor()			{ return inertiaTensor; }
void FizObject::setInertiaTensor(double[] newtensor)	{
       							 if(sizeof(newtensor) / sizeof(double) == 6)	
							 {
								delete[] inertiaTensor; 
								inertiaTensor = newtensor;
							 }
							 else
								throw std::invalid_argument("Tensor array must be of length 6");
							
							}
                
const double[] FizObject::getInertiaTensorInv()    	       	{ return inertiaTensor; }
double[] FizObject::rgetInertiatensor()                		{ return inertiaTensorInv; }
void FizObject::setInertiaTensorInv(double[] newtensor)  	{
       								 if(sizeof(newtensor) / sizeof(double) == 6)	
								 {
									delete[] inertiaTensorInv;
									inertiaTensorInv = newtensor;
								 }
								 else
									 throw std::invalid_argument("Tensor array must be of length 6");
							
								}
		
double FizObject::getMass()				{ return mass; }
double& FizObject::rgetMass()				{ return mass; }
void FizObject::setMass(double newmass)			{ mass = newmass; 
      						          props["mass"] = fizdatum(mass, vec3(), SCALAR);
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

const FizObject::triangle getCOMTriangle()		{ return comtriangle; }
triangle& FizObject::rgetCOMTriangle();			{ return comtriangle; }
void FizObject::setCOMTriangle(triangle tri);		{ comtriange = tri; }

bool FizObject::comApprox()	{ return comapprox; }

#endif




