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
#ifndef AND_CPP
#define AND_CPP

#include "operators.h"
using namespace FizOper;

using namespace std;

std::string And::token = "&";

And::And(int numOperands)
{
	And::numOperands=numOperands;
	description="Returns true if supplied\"booleans\" are all true";
}

const fizdatum And::eval(fizstack& stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum a = fizdatum(1.0);
	for (int i = 0; i < numOperands; i++)
	{
		fizdatum b = stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
		if (b.type == SCALAR)
		{
			if (a.scalar != 0) a.scalar = b.scalar;
		}
		else if (b.type == NIL)
			a = fizdatum();
		else throw std::logic_error("Cannot && non-booleans");
	}
	return a;
}

const std::string And::toString(fizstack& stack)
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

