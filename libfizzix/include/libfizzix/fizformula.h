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
#include <stack>

#include "gen_structs.h"
#include "fizformnode.h"
#include "fizformoperator.h"
#include "fizformanonconst.h"
#include "fizformvariable.h"

class FizFormula
{
	protected:
		//std::vector<FizFormNode> stack; /* This is not a stack because a stack would be destroyed upon evaluation */
		std::stack<FizFormNode> stack; //various operators pop different number of operands off the stack, and you can't just do current++
		std::stack<FizFormNode> stackCopy; //created and destroyed upon every evaluation
	public:
		/* Constructs a new FizFormula with the given node stack */
		//FizFormula(std::vector<FizFormNode> stack);
		FizFormula(const std::stack<FizFormNode> stack) : stackCopy(stack) {};
		/* Evaluate the formula between two FizObjects */
		const fizdatum eval(const FizObject& obj1, const FizObject& obj2);
		//const std::vector<FizFormNode> getStack();
		const std::stack<FizFormNode> getStack();
};

#endif
