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

#include "fizformula.h"

FizFormula::FizFormula() {stack=fizstack();}

FizFormula::FizFormula(fizstack stk) : stack(stk) {}

const fizdatum FizFormula::eval(const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2)
{

	stack.reset();
	fizdatum a = stack.pop()->eval(stack,obj1,tri1,obj2,tri2); //the stack represents a postfix expression, which is recursively evaluated from the back

	stack.reset();
	return a;
}

const fizstack FizFormula::getStack()
{
	return stack;
}

fizstack& FizFormula::rgetStack()
{
	return stack;
}

bool FizFormula::isSymmetric()
{
	return symmetric;
}

std::string FizFormula::toString()
{
	if(stack.size()==0) return "Formula empty";
	stack.reset();
	std::string oper = stack.pop()->toString(stack);
	stack.reset();	
	return oper;
}
