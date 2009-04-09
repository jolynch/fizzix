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

#ifndef FIZFORCE_H
#define FIZFORCE_H

#include <vector>
#include "fizformula.h"
#include "gen_structs.h"

class FizFormula;

class FizForce
{
	private:
		bool symmetric;
		FizFormula formula;
	public:
		//default constructor - F = 0
		FizForce();
		//constructor that takes a string
		FizForce(string form)
		//constructor that takes a formula
		FizForce(FizFormula form)
		//default destructor
		~FizForce();
		//applies and evaluates force and torque between two different objects
		vec3[2] eval(FizObject& obj1, FizObject& obj2);
};

#endif
