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
//REPLACE ALL INSTANCES OF FOO AND BAR.
//BAR is the superclass if the class has one

#ifndef FIZSTACK_H
#define FIZSTACK_H

#include <vector>
#include <stdexcept>

/* Class declaration
 * */

template <class T>
class FizStack
{
	private:
		std::vector<T> stack;
		int index;
	public:
		FizStack();
		FizStack(std::vector<T> s);	
		void reset();
		bool empty();
		
		T pop();
		void push(T f);
};

/* Class definitions
 * Must be present in .h file as it is a template class
 * */
template< typename T >
FizStack<T>::FizStack(std::vector<T> s)
{
	stack = s;
	reset();
}

template< typename T >
FizStack<T>::FizStack()
{
	reset();
}


template< typename T >
void FizStack<T>::reset()
{
	index = stack.size() - 1;
}

template< typename T >
bool FizStack<T>::empty()
{
	return index < 0;
}

template< typename T >
T FizStack<T>::pop()
{
	if( !empty() ) 
	//	throw std::out_of_range("Can't pop an empty stack");
	//else 
		return stack[index--];
}

template< typename T >
void FizStack<T>::push(T f)
{
	//All those items you popped will magically reappear, be careful
	stack.push_back(f);
	reset();
}

#endif

