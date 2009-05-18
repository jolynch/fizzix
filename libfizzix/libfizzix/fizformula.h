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

#ifndef FIZFORMULA_H
#define FIZFORMULA_H

#include <vector>
#include <string>
#include <stack>

#include "fizformnode.h"
#include "fizformoperator.h"
#include "fizformanonconst.h"
#include "fizformget.h"
//#include "fizformvariable.h"

class FizFormula
{
	protected:
		//std::vector<FizFormNode> stack; /* This is not a stack because a stack would be destroyed upon evaluation */
		fizstack stack; //various operators pop different number of operands off the stack, and you can't just do current++
		bool symmetric;
	public:
		FizFormula();
		/* Constructs a new FizFormula with the given node stack */
		//FizFormula(std::vector<FizFormNode> stack);
		FizFormula(const fizstack stk);
		/* Evaluate the formula between two FizObjects */
		const fizdatum eval(const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		//const std::vector<FizFormNode> getStack();
		const fizstack getStack();
		fizstack&  rgetStack();
		bool isSymmetric();
		std::string toString();
};

#endif
