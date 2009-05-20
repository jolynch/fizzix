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

// This file contains general structures and definitions that are used everywhere in libfizzix.

/* Forward declarations (all are implemented or used below)
 */
struct vec3;
struct triangle;
class FizFormNode;

/* Some enums, typedefs and global constant like things
 */

//Types of fizdatum available
enum Type {NIL, SCALAR, VECTOR, INPROGRESS};
//enum Type2 {PROPERTY1, PROPERTY2, PROPERTYJOINT, FORCE, NAMEDCONST};

typedef FizStack<FizFormNode*> fizstack;
typedef vec3 point;

static double div_consts[] = {1.0/6.0, 1.0/24.0, 1.0/60.0, 1.0/120.0};

//A 3 variable vector (x,y,z) that can represent a vector or a point. Includes vector and vector-scalar operations
struct vec3
{
	double x;
 	double y;
	double z;
	
	//individual coordinate access
	const double operator[](int index) const;
	double& operator[](int index);
	
	vec3 operator*(const vec3 & other) const ;
	vec3 operator*(const double & other) const ;
	vec3 operator/(const vec3 & other) const ;
	vec3 operator/(const double & other) const ;
	vec3 operator+(const vec3 & other) const ;
	vec3 operator-(const vec3 & other) const;
	vec3 operator*=(const vec3 & other);
	vec3 operator*=(const double & other);
	vec3 operator/=(const vec3 & other);
	vec3 operator/=(const double & other);
	vec3 operator+=(const vec3 & other);
	vec3 operator-=(const vec3 & other);

	//creates a vector from 3 doubles
	vec3(double _x, double _y, double _z);
	//creates a vector <0,0,0>
	vec3();

	//returns the dot product of two vec3s
	double dot(const vec3& other) const;
	//returns the cross product of two vec3s
	vec3 cross(const vec3& other) const;
	double mag();
};

//A 4 variable vector
struct vec4
{
	double x;
	double y;
	double z;
	double w;

	const double operator[](int index) const;
	double& operator[](int index);
	
	vec4(double _x, double _y, double _z, double _w);
	vec4();

	vec4 dot(const vec4& other);
	vec4 cross(const vec4& other);
	double mag();
};

//A vertex is a point on the outside of an object. It includes its location and a list of pointers to all triangles that radiate from it
struct vertex
{
	point p;
	std::vector<triangle*> triangles;

	//access for (x,y,z) of the point's location
	const double operator[](int index) const;
	double& operator[](int index);
	//access for the index-th triangle that the vertex is included in
	const triangle operator()(int index) const;
	triangle& operator()(int index); 
	
	//adds a triangle to the list of triangles the point is a part of
	void add_triangle(triangle* t);
	void clear_triangles();
	vertex(double _x, double _y, double _z);
	//creates a vertex at <0,0,0> that includes no triangles
	vertex();
};

//TODO: NEEDS DESTRUCTOR
//A triangle on the surface of the object used for drawing objects and evaluating forces
struct triangle 
{
	//the 3 points of the triangle
	vertex * vertices[3];
	//outer normal to the plane of the triangle, pointing outward from the surface of the object
	vec3 normal;
	//normal of magnitude 1
	vec3 unit_normal;
	//a proportionality constant that represents how much of the mass of the whole object is included in the triangle, for integration/summing up of forces
	double massp;

	//accessors for the 3 vertices of the triangle
	const vertex operator[](int index) const;
	vertex& operator[](int index);
	
	//creates a triangle from three vertices, and adds the triangle to each of the vertices' lists of triangles if add is true
	triangle(vertex * v1, vertex * v2, vertex * v3, bool add = true);
	//creates a triangle with three vertices of (0,0,0)
	triangle();
};

//A struct that allows for doing both vector and scalar math in FizFormulas
struct fizdatum
{
	double scalar;
	vec3 vector;
	//whether the fizdatum represents a vector or scalar, whether it's NIL, or whether the datum is being calculated (to prevent circular referencing and infinite loops)
	Type type;

	//creates a fizdatum with the given values
	fizdatum(double s, vec3 v, Type t);
	//creates a fizdatum of type scalar, value s
	fizdatum(double s);
	//creates a fizdatum of type vector, value v
	fizdatum(vec3 v);
	//creates a fizdatum of type scalar, value 0
	fizdatum();
};

//Represents a point and edge of contact between two objects
struct collision
{
	point collision_point;
	vec3 vector;

	collision(point pt,vec3 vec);
	//default collision of (0,0,0), <0,0,0>
	collision();
};

#endif

