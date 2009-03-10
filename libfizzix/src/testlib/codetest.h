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


#ifndef CODETEST_H
#define CODETEST_H

//@class CodeTest
//CodeTest is an abstract class to inherit for code tests.
//This will be compiled only with make test.
class CodeTest
{
	public:
		//name - provides test name
		//@parameters - none
		//@returns - the name of the test as a const char *, to be displayed with any errors
		virtual const char * name (void) = 0;
		
		//execute - executes the test
		//@parameters - an optional parameter to return out error descriptions.
		//@returns - false if failed
		//			true if success
		virtual bool execute (char * error) = 0;
};

#endif