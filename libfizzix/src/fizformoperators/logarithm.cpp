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

#include "operators.h"

Logarithm::Logarithm(int numOperands)
{
	this->numOperands=numOperands;
	description = "Finds the log of a scalar to a base, and takes the natural log if no base is specified.";
	token = "log";
}

const fizdatum Logarithm::eval(std::stack<FizFormNode>& stack, const FizObject& obj1, const FizObject& obj2)
{
	fizdatum c;
	c.type = SCALAR;
	if (numOperands == 1)
	{	fizdatum a = stack.top().eval(stack, obj1, obj2);
		stack.pop();
		if (a.type == SCALAR) c.scalar = log(a.scalar); //natural log
		else throw new std::logic_error("Cannot take the log of a vector.");
	}
	else if (numOperands == 2)
	{	fizdatum b = stack.top().eval(stack, obj1, obj2);
		stack.pop();
		fizdatum a = stack.top().eval(stack, obj1, obj2);
		stack.pop();
		if (a.type == SCALAR && b.type == SCALAR) c.scalar = log(a.scalar)/log(b.scalar);
		else throw new std::logic_error("Cannot take the log of a vector.");
	}
	else throw new std::logic_error("Cannot take a log with multiple bases.");
	return c;
}

