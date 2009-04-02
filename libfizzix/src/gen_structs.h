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

//#include <matrix.h>

struct vec3
{
	double x;
 	double y;
	double z;
	const double operator[](int index) const;
	double& operator[](int index);
	vec3(int x, int y, int z);
};

typedef vec3 point;

struct vec4
{
	double x;
	double y;
	double z;
	double w;
	const double operator[](int index) const;
	double& operator[](int index);
	vec4(int x, int y, int z, int w);
};

struct triangle;

struct vertex
{
	point p;
	std::vector<triangle> triangles;
	const double operator[](int index) const;
	double & operator[](int index);
	const triangle operator()(int index) const;
	triangle operator()(int index) 
};

struct triangle 
{
	//3x3 matrix essentially.  (x,y,z) of each vertice
	std::vector<vertex> vertices;
	//Normal vector to surface <x,y,z>
	vec3 normal;
	//Normal vector to surface <x,y,z>
	vec3 unitNormal;
	//For use in center of mass computations
	double mass;
	const double operator

};

struct line
{
	point p1;
	point p2;
};

enum Type {SCALAR, VECTOR};
enum Type2 {PROPERTY1, PROPERTY2, PROPERTYJOINT, FORCE};

struct fizdatum
{
	double scalar;
	vec3 vector;
	Type type;
};

double div_consts[] = {1.0/6.0, 1.0/24.0, 1.0/60.0, 1.0/120.0};

#endif

