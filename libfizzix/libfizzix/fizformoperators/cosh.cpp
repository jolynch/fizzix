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
#ifndef COSH_CPP
#define COSH_CPP

#include "operators.h"
using namespace FizOper;
std::string Cosh::token = "cosh";

Cosh::Cosh(int numOperands)
{
	this->numOperands=numOperands;
	description="Takes the hyperbolic cosine of a number.";
}

const fizdatum Cosh::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum c;
	c.type = SCALAR;
	if (numOperands == 1)
	{
		fizdatum a = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);

		if (a.type == SCALAR) c.scalar = cosh(a.scalar);
		else if (a.type == NIL) c = fizdatum();
		else throw std::logic_error("Cannot take the cosh of a vector.");
	}
	else throw std::logic_error("Can only take the cosh of a single value.");
	return c;
}

const std::string Cosh::toString(fizstack& stack)
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

