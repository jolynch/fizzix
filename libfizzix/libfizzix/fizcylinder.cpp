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
#ifndef FIZCYLINDER_CPP
#define FIZCYLINDER_CPP

#include "fizcylinder.h"

//Default constructor
FizCylinder::FizCylinder()
{
	this->init("UnNamedCylinder", vec3(64.0, 64.0, 64.0), *(new std::vector<triangle>()), 1, 1, 1); //default is rad=1, height=1
}

//Constructor that inits the name and dimensions
FizCylinder::FizCylinder(std::string newname, double mass, double rad, double h)
{
	this->init(newname, vec3(64.0, 64.0, 64.0), *(new std::vector<triangle>()), mass, rad, h);
}

//Constructor that inits the name, color, and dimensions
FizCylinder::FizCylinder(std::string newname, vec3 color, double mass, double rad, double h)
{
	this->init(newname, color, *(new std::vector<triangle>()), mass, rad, h);
}

//Constructor that inits the name, triangles, and dimensions
FizCylinder::FizCylinder(std::string newname, std::vector<triangle> new_vertices, double mass, double rad, double h)
{
	this->init(newname, vec3(64.0, 64.0, 64.0), new_vertices, mass, rad, h);
}

//Constructor that inits the name, color, triangles, and dimensions
FizCylinder::FizCylinder(std::string newname, vec3 color, std::vector<triangle> new_vertices, double mass, double rad, double h)
{
	this->init(newname, color, new_vertices, mass, rad, h);
}

void FizCylinder::init(std::string name, vec3 color, const std::vector<triangle>& new_vertices, double mass, double rad, double h)
{
	inertiaTensor.resize(6);
	inertiaTensorInv.resize(6);
	this->init_object(name,color,new_vertices, mass, rad, h);
	this->compute();
	this->adjustMasses();
	this->computeBounds();
}

void FizCylinder::init_object(std::string name, vec3 color, const std::vector<triangle>& tinit, double mass, double rad, double h)
{
	this->name = name;
	vertices = tinit;
	setProperty("color", fizdatum(0.0, color, VECTOR));
	setRadius(rad);
	setHeight(h);
	setMass(mass);
}

void FizCylinder::computeBounds()
{
	maxrad = sqrt(pow(radius,2)+pow((height/2),2));
}

void FizCylinder::compute()
{
	/**computing masses of triangles copied from FizObject
	*/
	double integral[4] = {0.0, 0.0, 0.0, 0.0};
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
		t.massp = d[0] * f1x;
		integral[0] += d[0] * f1x;
		integral[1] += d[0] * f2x;
		integral[2] += d[1] * f2y;
		integral[3] += d[2] * f2z;
	}

	integral[0] *= div_consts[0];
	integral[1] *= div_consts[1];
	integral[2] *= div_consts[1];
	integral[3] *= div_consts[1];

	setProperty("temp_mass", fizdatum(getMass()));
	setMass(integral[0]); 
	setPos(vec3(integral[1]/mass, integral[2]/mass, integral[3]/mass));
	/**end copied code
	*/
	
	std::vector<double> tempI(6,0.0);
	std::vector<double> tempIi(6,0.0);
	tempI[0] = tempI[1] = 1/12*mass*(3*pow(radius,2)+pow(height,2));
	tempI[2] = 1/2*mass*pow(radius,2);
	tempI[4] = tempI[5] = tempI[3] = 0;
	tempIi[0] = tempIi[1] = 1/tempI[0];
	tempIi[2] = 1/tempI[2];
	tempIi[3] = tempIi[4] = tempIi[5] = 0;
	setInertiaTensor(tempI);
	setInertiaTensorInv(tempIi);
}

double FizCylinder::getRadius() const			{ return radius; }
double& FizCylinder::rgetRadius()			{ return radius; }
void FizCylinder::setRadius(double newradius)		{ radius = newradius; 
      						          props["radius"] = fizdatum(radius, vec3(), SCALAR);
							}

double FizCylinder::getHeight() const			{ return height; }
double& FizCylinder::rgetHeight()			{ return height; }
void FizCylinder::setHeight(double newheight)		{ height = newheight; 
      						          props["height"] = fizdatum(height, vec3(), SCALAR);
							}
							
void FizCylinder::setVertices(std::vector<triangle> newvertices)	{
									  vertices = newvertices;
									  init(this->getName(), props["color"].vector, newvertices, this->getMass(), this->getRadius(), this->getHeight());
									}

#endif
