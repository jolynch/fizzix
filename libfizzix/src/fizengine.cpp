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

#ifndef FIZENGINE_CPP
#define FIZENGINE_CPP

#include "fizengine.h"

/* Constructor for FizEngine
 */
FizEngine::FizEngine() 
{
	thisStep = NULL;
	nextStep = NULL;
	forces = NULL;
}

/* Step thorugh objects
 */
void FizEngine::evalForces()
{
	if(thisStep == NULL) 
		throw std::logic_error("Nothing to work on??");
	
	std::vector<FizObject*>::iterator outer_iter = thisStep.begin();
	std::vector<FizObject*>::iterator inner_iter;
	while(outer_iter != thisStep.end();)
	{
		inner_iter = thisStep.begin();
		while(inner_iter != thisStep.end())
		{
			if(inner_iter == outer_iter) continue;
			for(int i=0; i<forces.size(); i++)
				evalForce(forces[i], *iouter_iter, *inner_iter);
			inner_iter++;
		}

		//DO NOT CHANGE BELOW THIS POINT
		outer_iter++
		fcache.clear();
		pcache.clear();
		//DONE
	}
}

/* Eval a single Runge Kutta step
 *
 * NOTE: THIS ASSUMES CONSTANT ACCEL
 * OVER THE INTERVAL dt, this 
 * may be bad
 *
 * state[0] = position = x
 * state[1] = velocity = v
 * state[2] = acceleration = a
 * 
 * derivatives[0] = velocity = dx/dt
 * derivatives[1] = acceleration; = dv/dt
 *
 *result[0] = new velocity
 *result[1] = new acceleration
 */
void eval(vec3 state[], vec3 derivatives[], double dt, vec3 results[])
{
	vec3 newstate[2];
	newstate[0] = state[0] + (derivatives[0] * dt);
	newstate[1] = state[1] + (derivatives[1] * dt);
	
	result[0] = newstate[1]; 
	result[1] = state[2];
}

void FizEngine::evalForce(FizForce * force, FizObject * o1, FizObject * o2)
{
	//I am giving you a reference by dereferencing a pointer
	//THIS IS DANGEROUS!!
	//
	//Gives me the total force and torque exerted on o1 by o2
	//and visa-versa
	FizObject *ro[2] = {o1, o2};
	//result[0] = Force, result[1] = Torque
	vec3 result[4] = force->eval(*(ro[0]),*(ro[1]));
	
	/* Runga Kutta == MAGIC
	 * t = time
	 * dt = delta t
	 * xi = initial position
	 * xf = final position
	 *
	 * k1 = f'(t,xi)
	 * k2 = f'(t + dt/2, xi + k1/2)
	 * k3 = f'(t + dt/2, xi + k2/2)
	 * k4 = f'(t + dt, xi + k3)
	 *
	 * xf = xi + (k1 + 2k2 + 2k3 + k4) / 6
	 *
	 * Note that I cheat a little because
	 * I say accel is constant
	 */
	
	int x = 0; int v = 1;
	vec3 d[2];
	vec3 k1[2];
	vec3 k2[2];
	vec3 k3[2];
	vec3 k4[2];
	//initial time dependent properties
	vec3 tdi[2][3];
	//final time dependent properties
	vec3 tdf[2][3];

	//When we figure out how to work in quaternions,
	//td[1][2] = result[i * 2 + 1] / ro[i].getInertiaTensor();
	//TODO: Implement rotational
	for( int i = 0; i< 2 ;i++)
	{
		//Initialize the arrays
		td[0][0] = ro[i].getPos();
		td[0][1] = ro[i].getVel();
		td[0][2] = result[i * 2] / ro[i].getMass();
		for(int j = 0; j < 1; j++) // change to 2 for rot
		{
			vec3 deriv[] = { td[j][1], td[j][2] };
			eval(td[j], deriv, 0, k1);
			eval(td[j], k1, dt * .5, k2);
			eval(td[j], k2, dt * .5, k3);
			eval(td[j], k3, dt, k4);
			tdf[j][0] = tdi[j][0] + ((k1[0] + k2[0] * 2 + k3[0] * 2 + k4[0]) / 6);	
			tdf[j][1] = tdi[j][1] + ((k1[1] + k2[1] * 2 + k3[1] * 2 + k4[1]) / 6);
		}
	}
	

		
}

#endif




