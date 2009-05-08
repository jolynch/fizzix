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
#ifndef NOTEQUAL_CPP
#define NOTEQUAL_CPP

#include "operators.h"
using namespace FizOper;
std::string Notequal::token = "!=";

using namespace std;

Notequal::Notequal(int numOperands)
{
	Notequal::numOperands=numOperands;
	description="Returns true if not all arguments are equal";
}

const fizdatum Notequal::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum a;
	a.type = SCALAR;
	if (numOperands == 2)
	{
		fizdatum c = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
		fizdatum b = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
		if (b.type == NIL || c.type == NIL) return fizdatum();
		else if (b.type != c.type) a.scalar = 1;
		else if (b.type == SCALAR) a.scalar = (b.scalar == c.scalar)?0:1;
		else a.scalar = (b.vector[0]!=c.vector[0] || b.vector[1]!=c.vector[1] || b.vector[2]!=c.vector[2])?1:0;
	}
	else throw std::logic_error("Not equals is a binary operator");
	return a;
}

const std::string Notequal::toString(fizstack& stack)
{
	std::string val = "";
	for(int i=0;i<numOperands;i++)
	{
		val = " "+stack.pop()->toString(stack) + val;
	}
	val = "("+token+val+")";
}

#endif

