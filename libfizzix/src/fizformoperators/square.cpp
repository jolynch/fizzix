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
using namespace FizOper;

Square::Square(int numOperands)
{
	this->numOperands=numOperands;
	description = "Takes the square of a scalar.";
	token = "square";
}

const fizdatum Square::eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2)
{
	fizdatum a = stack.pop()->eval(stack, obj1, tri1, obj2);
	fizdatum b;
	b.type = SCALAR;
	if (a.type == SCALAR) b.scalar = a.scalar*a.scalar;
	else if (a.type == NIL) b = fizdatum();
	else throw std::logic_error("Cannot square a vector.");
	return b;
}
