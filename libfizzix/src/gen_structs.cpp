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
#ifndef GEN_STRUCTS_CPP
#define GEN_STRUCTS_CPP

#include "gen_structs.h"


vec3::vec3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

const double vec3::operator[](int index) const
{
	if (index == 0) return x;
	if (index == 1) return y;
	if (index == 2) return z;
}

double & vec3::operator[](int index)
{
	if (index == 0) return x;
	if (index == 1) return y;
	if (index == 2) return z;
}

vec4::vec4(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w) {}

const double vec4::operator[](int index) const
{
	if (index == 0) return w;
	if (index == 1) return x;
	if (index == 2) return y;
	if (index == 3) return z;
}

double & vec4::operator[](int index)
{
	if (index == 0) return w;
	if (index == 1) return x;
	if (index == 2) return y;
	if (index == 3) return z;
}



#endif

