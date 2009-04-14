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
#ifndef FIZFORMVARIABLE_CPP
#define FIZFORMVARIABLE_CPP

#include "../include/libfizzix/fizformvariable.h"

using namespace std;

FizFormVariable::FizFormVariable(Type2 varType,string id) : variableType(varType),identifier(id) {};

const fizdatum FizFormVariable::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
	fizdatum a;
	switch (variableType)
	{
		case PROPERTY1:
			try
			{
				a = obj1[identifier]; //fetches the property of object 1
				if (eng->propdist[identifier])
					if (a.type == SCALAR) a.scalar *= tri1.massp; //if it is a distributed property, such as mass, multiplies the property by the correct multiplication factor for the given triangle
			}
			catch (out_of_range)
			{
				a = fizdatum(); //returns a fizdatum of type NIL
			}
			break;
		case PROPERTY2:
			try
			{
				a = obj2[identifier]; //properties of the second object are for the whole object, since forces are calculated iterating over the first object, to the center of mass of the second
			}
			catch (out_of_range)
			{
				a = fizdatum();
			}
			break;
		case PROPERTYJOINT: 
			a = eng->pcache[identifier]; //fetches value from property cache
			break;
		case FORCE:
			a = eng->fcache[identifier]; //fetches value from force cache
			if (a.type == NIL)
			{	a = eng->forces[identifier]->eval(); //if not in cache, evaluates and stick s it in -- JOEY can you make fizengine.forces public?
				eng->forces.insert(/*pair something something*/);
			}
			break;
		case NAMEDCONST:
			a = eng->ccache[identifier]; //fetches from constant cache
		default: throw new logic_error("wtf"); break;
	}
}

#endif
