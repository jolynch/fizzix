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
#ifndef FIZFORMGETPROP_CPP
#define FIZFORMGETPROP_CPP

#include "getters.h"

using namespace std;

FizFormGetProp::FizFormGetProp(string id)
{
	identifier = id;
}
FizFormGetProp::FizFormGetProp(string id, bool first)
{
	identifier = id;
	firstobject = first;
}
FizFormGetProp::FizFormGetProp(string id, string name)
{
	identifier = id;
	objectname = name;
}

const fizdatum FizFormGetProp::eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2)
{
cout << "GONNA GET A PROPERTY CALLED " << identifier << '\n';
	fizdatum a;
	if (objectname != "") a = eng->getPropVal(objectname, identifier);
	else
	{
		bool dist = eng->propdist.count(identifier)==1;
		if (firstobject)
		{
			a = obj1.getProperty(identifier);
			if (dist)
			{
				if (a.type == SCALAR) a.scalar *= tri1.massp;
				else a.vector *= tri1.massp;
			}
		}
		else
		{
			a = obj2.getProperty(identifier);
			if (dist)
			{
				if (a.type == SCALAR) a.scalar *= tri2.massp;
				else a.vector *= tri2.massp;
			}
		}
	}
	return a;
}

const std::string FizFormGetProp::toString(fizstack& stack)
{
	if (objectname != "") return "#"+objectname+"."+identifier;
	else if (firstobject) return "$"+identifier;
	else return "@"+identifier;
}

#endif
