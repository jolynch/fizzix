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
#ifndef GEN_STRUCTS_H
#define GEN_STRUCTS_H

#include <vector>
#include <string>
#include <math.h>
#include <stdexcept>
#include "fizstack.h"

/* Forward declarations (all are implemented or used below)
 */
struct vec3;
struct triangle;
class FizFormNode;

/* Some enums, typedefs and global constant like things
 */

enum Type {SCALAR, VECTOR, NIL};
enum Type2 {PROPERTY1, PROPERTY2, PROPERTYJOINT, FORCE, NAMEDCONST};

typedef FizStack<FizFormNode*> fizstack;
typedef vec3 point;

double div_consts[] = {1.0/6.0, 1.0/24.0, 1.0/60.0, 1.0/120.0};


struct vec3
{
	double x;
 	double y;
	double z;
	
	const double operator[](int index) const;
	double& operator[](int index);
	
	vec3 operator*(vec3 other);
	vec3 operator*(double other);
	vec3 operator/(vec3 other);
	vec3 operator/(double other);
	vec3 operator+(vec3 other);
	vec3 operator-(vec3 other);
	vec3 operator*=(vec3 other);
	vec3 operator*=(double other);
	vec3 operator/=(vec3 other);
	vec3 operator/=(double other);
	vec3 operator+=(vec3 other);
	vec3 operator-=(vec3 other);

	vec3(int _x, int _y, int _z);
	vec3();

	vec3 dot(const vec3& other);
	vec3 cross(const vec3& other);
	double mag();
};

struct vec4
{
	double x;
	double y;
	double z;
	double w;

	const double operator[](int index) const;
	double& operator[](int index);
	
	vec4(int _x, int _y, int _z, int _w);
	vec4();

	vec4 dot(const vec4& other);
	vec4 cross(const vec4& other);
	double mag();
};

struct vertex
{
	point p;
	std::vector<triangle*> triangles;

	const double operator[](int index) const;
	double& operator[](int index);
	const triangle * operator()(int index) const;
	triangle * operator()(int index); 
	
	void add_triangle(triangle* t);
	vertex(int _x, int _y, int _z);
	vertex();
};

struct triangle 
{
	vertex vertices[3];
	vec3 normal;
	vec3 unit_normal;
	double massp;

	const vertex operator[](int index) const;
	vertex& operator[](int index);
	
	triangle(vertex v1, vertex v2, vertex v3);
};

struct fizdatum
{
	double scalar;
	vec3 vector;
	Type type;

	fizdatum(double s, vec3 v, Type t);
	fizdatum(double s);
	fizdatum(vec3 v);
	fizdatum();

};

#endif

