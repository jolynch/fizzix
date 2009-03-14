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

#ifndef QUATERNION_CPP
#define QUATERNION_CPP

#include "quaternion.h"
#include <math.h>

using namespace std;

Quaternion::Quaternion()
{
	values.w = 1.0;
	values.x = 0.0;
	values.y = 0.0;
	values.z = 0.0;
}

Quaternion::Quaternion(const vector<double> & rot)
{
	values.w = rot[0];
	values.x = rot[1];
	values.y = rot[2];
	values.z = rot[3];
}

Quaternion::Quaternion(const Quaternion & toCopy)
{
	values.w = 1.0;
	values.x = 0.0;
	values.y = 0.0;
	values.z = 0.0;
}

Quaternion::Quaternion(const vec4 & vec)
{
	values.w = vec.w;
	values.x = vec.x;
	values.y = vec.y;
	values.z = vec.z;
}

Quaternion::Quaternion(const double w, const double x, const double y, const double z)
{
	values.w = w;
	values.x = x;
	values.y = y;
	values.z = z;
}

const vec4 & Quaternion::getVec() const
{
	return values;
}

vec4 & Quaternion::getVec()
{
	return values;
}

void Quaternion::setVec(vec4 v)
{
	values = v;
}

void Quaternion::normalize(double tolerance)
{
	double magsquared = values.w*values.w + values.x*values.x + values.y*values.y + values.z*values.z;
	if (magsquared > tolerance*tolerance)
	{
		double mag = sqrt(magsquared);
		values.w /= mag;
		values.x /= mag;
		values.y /= mag;
		values.z /= mag;
	}
}

const double Quaternion::operator[](const int index) const
{
	if (index == 0) return values.w;
	if (index == 1) return values.x;
	if (index == 2) return values.y;
	if (index == 3) return values.z;
}

double & Quaternion::operator[](const int index)
{
	if (index == 0) return values.w;
	if (index == 1) return values.x;
	if (index == 2) return values.y;
	if (index == 3) return values.z;
}

Quaternion Quaternion::operator+(const Quaternion & other) const
{
	return Quaternion(values.w+other[0],values.x+other[1],values.y+other[2],values.z+other[3]);
}

void Quaternion::operator+=(const Quaternion & other)
{
	values.w+=other[0];
	values.x+=other[1];
	values.y+=other[2];
	values.z+=other[3];
}

Quaternion Quaternion::operator-(const Quaternion & other) const
{
	return Quaternion(values.w-other[0],values.x-other[1],values.y-other[2],values.z-other[3]);
}

void Quaternion::operator-=(const Quaternion & other)
{
	values.w-=other[0];
	values.x-=other[1];
	values.y-=other[2];
	values.z-=other[3];
}

Quaternion Quaternion::operator*(const Quaternion & other) const
{
	vec4 vec;
	vec.w = values.w * other[0] - values.x * other[1] - values.y * other[2] - values.z * other[3];
	vec.x = values.w * other[1] + values.x * other[0] + values.y * other[3] - values.z * other[2];
	vec.y = values.w * other[2] + values.x * other[3] + values.y * other[0] - values.z * other[1];
	vec.z = values.w * other[3] + values.x * other[2] + values.y * other[1] - values.z * other[0];
	return Quaternion(vec);
}

void Quaternion::operator*=(const Quaternion & other)
{
	vec4 vec;
	vec.w = values.w * other[0] - values.x * other[1] - values.y * other[2] - values.z * other[3];
	vec.x = values.w * other[1] + values.x * other[0] + values.y * other[3] - values.z * other[2];
	vec.y = values.w * other[2] + values.x * other[3] + values.y * other[0] - values.z * other[1];
	vec.z = values.w * other[3] + values.x * other[2] + values.y * other[1] - values.z * other[0];
	values = vec;
}

#endif
