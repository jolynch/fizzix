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

/** @class FizForce fizforce.h "libfizzix/src/fizforce.h"
 *  @brief This class contains a formula that can be evaluated as a force between two objects.
 *  
 *  FizForce contains a formula as well as additional properties to optimize
 *  computation time. It can compute itself given two objects and their desired
 *  triangles. If the objects are approximated as their COM, the given
 *  triangles should be the virtual COM ones.
 */
class FizForce
{
	private:
		bool distributed; // If any of the properties the force uses are distributed
		bool symmetric; // If Newton's 3rd law applies
		FizFormula formula; // The formula
	public:
		FizForce(FizFormula form); // Makes a new FizForce with given formula
		vec3 getForce(const FizObject& obj1,const triangle& tri1,const FizObject& obj2,const triangle& tri2); // Evaluates the force from obj1's triangle tri1 to obj2's triangle tri2.

		// Getters and setters
		bool isSymmetric();
		bool isDistributed();
		void setSymmetric(bool s);
		FizFormula& getFormula();
};

#endif
