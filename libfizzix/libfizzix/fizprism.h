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
#ifndef FIZPRISM_H
#define FIZPRISM_H

#include "fizobject.h"

// A rectangular prism (box) FizObject. Has a height, width, and depth.
class FizPrism:public FizObject
{
	private:
		double height;
		double width;
		double depth;
	public:
		FizPrism(); //Default constructor
		FizPrism(std::string newname, double mass = 1, double h = 1, double w = 1, double d = 1); // Constructor that inits the name and dimensions
		FizPrism(std::string newname, vec3 color, double mass = 1, double h = 1, double w = 1, double d = 1);	// Constructor that inits the name, color, and dimensions
		FizPrism(std::string newname, std::vector<triangle*> new_vertices, double mass = 1, double h = 1, double w = 1, double d = 1); // Constructor that inits the name, triangle*s, and dimensions
		FizPrism(std::string newname, vec3 color, std::vector<triangle*> new_vertices, double mass = 1, double h = 1, double w = 1, double d = 1); // Constructor that inits the name, color, triangle*s, and dimensions
		
		// Init functions used by constructors:
		void init(std::string new_name, vec3 color, const std::vector<triangle*>& new_vertices, double new_mass, double h, double w, double d);
		void init_object(std::string new_name, vec3 color, const std::vector<triangle*>& tinit, double new_mass, double h, double w, double d);
		
		// From FizObject
		void compute();
		void computeBounds();
		
		double getHeight() const;
		double& rgetHeight();
		void setHeight(double newheight);
							
		double getWidth() const;
		double& rgetWidth();
		void setWidth(double newwidth);
							
		double getDepth() const;
		double& rgetDepth();
		void setDepth(double newdepth);
		
		void setVertices(std::vector<triangle*> newvertices);
};

#endif
