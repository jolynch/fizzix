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
#ifndef DIFFERENCE_CPP
#define DIFFERENCE_CPP

#include "operators.h"
using namespace FizOper;

using namespace std;

FizOper::Difference::Difference(int numOperands)
{
	Difference::numOperands=numOperands;
	description="Finds the difference of scalars or vectors";
}

const fizdatum FizOper::Difference::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum diff=stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
	if (diff.type == NIL) return diff;
	fizdatum next;
	for(int i=1;i<numOperands;i++)
	{
		next=stack.pop()->eval(stack, obj1, tri1, obj2, tri2);
		if(next.type == NIL) return next;
		if(next.type!=diff.type) throw logic_error("Cannot mix scalars and vectors in difference");
		if(diff.type==SCALAR) diff.scalar-=next.scalar; else diff.vector-=next.vector;
	}
	return diff;
}


#endif

