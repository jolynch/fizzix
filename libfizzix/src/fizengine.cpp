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
	
	std::vector<FizObject*>::iterator outer_iter = thisStep->begin();
	std::vector<FizObject*>::iterator inner_iter;
	while(outer_iter != thisStep->end())
	{
		//inner_iter = thisStep->begin();
		inner_iter = outer_iter;
		inner_iter++;
		while(inner_iter != thisStep->end())
		{
			if(inner_iter == outer_iter) continue;
			FizObject obj1 = *outer_iter;
			FizObject obj2 = *inner_iter;
			std::vector<triangle>& tris1 = obj1.rgetVertices();
			std::vector<triangle>& tris2 = obj2.rgetVertices();
			vec3 dforce;
			
			//for(int i=0; i<forces.size(); i++)
			for (std::vector<FizForce*>::iterator i = forces.begin(); i != forces.end(); i++)
			{
				//evalForce(forces[i], *outer_iter, *inner_iter);
				FizForce* force = i->second;
				std::string forcename = i->first;
				
				if(!forceEvaled[forcename])
				{	
					//need a COM triangle in each object
					if (obj1.comApprox()) //if object 1 can be approximated as at its COM
					{
						if (obj2.comApprox())
						{
							for (std::vector<FizForce*>::iterator i = forces.begin(); i != forces.end(); i++)
							{
								FizForce* force = i->second;
								std::string forcename = i->first;
								
								dforce = force->getForce(obj1, obj1.rgetCOMTriangle(), obj2, obj2.rgetCOMTriangle());
								evaluatedForces[&obj1][0] += dforce;
								if (force->isSymmetric()) evaluatedForces[&obj2][0] -= dforce; //opposite direction
								else
								{
									clearNonsymmetricCaches();
									dforce = force->getForce(obj2, obj2.rgetCOMTriangle(), obj1, obj1.rgetCOMTriangle());
									evaluatedForces[&obj2][0] += dforce;
								}
								//no torque for obj1 nor obj2
							}
						}
						else
						{
							for (int j = 0; j < tris2.size(); j++)
							{
								for (std::vector<FizForce*>::iterator i = forces.begin(); i != forces.end(); i++)
								{
									FizForce* force = i->second;
									std::string forcename = i->first;
								
									if (!force->distributed) clearDistributedCaches();
									dforce = force->getForce(obj1, obj1.rgetCOMTriangle(), obj2, tris2[j]);
									evaluatedForces[&obj1][0] += dforce;
									//no torque for obj1
									if (force->isSymmetric()) evaluatedForces[&obj2][0] -= dforce;
									else
									{
										clearNonsymmetricCaches();
										dforce = force->getForce(obj2, tris2[j], obj1, obj1.rgetCOMTriangle());
										evaluatedForces[&obj2][0] += dforce;
									}
									vec3 radius = (tris2[j].vertices[0].p + tris2[j].vertices[1].p + tris2[j].vertices[2].p)/3; //vector from center of object to center of triangle
									evaluatedForces[&obj2][1] += dforce.cross(radius); //T = F x r
								}
							}
						}
					}
					else
					{
						for (int i = 0; i < tris1.size(); i++)
						{
							if (obj2.comApprox())
							{
								for (std::vector<FizForce*>::iterator i = forces.begin(); i != forces.end(); i++)
								{
									FizForce* force = i->second;
									std::string forcename = i->first;
									if (!force->distributed) clearDistributedCaches();
									dforce = force->getForce(obj1, tris1[i], obj2, obj2.rgetCOMTriangle());
									evaluatedForces[&obj1][0] += dforce;
									vec3 radius = (tris1[i].vertices[0].p + tris1[i].vertices[1].p + tris1[i].vertices[2].p)/3;
									evaluatedForces[&obj1][1] += dforce.cross(radius);
									if (force->isSymmetric()) evaluatedForces[&obj2][0] -= dforce;
									else
									{
										clearNonsymmetricCaches();
										dforce = force->getForce(obj2, obj2.rgetCOMTriangle(), obj1, tris1[i]);
										evaluatedForces[&obj2][0] += dforce;
									}
									//no torque for obj2
								}
							}
							else
							{
								for (int j = 0; j < tris2.size(); j++)
								{
									for (std::vector<FizForce*>::iterator i = forces.begin(); i != forces.end(); i++)
									{
										FizForce* force = i->second;
										std::string forcename = i->first;
										if (!force->distributed) clearDistributedCaches();
										dforce = force->getForce(obj1, tris1[i], obj2, tris2[j]);
										evaluatedForces[&obj1][0] += dforce;
										vec3 radius = (tris1[i].vertices[0].p + tris1[i].vertices[1].p + tris1[i].vertices[2].p)/3;
										evaluatedForces[&obj1][1] += dforce.cross(radius);
										if (force->isSymmetric()) evaluatedForces[&obj2][0] -= force;
										else
										{
											clearNonsymmetricCaches();
											dforce = force->getForce(obj2, tris2[j], obj1, tris1[i]);
											evaluatedForces[&obj2][0] += dforce;
										}
										radius = (tris2[j].vertices[0].p + tris2[j].vertices[1].p + tris2[j].vertices[2].p)/3;
										evaluatedForces[&obj2][1] += dforce.cross(radius);
									}
								}
							}
						}
					}
				}
			}
			
			inner_iter++;
			fcache.clear();
			pcache.clear();
		}

		//DO NOT CHANGE BELOW THIS POINT
		outer_iter++;
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
	//TODO: result(4) = evaluatedForces[o1](2), evaluatedForces[o2](2)
	
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

/** Applys the force and torque on ob1 using a Runge-Kutta foruth order solver
 * 
 *  Some math notes:
 *  accel = Force / mass = dpdt = m * dvdt
 *  alpha = I_inverse * Torque (where Torque is a 3x1 representation of a vector)
 *  I_inverse is a 3x3 symmetric matrix stored as a double[6] of the form:
 *  [0 3 5]
 *  [3 1 4] where the number indicates the array index
 *  [5 4 2]
 *
 *  Linear Motion:
 *  position = integral(velocity), velocity = integral(acceleration)   
 *
 *  Rotational Motion:
 *  quaternion = 1/2 * omega * current_quaternion
 *  where omega can be seen as a quaternion (w,x,y,z) of the form (0,wx,wy,wz)
 *  omega = integral(alpha)
 
 *  @param force The force to apply
 *  @param torque The torque to apply
 *  @param ob1 The object to modify
 *  @param dt The time period over which this force/torque is applied
 */
void applyForceAndTorque(vec3 force, vec3 torque, FizObject * ob1, double dt)
{
	vec3 new_pos, new_vel, new_w;
	quaternion new_quat;
	vec3 dvdt = force / ob1->getMass();
	//Inertia tensor invese in the order xx,yy,zz,xy,yz,xz (symmetric)
	vector<double> i = ob1->getInertiaTensorInv();
	vec3& t = torque; // just for convenience
	vec3 dwdt = vec3(i[0] * t[0] + i[3] * t[1] + i[5] * t[2],
		       	 i[3] * t[0] + i[1] * t[1] + i[4] * t[2], 
			 i[5] * t[0] + i[4] + t[1] + i[2] + t[2]);
	//Step 1
	vector dxdt1 = ob1->getVel();
	vec3 omega = ob1->getOme();
	Quaternion dqdt1 = (Quaternion(0.0, omega[0],omega[1], omega[2]) * ob1->getQuaternion()) * 0.5;
	
  
	
}	


// Get from cache or evaluate:	
fizdatum FizEngine::getForceVal(const std::string& force, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2)
{	
	if(isCached(fcache,force))
	{		
		fizdatum& cachedVal=fcache[force];
		if(cachedVal.type==INPROGRESS)
		{
			throw logic_error("No circular references, please");
		}
		return cachedVal;
	}
	fizdatum& cachedVal=fcache[force];
	cachedVal.type=INPROGRESS;
	forceEvaled[force] = true;
	return cachedVal=forces[force]->getForce(obj1, tri1, obj2, tri2);
}

fizdatum FizEngine::getPropVal(const std::string& prop, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2)
{	
	if(isCached(pcache.prop))
	{		
		fizdatum& cachedVal=pcache[prop];
		if(cachedVal.type==INPROGRESS)
		{
			throw logic_error("No circular references, please");
		}
		return cachedVal;
	}
	fizdatum& cachedVal=pcache[prop];
	cachedVal.type=INPROGRESS;
	return cachedVal=props[prop]->eval(obj1, tri1, obj2, tri2);
}

bool FizEngine::isCached(const std::map<std::string, fizdatum>& cache, const std::string& key);
{
	return cache.count(key) != 0; 
}

void FizEngine::clearDistributedCaches()
{
	for(std::set<std::string>::const_iterator it = propdist.begin(); it != propdist.end(); ++it)
	{
		pcache.remove(it->first);
	}
	for(std::set<std::string>::const_iterator it = forcedist.begin(); it != forcedist.end(); ++it)
	{
		fcache.remove(it->first);
	}
}

void FizEngine::clearNonsymmetricProperties()
{
	for(std::set<std::string>::cons_iterator it = propsymmetric.begin(); it != propsymmetric.end(); ++it)
	{
		pcache.remove(it->first);
	}

	for(std::set<std::string>::cons_iterator it = forcesymmetric.begin(); it != forcesymmetric.end(); ++it)
	{
		fcache.remove(it->first);
	}
}
#endif

