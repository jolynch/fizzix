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
#include <cmath>
#include <cstdlib>

#include "../fizformoperator.h"

namespace FizOper
{
	class Dot: public FizFormOperator
	{	public: Dot(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Cross: public FizFormOperator
	{	public: Cross(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	
	class Sum: public FizFormOperator
	{	public: Sum(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Difference: public FizFormOperator
	{	public: Difference(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Product: public FizFormOperator
	{	public: Product(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Quotient: public FizFormOperator
	{	public: Quotient(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	
	class Cosine: public FizFormOperator
	{	public: Cosine(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Sine: public FizFormOperator
	{	public: Sine(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Tangent: public FizFormOperator
	{	public: Tangent(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Arcsin: public FizFormOperator
	{	public: Arcsin(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Arccos: public FizFormOperator
	{	public: Arccos(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Arctan: public FizFormOperator
	{	public: Arctan(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Sinh: public FizFormOperator
	{	public: Sinh(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Cosh: public FizFormOperator
	{	public: Cosh(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Tanh: public FizFormOperator
	{	public: Tanh(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	
	class Factorial: public FizFormOperator
	{	public: Factorial(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Magnitude: public FizFormOperator
	{	public: Magnitude(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Square: public FizFormOperator
	{	public: Square(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Exponent: public FizFormOperator
	{	public: Exponent(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Exponentiate: public FizFormOperator
	{	public: Exponentiate(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Random: public FizFormOperator
	{	public: Random(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Vectorize: public FizFormOperator
	{	public: Vectorize(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
	class Logarithm: public FizFormOperator
	{	public: Logarithm(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle tri1, const FizObject& obj2);
	};
}
