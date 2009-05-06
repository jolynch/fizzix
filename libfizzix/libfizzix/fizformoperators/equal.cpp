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
#ifndef EQUAL_CPP
#define EQUAL_CPP

#include "operators.h"
using namespace FizOper;

using namespace std;

Equal::Equal(int numOperands)
{
	Equal::numOperands=numOperands;
	description="Returns true if all arguments are equal";
}

const fizdatum Equal::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum a = fizdatum(1);
	fizdatum b = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
	if (b.type == NIL) a = fizdatum();
	for (int i = 1; i < numOperands; i++)
	{
		fizdatum c = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
		if (a.type == SCALAR && a.scalar != 0)
		{
			if (c.type == NIL) a = fizdatum();
			else if (c.type == b.type)
			{
				if (c.type == VECTOR)
				{
					a.scalar = (c.vector[0]==b.vector[0] && c.vector[1]==b.vector[1] && c.vector[2]==b.vector[2])?1:0;
				}
				else a.scalar = (c.scalar == b.scalar)?1:0;
			}
			else a.scalar = 0;
		}
	}
	return a;
}


#endif

