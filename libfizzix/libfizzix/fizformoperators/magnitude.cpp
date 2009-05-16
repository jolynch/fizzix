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
#ifndef MAGNITUDE_CPP
#define MAGNITUDE_CPP

#include "operators.h"
using namespace FizOper;
std::string Magnitude::token = "mag";

Magnitude::Magnitude(int numOperands)
{
	this->numOperands=numOperands;
	description="Takes the magnitude of a value: absolute value of a scalar, length of a vector.";
}

const fizdatum Magnitude::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum c;
	c.type = SCALAR;
	if (numOperands == 1)
	{
		fizdatum a = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);

		if (a.type == VECTOR)
			c.scalar = sqrt(a.vector[0]*a.vector[0] + a.vector[1]*a.vector[1] + a.vector[2]*a.vector[2]);
		else if (a.type == SCALAR)
			c.scalar = abs(a.scalar);
		else
			c = fizdatum();
	}
	else throw std::logic_error("Cannot take the magnitude of multiple values");
	return c;
}

const std::string Magnitude::toString(fizstack& stack)
{
	std::string val = "";
	for(int i=0;i<numOperands;i++)
	{
		val = " "+stack.pop()->toString(stack) + val;
	}
	val = "("+token+val+")";
	return val;
}

#endif

