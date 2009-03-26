/***********************************************************************************************
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

#include <vector>
#include <stack>
#include <string>
#include <stdexcept>

#include "../fizformoperator.h"

namespace FizOper
{	class Dot: public FizFormOperator {};
	class Cross: public FizFormOperator {};
	
	class Sum: public FizFormOperator {};
	class Difference: public FizFormOperator {};
	class Product: public FizFormOperator {};
	class Quotient: public FizFormOperator {};
	
	class Cosine: public FizFormOperator {};
	class Sine: public FizFormOperator {};
	class Tangent: public FizFormOperator {};
	class Arcsin: public FizFormOperator {};
	class Arccos: public FizFormOperator {};
	class Arctan: public FizFormOperator {};
	
	class Factorial: public FizFormOperator{};
	class Magnitude: public FizFormOperator {};
	class Square: public FizFormOperator {};
	class Exponentiate: public FizFormOperator {};
	class Random: public FizFormOperator {};
	class Vectorize: public FizFormOperator {};
	class Logarithm: public FizFormOperator {};
}
