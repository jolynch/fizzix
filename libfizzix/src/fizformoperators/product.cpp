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

#include "../../include/libfizzix/operators.h"

using namespace std;

Product::Product(int numOperands)
{
	Product::numOperands=numOperands;
	token="mult";
	description="Finds the product of scalars and at most one vector";
}

const fizdatum Product::eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2)
{
	fizdatum product=stack.pop().eval(stack,obj1,obj2);
	fizdatum next;
	if (product.type == NIL) return product;
	for(int i=1;i<numOperands;i++)
	{
		next=stack.pop().eval(stack,obj1,obj2);

		if(product.type == VECTOR)
		{
			if(next.type == SCALAR)
			{
				product.vector[0]*=next.scalar;
				product.vector[1]*=next.scalar;
				product.vector[2]*=next.scalar;
			}
			else if (next.type == NIL) return  fizdatum();
			else throw logic_error("Cannot use scalar multiplication on multiple vectors.");
		}
		else if (product.type == SCALAR)
		{
			if(next.type == SCALAR) product.scalar *= next.scalar;
			else if (next.type == NIL) return fizdatum();
			else
			{
				product.type = VECTOR;
				product.vector[0] = product.scalar*next.vector[0];
				product.vector[1] = product.scalar*next.vector[1];
				product.vector[2] = product.scalar*next.vector[2];
			}
		}
	}
	return product;
}
