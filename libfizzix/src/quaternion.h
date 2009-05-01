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

#ifndef QUATERNION_H
#define QUATERNION_H

#include <vector>
#include "gen_structs.h"

/* This class defines a quaternion, with methods for multiplication, addition, and normalization. */
class Quaternion
{
	private:
		vec4 values;
	public:
		/* Default constructor
		   Creates a unit quaternion with value (1,0,0,0). */
		Quaternion();
		/* Copy constructor */
		Quaternion(const Quaternion & toCopy);
		/* Constructor with a vector of length 4. */
		Quaternion(const std::vector<double> & vec);
		/*Creates a quaternion with vector vec. */
		Quaternion(const vec4 & vec);
		/* Creates a quaternion with value (w,x,y,z) */
		Quaternion(double w,double x,double y,double z);
		/* Get a reference to this quaternion's vector */
		const vec4 & getVec() const;
		/* Manipulate this quaternion's vector */
		vec4 & getVec();
		/* Set this quaternion's vector */
		void setVec(vec4 vec);
		/* Normalize this quaternion
		   Automatically checks that it is unit within tolerance,
			 and will not change if it is close enough */
		void normalize(double tolerance);
		/* Return the element of this quaternion to set it.  0 = w, 1 = x, 2 = y, 3 = z */
		double & operator[](const int index);
		/* Return the conjugate of this quaternion (w,-x,-y,-z) */
		Quaternion conjugate();
		/* Return the transformed vector based on the transformation q means */
		vec3 transformVec(const vec3 & vec);
		/* Return the element of this quaternion at index.  0 = w, 1 = x, 2 = y, 3 = z */
		const double operator[](const int index) const;
		/* Return the sum of this and another quaternion */
		Quaternion operator+(const Quaternion & other) const;
		/* Add another quaternion to this one */
		void operator+=(const Quaternion & other);
		/* Return the difference of this and another quaternion */
		Quaternion operator-(const Quaternion & other) const;
		/* Subtract another quaternion from this one */
		void operator-=(const Quaternion & other);
		/* Return the product of this and another quaternion
		   wnew = w1*w2 - x1*x2 - y1*y2 - z1*z2
		   xnew = w1*x2 + x1*w2 + y1*z2 - z1*y2
		   ynew = w1*y2 - x1*z2 + y1*w2 + z1*x2
		   znew = w1*z2 + x1*y2 - y1*x2 + z1*w2 */
		Quaternion operator*(const Quaternion & other) const;
		/* Multiply another quaternion on this one on the left
		   qnew = other * q */
		void operator*=(const Quaternion & other);
		/* Scalar multiplication*/
		Quaternion operator*(double scalar);
		/* qnew = other * q*/
		void operator*=(double scalar);
};

#endif
