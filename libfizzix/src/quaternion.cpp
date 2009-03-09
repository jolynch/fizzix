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
    values = vector<double>(4,0.0);
    values[0] = 1.0;
}

Quaternion::Quaternion(vector<double> rot)
{
    values = rot;
}

Quaternion::Quaternion(const Quaternion & toCopy)
{
    values = vector<double>(toCopy.getVec());
}

Quaternion::Quaternion(double w,double x,double y,double z)
{
    values = vector<double>(4,0.0);
    values[0] = w;
    values[1] = x;
    values[2] = y;
    values[3] = z;
}

Quaternion::~Quaternion()
{
    delete &values;
}

vector<double> Quaternion::getVec() const
{
    return values;
}

void Quaternion::setVec(vector<double> v)
{
    values = v;
}

void Quaternion::normalize(double tolerance)
{
    double magsquared = values[0]*values[0] + values[1]*values[1] + values[2]*values[2] + values[3]*values[3];
    if (magsquared > tolerance*tolerance)
    {
        double mag = sqrt(magsquared);
        values[0] /= mag;
        values[1] /= mag;
        values[2] /= mag;
        values[3] /= mag;
    }
}

double Quaternion::operator[](const int index) const
{
    return values[index];
}

Quaternion Quaternion::operator+(const Quaternion & other) const
{
    return Quaternion(values[0]+other[0],values[1]+other[1],values[2]+other[2],values[3]+other[3]);
}

void Quaternion::operator+=(const Quaternion & other)
{
    values[0]+=other[0];
    values[1]+=other[1];
    values[2]+=other[2];
}

Quaternion Quaternion::operator-(const Quaternion & other) const
{
    return Quaternion(values[0]-other[0],values[1]-other[1],values[2]-other[2],values[3]-other[3]);
}

void Quaternion::operator-=(const Quaternion & other)
{
    values[0]-=other[0];
    values[1]-=other[1];
    values[2]-=other[2];
}

Quaternion Quaternion::operator*(const Quaternion & other) const
{
    vector<double> vec;
    vec[0] = values[0] * other[0] - values[1] * other[1] - values[2] * other[2] - values[3] * other[3];
    vec[1] = values[0] * other[1] + values[1] * other[0] + values[2] * other[3] - values[3] * other[2];
    vec[2] = values[0] * other[2] + values[1] * other[3] + values[2] * other[0] - values[3] * other[1];
    vec[3] = values[0] * other[3] + values[1] * other[2] + values[2] * other[1] - values[3] * other[0];
    return Quaternion(vec);
}

void Quaternion::operator*=(const Quaternion & other)
{
    values[0] = values[0] * other[0] - values[1] * other[1] - values[2] * other[2] - values[3] * other[3];
    values[1] = values[1] * other[0] + values[0] * other[1] + values[3] * other[2] - values[2] * other[3];
    values[2] = values[2] * other[0] + values[3] * other[1] + values[0] * other[2] - values[1] * other[3];
    values[3] = values[3] * other[0] + values[2] * other[1] + values[1] * other[2] - values[0] * other[3];
}

#endif
