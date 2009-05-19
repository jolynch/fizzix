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
	//The pointer is so that the default vertices don't die after the constructor
std::cout << "YO YO";
	this->init("UnNamed", color, *(new std::vector<triangle*>()), 1);
}
	
//Constructor that inits the name
FizObject::FizObject(std::string newname, double mass) 
{
	vec3 color(64.0,64.0,64.0);
	this->init(newname, color, *(new std::vector<triangle*>()), mass);
}

//Constructor that inits the name, color and possibly the smoothity
FizObject::FizObject(std::string newname, vec3 color, double mass)
{
	this->init(newname,color, *(new std::vector<triangle*>()), mass);
}

// Constructor that inits the name and vertices and possibly the smoothity
FizObject::FizObject(std::string newname, std::vector<triangle*> new_vertices, double mass) 
{
	vec3 color(64.0, 64.0, 64.0);
	this->init(newname,color,new_vertices, mass);
}

// Constructor that inits the vertices, color, and smoothity
FizObject::FizObject(std::string newname, vec3 color, std::vector<triangle*> new_vertices, double mass)
{
	this->init(newname, color, new_vertices, mass);
}

// Init the object
void FizObject::init(std::string new_name, vec3 color, const std::vector<triangle*>& tinit, double new_mass)
{
	inertiaTensor.resize(6);
	inertiaTensorInv.resize(6);
std::cout << tinit.size();
	this->init_object(new_name,color,tinit, new_mass);
	this->compute();
	this->adjustMasses();
	this->computeBounds();
}

/** Initialized the structure, used by constructors
 */
void FizObject::init_object(std::string new_name, vec3 color, const std::vector<triangle*>& tinit, double new_mass) 
{
	name = new_name;
	vertices = tinit;
	props["SYSTEM_color"] = fizdatum(0.0, color, VECTOR);
	setMass(new_mass);
	vertex v = vertex();
	triangle com = triangle(&v,&v,&v,0); //hopefully this line works correctly
	com.massp = 1;
	setCOMTriangle(com);
	comapprox = 1;
	setVel(vec3());
	setAcc(vec3());
	setOme(vec3());
	setAlp(vec3());
}

/** Next two methods complements to Game Physics, 2nd Edition, by David H Eberly,
 *  Chapter 2.5, Momenta
 *:q

 *  These formulas found on pg 75 - 79
 */

void FizObject::sub_compute(const double& w0, const double& w1, const double& w2, 
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
		triangle& t = *vertices[i];
		sub_compute(t[0][0], t[1][0], t[2][0], f1x, f2x, f3x, g0x, g1x, g2x);
		sub_compute(t[0][1], t[1][1], t[2][1], f1y, f2y, f3y, g0y, g1y, g2y);
		sub_compute(t[0][2], t[1][2], t[2][2], f1z, f2z, f3z, g0z, g1z, g2z);
		const vec3& d = t.normal;
		t.massp = d[0] * f1x;
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


	setProperty("temp_mass", fizdatum(getMass()));
	setMass(integral[0]); 
	setPos(vec3(integral[1]/mass, integral[2]/mass, integral[3]/mass));
	
	//xx,yy,zz,xy,yz,xz
	std::vector<double> tempI(6,0.0);
	std::vector<double> tempIi(6,0.0);
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

void FizObject::adjustMasses()
{
	std::map<vertex*,bool> vlist;
	for(int i=0; i<vertices.size();i++)
	{	
		triangle& t = *vertices[i];
		t.massp = t.massp / mass;
		for(int j =0; j<3;j++)
		{
			if(vlist.find(&(t[j])) == vlist.end())
			{
				t[j].p -= pos;
				vlist[&(t[j])] = true;
			}
		}
	}	

	setMass(getProperty("temp_mass").scalar);
	removeProperty("temp_mass");
}


void FizObject::computeBounds()
{
	maxrad = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			double r = sqrt(pow((*vertices[i])[j][0],2) + pow((*vertices[i])[j][1],2) + pow((*vertices[i])[j][2],2));
			if (r > maxrad) maxrad = r;
		}
	}
}

const fizdatum FizObject::operator[](const std::string& key) const
{
	return getProperty(key);
}

bool FizObject::contains(const std::string& key) const
{ 
	return props.count(key) != 0; 
}

//Getters and setters
const vec3 FizObject::getPos() const			{ return pos; }
vec3& FizObject::rgetPos() 				{ return pos; }
void FizObject::setPos(vec3 newpos)			{ pos = newpos; 
							  props["SYSTEM_position"] = fizdatum(0.0, pos, VECTOR); 
							}

