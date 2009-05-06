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
#ifndef OPERATORS_H
#define OPERATORS_H

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
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Cross: public FizFormOperator
	{	public: Cross(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Sum: public FizFormOperator
	{	public: Sum(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Difference: public FizFormOperator
	{	public: Difference(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Product: public FizFormOperator
	{	public: Product(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Quotient: public FizFormOperator
	{	public: Quotient(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Cosine: public FizFormOperator
	{	public: Cosine(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Sine: public FizFormOperator
	{	public: Sine(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Tangent: public FizFormOperator
	{	public: Tangent(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Arcsin: public FizFormOperator
	{	public: Arcsin(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Arccos: public FizFormOperator
	{	public: Arccos(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Arctan: public FizFormOperator
	{	public: Arctan(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Sinh: public FizFormOperator
	{	public: Sinh(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Cosh: public FizFormOperator
	{	public: Cosh(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Tanh: public FizFormOperator
	{	public: Tanh(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Factorial: public FizFormOperator
	{	public: Factorial(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Magnitude: public FizFormOperator
	{	public: Magnitude(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Square: public FizFormOperator
	{	public: Square(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Exponent: public FizFormOperator
	{	public: Exponent(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Exponentiate: public FizFormOperator
	{	public: Exponentiate(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Random: public FizFormOperator
	{	public: Random(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Vectorize: public FizFormOperator
	{	public: Vectorize(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class Logarithm: public FizFormOperator
	{	public: Logarithm(int numOperands);
		const fizdatum eval(fizstack &stack, const FizObject &obj1, const triangle &tri1, const FizObject &obj2, const triangle &tri2);
		static std::string token;
	};

	class If: public FizFormOperator
	{	public: If(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class And: public FizFormOperator
	{	public: And(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class Or: public FizFormOperator
	{	public: Or(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};
	
	class Equal: public FizFormOperator
	{	public: Equal(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class Notequal: public FizFormOperator
	{	public: Notequal(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class Greater: public FizFormOperator
	{	public: Greater(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class Greatereq: public FizFormOperator
	{	public: Greatereq(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class Less: public FizFormOperator
	{	public: Less(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

	class Lesseq: public FizFormOperator
	{	public: Lesseq(int numOperands);
		const fizdatum eval(fizstack& stack, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2);
		static std::string token;
	};

}

#endif
