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
#ifndef QUOTIENT_CPP
#define QUOTIENT_CPP

#include "operators.h"
using namespace FizOper;
std::string Quotient::token = "/";

using namespace std;

Quotient::Quotient(int numOperands)
{
	Quotient::numOperands=numOperands;
	description="Finds the quotient of scalars and at most one vector (as the numerator)";
}

const fizdatum Quotient::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum quotient = fizdatum(1);
	fizdatum next;
	for(int i = 0; i < numOperands-1; i++)
	{
		next = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);

		if(next.type == SCALAR) quotient.scalar /= next.scalar;
		else if (next.type == NIL) return fizdatum();
		else throw logic_error("Cannot have a vector in denominator");
		
	}
	if (numOperands > 0)
	{
		next = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);

		if(next.type == SCALAR) quotient.scalar *= next.scalar;
		else if (next.type == NIL) return fizdatum();
		else
		{
			quotient.type = VECTOR;
			quotient.vector[0] = next.vector[0]/quotient.scalar;
			quotient.vector[1] = next.vector[1]/quotient.scalar;
			quotient.vector[2] = next.vector[2]/quotient.scalar;
		}
	}
	return quotient;
}

#endif