const vec3 FizObject::getVel() const 			{ return vel; }
vec3& FizObject::rgetVel() 				{ return vel; }
void FizObject::setVel(vec3 newvel) 			{ vel = newvel; 
							  props["SYSTEM_velocity"] = fizdatum(0.0, vel, VECTOR);
							}

const vec3 FizObject::getAcc() const 			{ return acc; }
vec3& FizObject::rgetAcc() 				{ return acc; }
void FizObject::setAcc(vec3 newacc)			{ acc = newacc; 
						          props["SYSTEM_acceleration"] = fizdatum(0.0, acc, VECTOR);
							}

const vec3 FizObject::getOme() const 			{ return ome; }
vec3& FizObject::rgetOme() 				{ return ome; }
void FizObject::setOme(vec3 newome) 			{ ome = newome; 
							  props["SYSTEM_angular_velocity"] = fizdatum(0.0, ome, VECTOR); 
							}

const vec3 FizObject::getAlp() const 			{ return alp; }
vec3& FizObject::rgetAlp() 				{ return alp; }
void FizObject::setAlp(vec3 newalp)			{ alp = newalp; 
							  props["SYSTEM_angular_acceleration"] = fizdatum(0.0, alp, VECTOR);
							}
	
const std::vector<triangle*> FizObject::getVertices() const	{ return vertices; }
std::vector<triangle*>& FizObject::rgetVertices() 		{ return vertices; }
void FizObject::setVertices(std::vector<triangle*> newvertices) 	{ 
								  vertices = newvertices;
								  init(this->getName(), props["SYSTEM_color"].vector, newvertices, this->getMass());
								}
		

const Quaternion FizObject::getQuaternion() const 	{ 
std::cout<<"HM NOW QUATERNION: "<<quaternion[0]<<" "<<quaternion[1]<<" "<<quaternion[2]<<" "<<quaternion[3]<<std::endl;
						return this->quaternion; }
Quaternion& FizObject::rgetQuaternion()			{ 
std::cout<<"OH SNAP RQUATERNION: "<<quaternion[0]<<" "<<quaternion[1]<<" "<<quaternion[2]<<" "<<quaternion[3]<<std::endl;

return this->quaternion; }
void FizObject::setQuaternion(Quaternion newquat)	{ 
std::cout<<"SETTING QUATERNION: "<<newquat[0]<<" "<<newquat[1]<<" "<<newquat[2]<<" "<<newquat[3]<<std::endl;
							  quaternion = newquat;	
							}

const std::vector<double> FizObject::getInertiaTensor() const	{ return inertiaTensor; }
std::vector<double>& FizObject::rgetInertiaTensor()		{ return inertiaTensor; }
void FizObject::setInertiaTensor(std::vector<double> newtensor)	{ 
							  	if(newtensor.size() == 6)
									inertiaTensor = newtensor; 
							  	else
									throw std::invalid_argument("Inertia Tensors are size 6 because they are symmetric");
								}

           
