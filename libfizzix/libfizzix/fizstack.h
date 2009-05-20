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
#include <iostream>

/** @class FizStack fizstack.h "libfizzix/src/fizstack.h"
 *  @brief A FizStack is a stack that can be reset
 *
 *  A FizStack is a stack that can be pushed and popped, but will reset itself
 *  to the state with the most elements whenever something is pushed or reset
 *  is called. It is useful if you want to do non-destructive pops, such as in
 *  FizFormulae.
 */
template <class T>
class FizStack
{
	private:
		std::vector<T> stack;
		int index;
	public:
		// Same as std::stack, except for reset, and pop returns the popped element.
		FizStack();
		FizStack(std::vector<T> s);	
		void reset(); // Puts back all popped items
		bool empty();
		int size();	
		const T operator[](int index) const;
		T& operator[](int index);
		T pop();
		void push(T f);
};

/* Class definitions
 * Must be present in .h file as it is a template class
 * */
template< typename T >
const T FizStack<T>::operator[](int index) const
{
	return stack[index];
}

template< typename T >
T& FizStack<T>::operator[](int index)
{
	return stack[index];
}



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

template <typename T>
int FizStack<T>::size()
{
	return index+1;
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

