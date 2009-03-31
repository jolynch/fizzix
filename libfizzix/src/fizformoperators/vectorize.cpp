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

Vectorize::Vectorize(int numOperands)
{
	this->numOperands=numOperands;
	token="vector";
	description="Takes three scalars and puts them into a vector";
}

const fizdatum Vectorize::eval(std::stack<FizFormNode> &stack, const FizObject &obj1, const FizObject &obj2)
{
	fizdatum c = stack.top().eval(stack, obj1, obj2);
	stack.pop();
	fizdatum b = stack.top().eval(stack, obj1, obj2);
	stack.pop();
	fizdatum a = stack.top().eval(stack, obj1, obj2);
	stack.pop();
	fizdatum d;
	d.type = VECTOR;
	if (c.type == SCALAR && b.type == SCALAR && a.type == SCALAR)
	{
		d.vector[0] = a.scalar;
		d.vector[1] = b.scalar;
		d.vector[2] = c.scalar;
	}
	else throw new std::logic_error("Can only make a vector from three scalars");
}

