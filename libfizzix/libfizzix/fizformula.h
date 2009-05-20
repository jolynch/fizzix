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

/** @class FizFormula fizformula.h "libfizzix/src/fizformula.h"
 *  @brief This class stores a prefix formula that can be evaluated.
 *  A FizFormula contains a stack of nodes. Each node, when evaluated, will
 *  return a value and may pop from the stack to deterime this value.
 *  Evaluating a formula tells the first node to evaluate itself, which should
 *  result in the entire formula being evaluated. Formulae return different
 *  results when evaluated using different objects / triangles as input.
 */
class FizFormula
{
	protected:
		fizstack stack; // Stack of nodes
		bool symmetric; // Whether the formula returns the same answer when passed the objects in the reverse order.
		// (saves computation time)
	public:
		FizFormula();
		FizFormula(const fizstack stk); // Constructs a new FizFormula with the given node stack
		const fizdatum eval(const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2); // Evaluate the formula between two FizObjects and their triangles

		// Getters and setters
		const fizstack getStack();
		fizstack&  rgetStack();
		bool isSymmetric();
		std::string toString();
};

#endif
