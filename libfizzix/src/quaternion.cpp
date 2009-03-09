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

Quaternion::Quaternion()
{
    values = new vector<double>(4,0.0);
    values->at(0) = 1.0;
}

Quaternion::Quaternion(vector<double> * rot)
{
    values = rot;
}

Quaternion::Quaternion(Quaternion * toCopy)
{
    values = new vector<double>(*toCopy->getVec());
}

Quaternion::Quaternion(double w,double x,double y,double z)
{
    values = new vector<double>(4,0.0);
    values->at(0) = w;
    values->at(1) = x;
    values->at(2) = y;
    values->at(3) = z;
}

Quaternion::~Quaternion()
{
    delete values;
}

vector<double> * Quaternion::getVec()
{
    return values;
}

void Quaternion::setVec(vector<double> * v)
{
    values = v;
}

void Quaternion::normalize(double tolerance)
{
    double magsquared = this->getVec()->at(0)*this->getVec()->at(0)+this->getVec()->at(1)*this->getVec()->at(1)+this->getVec()->at(2)*this->getVec()->at(2)+this->getVec()->at(3)*this->getVec()->at(3);
    if (magsquared > tolerance*tolerance)
    {
        double mag = sqrt(magsquared);
        this->getVec()->at(0) /= mag;
        this->getVec()->at(1) /= mag;
        this->getVec()->at(2) /= mag;
        this->getVec()->at(3) /= mag;
    }
}

Quaternion Quaternion::operator+(Quaternion * other)
{
    return new Quaternion(this->getVec()->at(0)+other->getVec()->at(0),this->getVec()->at(1)+other->getVec()->at(1),this->getVec()->at(2)+other->getVec()->at(2),this->getVec()->at(3)+other->getVec()->at(3));
}

void Quaternion::operator+=(Quaternion * other)
{
    this->getVec()->at(0)+=other->getVec()->at(0);
    this->getVec()->at(1)+=other->getVec()->at(1);
    this->getVec()->at(2)+=other->getVec()->at(2);
    this->getVec()->at(3)+=other->getVec()->at(3);
}

Quaternion Quaternion::operator-(Quaternion * other)
{
    return new Quaternion(this->getVec()->at(0)-other->getVec()->at(0),this->getVec()->at(1)-other->getVec()->at(1),this->getVec()->at(2)-other->getVec()->at(2),this->getVec()->at(3)-other->getVec()->at(3));
}

void Quaternion::operator-=(Quaternion * other)
{
    this->getVec()->at(0)-=other->getVec()->at(0);
    this->getVec()->at(1)-=other->getVec()->at(1);
    this->getVec()->at(2)-=other->getVec()->at(2);
    this->getVec()->at(3)-=other->getVec()->at(3);
}

Quaternion Quaternion::operator*(Quaternion * other)
{
    Quaternion * product = new Quaternion();
    product->getVec()->at(0) = this->getVec()->at(0)*other->getVec()->at(0) - this->getVec()->at(1)*other->getVec()->at(1) - this->getVec()->at(2)*other->getVec()->at(2) - this->getVec()->at(3)*other->getVec()->at(3);
    product->getVec()->at(1) = this->getVec()->at(0)*other->getVec()->at(1) + this->getVec()->at(1)*other->getVec()->at(0) + this->getVec()->at(2)*other->getVec()->at(3) - this->getVec()->at(3)*other->getVec()->at(2);
    product->getVec()->at(2) = this->getVec()->at(0)*other->getVec()->at(2) - this->getVec()->at(1)*other->getVec()->at(3) + this->getVec()->at(2)*other->getVec()->at(0) + this->getVec()->at(3)*other->getVec()->at(1);
    product->getVec()->at(3) = this->getVec()->at(0)*other->getVec()->at(3) + this->getVec()->at(1)*other->getVec()->at(2) - this->getVec()->at(2)*other->getVec()->at(1) + this->getVec()->at(3)*other->getVec()->at(0);
    return *product;
}

void Quaternion::operator*=(Quaternion * other)
{
    this->getVec()->at(0) = this->getVec()->at(0)*other->getVec()->at(0) - this->getVec()->at(1)*other->getVec()->at(1) - this->getVec()->at(2)*other->getVec()->at(2) - this->getVec()->at(3)*other->getVec()->at(3);
    this->getVec()->at(1) = this->getVec()->at(1)*other->getVec()->at(0) + this->getVec()->at(0)*other->getVec()->at(1) + this->getVec()->at(3)*other->getVec()->at(2) - this->getVec()->at(2)*other->getVec()->at(3);
    this->getVec()->at(2) = this->getVec()->at(2)*other->getVec()->at(0) - this->getVec()->at(3)*other->getVec()->at(1) + this->getVec()->at(0)*other->getVec()->at(2) + this->getVec()->at(1)*other->getVec()->at(3);
    this->getVec()->at(3) = this->getVec()->at(3)*other->getVec()->at(0) + this->getVec()->at(2)*other->getVec()->at(1) - this->getVec()->at(1)*other->getVec()->at(2) + this->getVec()->at(0)*other->getVec()->at(3);
}

#endif
