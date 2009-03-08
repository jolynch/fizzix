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

#include <vector.h>

/* This class defines a quaternion, with methods for multiplication, addition, and normalization. */
class Quaternion
{
    private:
        *vector<double> values; // (w,x,y,z)
    public:
        /* Default constructor
         * Creates a unit quaternion with value (1,0,0,0). */
        Quaternion();
        /* Copy constructor */
        Quaternion(*Quaternion);
        /* Constructor with a vector of length 4. */
        Quaternion(*vector)
	/* Creates a quaternion with value (w,x,y,z) */
        Quaternion(double w,double x,double y,double z);
        /* Default destructor */
        ~Quaternion();
        /* Get a reference to this quaternion's vector */
        vector getVec();
        /* Set this quaternion's vector */
        void setVec(*vector);
        /* Normalize this quaternion
           Automatically checks that it is unit within tolerance,
             and will not change if it is close enough */
        void normalize(double tolerance);
        /* Return the sum of this and another quaternion */
        Quaternion operator+(Quaternion&);
        /* Add another quaternion to this one */
        void operator+=(Quaternion&);
        /* Return the difference of this and another quaternion */
        Quaternion operator-(Quaternion&);
        /* Subtract another quaternion from this one */
        void operator-=(Quaternion&);
        /* Return the product of this and another quaternion
           wnew = w1*w2 - x1*x2 - y1*y2 - z1*z2
           xnew = w1*x2 + x1*w2 + y1*z2 - z1*y2
           ynew = w1*y2 - x1*z2 + y1*w2 + z1*x2
           znew = w1*z2 + x1*y2 - y1*x2 + z1*w2 */
        Quaternion operator*(Quaternion&);
        /* Multiply another quaternion on this one on the left
           qnew = other * q */
        void operator*=(Quaternion&);
};

#endif
