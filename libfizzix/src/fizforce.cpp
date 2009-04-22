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

#ifndef FIZFORCE_CPP
#define FIZFORCE_CPP

#include "../include/libfizzix/fizforce.h"

vec3 FizForce::getForce(FizObject& obj1, triangle& tri1, FizObject& obj2, triangle& tri2)
{
	vec3 force;
	fizdatum form = formula.eval(obj1, tri1, obj2, tri2);
	if (form.type == SCALAR)
	{
		force = obj2.getPos() - obj1.getPos(); //F on obj 1
		force /= force.mag(); //force = rhat
		force *= form.scalar;
	}
	else if (form.type == VECTOR) force = form.vector;
	else force = vec3();
	return force;
}

bool FizForce::isSymmetric()
{
	return symmetric;
}

/*vec3[] FizForce::eval(FizObject& obj1, FizObject& obj2)
{
	vec3[4] result; //Force on obj1, Torque on obj1, F on obj2, T on obj2
	std::vector<triangle>& tris1 = obj1.rgetVertices();
	std::vector<triangle>& tris2 = obj2.rgetVertices();
	vec3 force;
	
	//need a COM triangle in each object
	if (obj1.comapprox) //if object 1 can be approximated as at its COM
	{
		if (obj2.comapprox)
		{
			force = getForce(obj1, obj1.comtriangle, obj2, obj2.comtriangle);
			result[0] += force;
			if (symmetric) result[2] -= force; //opposite direction
			else
			{
				eng->clearNonsymmetricCaches();
				force = getForce(obj2, obj2.comtriangle, obj1, obj1.comtriangle);
				result[2] += force;
			}
			//no torque for obj1 nor obj2
		}
		else
		{
			for (int j = 0; j < tris2.size(); j++)
			{
				eng->clearDistributedCaches();
				force = getForce(obj1, obj1.comtriangle, obj2, tris2[j]);
				result[0] += force;
				//no torque for obj1
				if (symmetric) result[2] -= force;
				else
				{
					eng->clearNonsymmetricCaches();
					force = getForce(obj2, tris2[j], obj1, obj1.comtriangle);
					result[2] += force;
				}
				vec3 radius = (tris2[j].vertices[0].p + tris2[j].vertices[1].p + tris2[j].vertices[2].p)/3; //vector from center of object to center of triangle
				result[3] += force.cross(radius); //T = F x r
			}
		}
	}
	else
	{
		for (int i = 0; i < tris1.size(); i++)
		{
			if (obj2.comapprox)
			{
				eng->clearDistributedCaches();
				force = getForce(obj1, tris1[i], obj2, obj2.comtriangle);
				result[0] += force;
				vec3 radius = (tris1[i].vertices[0].p + tris1[i].vertices[1].p + tris1[i].vertices[2].p)/3;
				result[1] += force.cross(radius);
				if (symmetric) result[2] -= force;
				else
				{
					eng->clearNonsymmetricCaches();
				
void FizForce::setEngine(FizEngine* e)
{
	eng = e;
}	force = getForce(obj2, obj2.comtriangle, obj1, tris1[i]);
					result[2] += force;
				}
				//no torque for obj2
			}
			else
			{
				for (int j = 0; j < tris2.size(); j++)
				{
					eng->clearDistributedCaches();
					force = getForce(obj1, tris1[i], obj2, tris2[j]);
					result[0] += force;
					vec3 radius = (tris1[i].vertices[0].p + tris1[i].vertices[1].p + tris1[i].vertices[2].p)/3;
					result[1] += force.cross(radius);
					if (symmetric) result[2] -= force;
					else
					{
						eng->clearNonsymmetricCaches();
						force = getForce(obj2, tris2[j], obj1, tris1[i]);
						result[2] += force;
					}
					radius = (tris2[j].vertices[0].p + tris2[j].vertices[1].p + tris2[j].vertices[2].p)/3;
					result[3] += force.cross(radius);
				}
			}
		}
	}
	

	return result;
}*/

#endif
