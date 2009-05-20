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

#ifndef FIZFORMOPERATOR_H
#define FIZFORMOPERATOR_H

#include <vector>
#include <stack>
#include <string>

#include "fizformnode.h"

// Outlines an operator, extending node to provide a way to store the number of operands as well as some help text.
namespace FizOper
{
	class FizFormOperator:public FizFormNode 
	{
		protected:
			int numOperands; // The number of parameters the function takes
			std::string description; // "Help" text
		public:
			virtual const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2) =0; // Gets the value of the node
			virtual const std::string toString(fizstack& stack) =0;
	};
	//std::string FizFormOperator::token = "generic_operator";
}

#endif