const std::vector<double> FizObject::getInertiaTensorInv() const	{ return inertiaTensorInv; }
std::vector<double>& FizObject::rgetInertiaTensorInv()			{ return inertiaTensorInv; }
std::vector<double> FizObject::getInertiaTensorInvWorld()	
{
	std::vector<double> r = quaternion.toRotationMatrix();
	std::vector<double>& i = inertiaTensorInv;
	std::vector<double> RIR(6,0.0);
	/*Manual multipliation of R * I^-1 * R^t\
	  R = 	[A,B,C]
	  	[D,E,F]
		[G,H,I]
	  I =	[U,W,Z]
	  	[W,V,Y]
		[Z,Y,X]
	  Rt = 	[A,D,G]
	  	[B,E,H]
		[C,F,I]
	  R * I * Rt =
	  [A*(C*Z+B*W+A*U)+C*(A*Z+B*Y+C*X)+B*(C*Y+A*W+B*V),A*(F*Z+E*W+D*U)+C*(D*Z+E*Y+F*X)+B*(F*Y+D*W+E*V),A*(I*Z+H*W+G*U)+C*(G*Z+H*Y+I*X)+B*(I*Y+G*W+H*V)]
	  [D*(C*Z+B*W+A*U)+F*(A*Z+B*Y+C*X)+E*(C*Y+A*W+B*V),D*(F*Z+E*W+D*U)+F*(D*Z+E*Y+F*X)+E*(F*Y+D*W+E*V),D*(I*Z+H*W+G*U)+F*(G*Z+H*Y+I*X)+E*(I*Y+G*W+H*V)]
	  [G*(C*Z+B*W+A*U)+I*(A*Z+B*Y+C*X)+H*(C*Y+A*W+B*V),G*(F*Z+E*W+D*U)+I*(D*Z+E*Y+F*X)+H*(F*Y+D*W+E*V),G*(I*Z+H*W+G*U)+I*(G*Z+H*Y+I*X)+H*(I*Y+G*W+H*V)]
	 */
	RIR[0] = r[0] * (r[2] * i[5] +r[1]*i[3]+r[0]*i[0])+r[2]*(r[0]*i[5]+r[1]*i[4]+r[2]*i[2])+r[1]*(r[2]*i[4]+r[0]*i[3]+r[1]*i[1]);
	RIR[1] = r[3] * (r[5] * i[5] +r[4]*i[3]+r[3]*i[0])+r[5]*(r[3]*i[5]+r[4]*i[4]+r[5]*i[2])+r[4]*(r[5]*i[4]+r[3]*i[3]+r[4]*i[1]); 
	RIR[2] = r[6] * (r[8] * i[5] +r[7]*i[3]+r[6]*i[0])+r[8]*(r[6]*i[5]+r[7]*i[4]+r[8]*i[2])+r[7]*(r[8]*i[4]+r[6]*i[3]+r[7]*i[1]); 
	RIR[3] = r[0] * (r[5] * i[5] +r[4]*i[3]+r[3]*i[0])+r[2]*(r[3]*i[5]+r[4]*i[4]+r[5]*i[2])+r[1]*(r[5]*i[4]+r[3]*i[3]+r[4]*i[1]);
	RIR[4] = r[3] * (r[8] * i[5] +r[7]*i[3]+r[6]*i[0])+r[5]*(r[6]*i[5]+r[7]*i[4]+r[8]*i[2])+r[4]*(r[8]*i[4]+r[6]*i[3]+r[7]*i[1]);
	RIR[5] = r[0] * (r[8] * i[5] +r[7]*i[3]+r[6]*i[0])+r[2]*(r[6]*i[5]+r[7]*i[4]+r[8]*i[2])+r[1]*(r[8]*i[4]+r[6]*i[3]+r[7]*i[1]);
	return RIR;
}
void FizObject::setInertiaTensorInv(std::vector<double> newtensor)	{
									if(newtensor.size() == 6)
										inertiaTensorInv = newtensor; 
									else
										throw std::invalid_argument("Inertia Tensors are size 6 because they are symmetric");
									}
double FizObject::getMass()	const			{ return mass; }
double& FizObject::rgetMass()				{ return mass; }
void FizObject::setMass(double newmass)			{ 
							  for(int i=0;i<6;i++)
							  {
							  	inertiaTensor[i] = (newmass / mass) * inertiaTensor[i]; 
							  	inertiaTensorInv[i] = (newmass / mass) * inertiaTensorInv[i]; 
							  } 
							  mass = newmass; 
      						          props["SYSTEM_mass"] = fizdatum(mass, vec3(), SCALAR);
							}

const std::string FizObject::getName() const		{ return name; }
void FizObject::setName(std::string newname)		{ name = newname;}


std::vector<std::string> FizObject::getSetProperties() const
{
	std::vector<std::string> v;
	for(std::map<std::string, fizdatum>::const_iterator it = props.begin();	it != props.end();	++it)
		{v.push_back(it->first);}
	return v;
}

fizdatum FizObject::getProperty(std::string key) const
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
	if(key=="SYSTEM_mass")
	{
		setMass(value.scalar);
		return;
	}
	if(key=="SYSTEM_position")
	{
		setPos(value.vector);
		return;
	}
	if(key=="SYSTEM_velocity")
	{
		setVel(value.vector);
		return;
	}
	if(key=="SYSTEM_acceleration")
	{
		setAcc(value.vector);
		return;
	}
	if(key=="SYSTEM_angular_velocity")
	{
		setOme(value.vector);
		return;
	}
	if(key=="SYSTEM_angular_acceleration")
	{
		setAlp(value.vector);
		return;
	}
	props[key] = value;
}

int FizObject::removeProperty(std::string key)
{
	return props.erase(key);
}

const triangle FizObject::getCOMTriangle() const	{ return comtriangle; }
triangle& FizObject::rgetCOMTriangle()			{ return comtriangle; }
void FizObject::setCOMTriangle(triangle tri)		{ comtriangle = tri; }

bool FizObject::comApprox()	{ return comapprox; }

double FizObject::getMaxRad() const			{ return maxrad; }
double& FizObject::rgetMaxRad()				{ return maxrad; }
void FizObject::setMaxRad(double newmax)		{ maxrad = newmax; }

#endif




