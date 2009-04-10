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

#include "../include/libfizzix/gen_structs.h"
#include <stdexcept>

/******************** VEC3 ********************/
vec3::vec3(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

vec3::vec3() : x(0.0), y(0.0), z(0.0) {}
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

vec3 vec3::operator*(vec3 other)
{
	return vec3(x * other[0], y * other[1], z * other[2]);
}

vec3 vec3::operator*(double other)
{
	return vec3(x * other, y * other, z * other);
}

vec3 vec3::operator/(vec3 other)
{
	return vec3(x / other[0], y / other[1], z / other[2]);
}

vec3 vec3::operator/(double other)
{
	return vec3(x / other, y / other, z / other);
}

vec3 vec3::operator+(vec3 other)
{
	return vec3(x + other[0], y + other[1], z + other[2]);
}

vec3 vec3::operator-(vec3 other)
{
	return vec3(x - other[0], y - other[1], z - other[2]);
}

vec3 vec3::operator*=(vec3 other)
{
	x *= other[0];
	y *= other[1];
	z *= other[2]);
	return this;
}

vec3 vec3::operator*=(double other)
{
	x *= other;
	y *= other;
	z *= other;
	return this;
}

vec3 vec3::operator/=(vec3 other)
{
	x /= other[0];
	y /= other[1];
	z /= other[2];
	return this;
}

vec3 vec3::operator/=(double other)
{
	x /= other;
	y /= other;
	z /= other;
	return this;
}

vec3 vec3::operator+=(vec3 other)
{
	x += other[0];
	y += other[1];
	z += other[2];
	return this;
}

vec3 vec3::operator-=(vec3 other)
{
	x -= other[0];
	y -= other[1];
	z -= other[2];
	return this;
}

vec3 vec3::dot(const vec3& other) 
{
	return vec3(x * other.x, y * other.y, z * other.z);
}

vec3 vec3::cross(const vec3& other) 
{
	return vec3(y * other.z - z * other.y,
		    z * other.x - x * other.z,
		    x * other.y - y * other.x);
}

double vec3::mag() 
{
	return sqrt(x * x + y * y + z * z);
}

/******************** VEC3 ********************/

/******************** VEC4 ********************/ 
vec4::vec4(int _x, int _y, int _z, int _w) : x(_x), y(_y), z(_z), w(_w) {}
vec4::vec4() : x(0.0), y(0.0), z(0.0), w(0.0) {}

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

vec4 vec4::dot(const vec4& other) 
{
	return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
}

vec4 vec4::cross(const vec4& other) {}
/* Cross products in 4space require 3 vectors to not have infinite results
 * How to deal with this ...
{
	return vec4(y * other.z - z * other.y,
		    z * other.x - x * other.z,
		    x * other.y - y * other.x)
}
*/

double vec4::mag()
{
	return sqrt(x * x + y * y + z * z + w * w);
}
/******************** VEC4 ********************/

/******************* VERTEX *******************/
vertex::vertex(int _x, int _y, int _z) : p(vec3(_x, _y, _z)) {};

vertex::vertex() : p(vec3()) {}

const double vertex::operator[](int index) const
{
	return p[index];
}

double& vertex::operator[](int index)
{
	return p[index];
}

const triangle * vertex::operator()(int index) const
{
	if (triangles.size() > index)
	{
		return triangles[index];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}

triangle * vertex::operator()(int index)
{
	if (triangles.size() > index)
	{
		return triangles[index];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}

void vertex::add_triangle(triangle * t) 
{
	triangles.push_back(t);
}
/******************* VERTEX *******************/

/****************** TRIANGLE ******************/
triangle::triangle(vertex v1, vertex v2, vertex v3)
{
	vertices[0] = v1; vertices[1] =  v2; vertices[2] = v3;
	massp = 0.0;
	vec3 e1 = vec3(v1[0]-v2[0],v1[1]-v2[1],v1[2]-v2[2]);
	vec3 e2 = vec3(v1[0]-v3[0],v1[1]-v3[1],v1[2]-v3[2]);
	normal = e1.cross(e2);
	unit_normal = vec3(normal[0]/normal.mag(), 
			   normal[1]/normal.mag(), 
			   normal[2]/normal.mag());
	v1.add_triangle(this);
	v2.add_triangle(this);
	v3.add_triangle(this);
}

const vertex triangle::operator[](int index) const
{
	if (index < 3)
	{
		return vertices[index];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}

vertex& triangle::operator[](int index)
{
	if (index < 3)
	{
		return vertices[index];
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}
/****************** TRIANGLE ******************/

/****************** FIZDATUM ******************/
fizdatum::fizdatum(double s, vec3 v, Type t) : scalar(s), vector(v), type(t) {}
fizdatum::fizdatum(double s) : scalar(s), type(SCALAR) {}
fizdatum::fizdatum(vec3 v) : vector(v), type(VECTOR) {}
fizdatum::fizdatum() : scalar(0), vector(vec3()), type(NIL) {}
/****************** FIZDATUM ******************/

#endif
