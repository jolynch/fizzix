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

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

class Matrix 
{
	private:
		const int row,col;
		std::vector< std::vector <double> > val;
	public:
		/* Constructs an nxn identity matrix. */
		Matrix(int n);
		/* Constructs a row x cols zero matrix */
		Matrix(int rows, int cols);
		/* Copy constructor */
		Matrix(const Matrix & other);
		/* Constructs a matrix from mat */
		Matrix(const std::vector< std::vector <double> > mat);
		/* Returns the value at (row, column) of this Matrix */
		double operator()(const int row, const int col) const;
		double & operator()(const int row, const int col);
		/* Returns the sum of this and Matrix other */
		Matrix operator+(const Matrix other) const;
		/* Adds other to this Matrix */
		void operator+=(const Matrix other);
		/* Returns the difference of this and Matrix other */
		Matrix operator-(const Matrix other) const;
		/* Subtracts other from this Matrix */
		void operator-=(const Matrix other);
		/* Returns the product of this and Matrix other */
		Matrix operator*(const Matrix other) const;
		/* Multiples other on the left of this, ie:
		     Matrix A(2),B(2);
		     A = B * A;
		   is equivalent to:
		     Matrix A(2),B(2);
		     A *= B; */
		void operator*=(const Matrix other);
		
};

#endif
