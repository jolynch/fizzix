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

vec3[] FizForce::eval(FizObject& obj1, FizObject& obj2)
{
	vec3[4] result;
	std::vector<triangle>& tris1 = obj1.rgetVertices();
	std::vector<triangle>& tris2 = obj2.rgetVertices();
	for (int i = 0; i < tris1.size(); i++)
	{
		vec3 force;
		fizdatum form = formula.eval(obj1, tris1[i], obj2);
		if (form.type == VECTOR) force = form.vector;
		else if (form.type == SCALAR)
		{
			force = obj2.getPos()-obj1.getPos();
			force /= force.mag(); //rhat
			force *= form.scalar;
		}
		else force = vec3();
		result[0] += force;
		result[1] += force.cross((tris1[i].vertices[0].p+tris1[i].vertices[1].p+tris1[i].vertices[2].p)/3);
	}
	if (symmetric) result[2] = result[0];
	for (int i = 0; i < tris2.size(); i++)
	{
		vec3 force;
		fizdatum form = formula.eval(obj2, tris2[i], obj2);
		if (form.type == VECTOR) force = form.vector;
		else if (form.type == SCALAR)
		{
			force = obj1.getPos()-obj2.getPos();
			force /= force.mag(); //rhat
			force *= form.scalar;
		}
		else force = vec3();
		if (!symmetric) result[2] += force; //this doesn't actually help with our current implementation...
		result[3] += force.cross((tris2[i].vertices[0].p+tris2[i].vertices[1].p+tris2[i].vertices[2].p)/3);
	}
	return result;
}

#endif