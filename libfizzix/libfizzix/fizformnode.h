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

#ifndef FIZFORMNODE_H
#define FIZFORMNODE_H

#include <vector>
#include <stack>

#include "fizobject.h"
class FizEngine;

/** @class FizFormNode fizformnode.h "libfizzix/src/fizformnode.h"
 *  @brief Objects of this class can be added to a FizStack and evaluated.
 *
 *  All operators and operands extend this class. A node is a single part of a
 *  FizFormula. It may take data from the objects themselves or the engine
 *  (getters), the formula's stack (operators), or from themselves and how they
 *  are constructed (anonymous constants). What they have in common is that
 *  they can all be evaluated. Evaluating the first node should evaluate the
 *  entire formula.
 */
class FizFormNode 
{
	protected:
		FizEngine* eng; // Where to get global data, like named constants
	public:
		FizFormNode();
		virtual const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2); // Gets the value of the node
		void setEngine(FizEngine* e); // Sets the engine that the node should use for global data
		virtual const std::string toString (fizstack& stack); // Converts the node to a string 
		static std::string token; // A short string that is the function name (token) of the node.
};

#endif
