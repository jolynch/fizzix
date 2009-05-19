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
	props = NULL;
	ccache = NULL;	
	evaluatedForces = new std::map<FizObject*, std::pair<vec3,vec3> >();
	forceEvaled = new std::map<std::string, bool>();
}

/* Step and compute
 */
void FizEngine::step(	std::map<std::string, FizObject*>  * thisStep,
		       	std::map<std::string, FizObject*>  * nextStep,
		       	std::map<std::string, FizForce*>   * forces,
		       	std::map<std::string, FizFormula*> * macros,
			std::map<std::string, fizdatum>    * ccache,
		      	double dt)
{
std::cout<< "FizEngine pointer from step "<<this<<std::endl; 
	this->thisStep = thisStep;
	this->nextStep = nextStep;
	this->forces = forces;
	this->props = macros; // Eventually props should be renamed to macros
	this->ccache = ccache;
	this->dt = dt;
	std::cout << "STEPPING BIATCH"<<std::endl;
	mcache.clear();
std::cout << &mcache <<std::endl;
	fcache.clear();
	evaluatedForces->clear();
	forceEvaled->clear();
std::cout << &mcache <<std::endl;
	evalForces();
}

/* Step thorugh objects
 */
void FizEngine::evalForces()
{std::cout << &mcache <<std::endl;
	if(thisStep == NULL || thisStep->size()==0) 
	{
		throw std::logic_error("Nothing to work on??");
		return;
	}

	std::map<std::string, FizObject*>::iterator outer_iter = thisStep->begin();
	std::map<std::string, FizObject*>::iterator inner_iter;
	std::map<std::string,FizForce*>::iterator force_iter;
	while(outer_iter != thisStep->end())
	{
		//inner_iter = thisStep->begin();
		inner_iter = outer_iter;
		inner_iter++;
		while(!(inner_iter == thisStep->end()))
		{
			if(inner_iter == outer_iter)
			{
				inner_iter++;
				std::cout << "CONTINUING BITCH" <<std::endl;
				continue;
			}
			FizObject& obj1 = *(outer_iter->second);
			FizObject& obj2 = *(inner_iter->second);
			//TODO
			//Anton, we don't need this is you keep names up to date ...
			obj1.setName(outer_iter->first);
			obj2.setName(inner_iter->first);
std::cout << "YO I'VE GOT OBJECTS" << '\n';
std::cout << &mcache <<std::endl;
			collisions(obj1, obj2);
			std::vector<triangle*>& tris1 = obj1.rgetVertices(); //actually, triangles, not vertices
			std::vector<triangle*>& tris2 = obj2.rgetVertices();
			vec3 dforce;
			bool fnan;
			bool rnan;
			//evalForce(forces[i], *outer_iter, *inner_iter);
			//need a COM triangle in each object
std::cout << "ABOUT TO EVALUATE SHIT" << '\n';
std::cout << &mcache <<std::endl;
			if (obj1.comApprox()) //if object 1 can be approximated as at its COM
			{
std::cout << "OBJ 1 CAN BE COMAPPROXED" << '\n';
std::cout << &mcache <<std::endl;
				if (obj2.comApprox())
				{
std::cout << "OBJ 2 CAN BE COMAPPROXED" << '\n';
std::cout << &mcache <<std::endl;
					force_iter = forces->begin();
std::cout << "ABOUT TO GO THROUGH FORCES" << '\n';
std::cout << &mcache <<std::endl;
					while(!(force_iter == forces->end()))
					{
std::cout << "IN FORCES YO" << '\n';
std::cout << &mcache <<std::endl;
						FizForce* force = force_iter->second;
						std::string forcename = force_iter->first;
std::cout << "ABOUT TO CHECK FORCEEVALED" << '\n';
std::cout << &mcache <<std::endl;
						if(!(*forceEvaled)[forcename])
						{
std::cout << "EVALING SHIT" << '\n';
std::cout << &mcache <<std::endl;
							triangle tri1 = obj1.getCOMTriangle();
							triangle tri2 = obj2.getCOMTriangle();
std::cout << "GOTTEN TRIANGLES" << '\n';
std::cout << &mcache <<std::endl;
							dforce = force->getForce(obj1, tri1, obj2, tri2);
std::cout << "WOOT GOT A FORCE OF: "<<dforce[0]<<" "<<dforce[1]<<" "<<dforce[2]<<std::endl;
std::cout << "ABOUT TO CHECK EVALUATEDFORCES" << '\n';
							fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
							if (!fnan) (*evaluatedForces)[&obj1].first += dforce;
std::cout << "ABOUT TO CHECK SYMMETRY" << '\n';
							if (force->isSymmetric()) 
							{	
std::cout<< "FORCE IS SYMMETRIC"<<std::endl;
								if (!fnan) (*evaluatedForces)[&obj2].first -= dforce; //opposite direction
							}
							else
							{
std::cout << "ABOUT TO CLEAR CACHE" << '\n';
								clearNonsymmetricCaches();
								dforce = force->getForce(obj2, obj2.rgetCOMTriangle(), obj1, obj1.rgetCOMTriangle());
								fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
								if (!fnan) ((*evaluatedForces)[&obj2]).first += dforce;
							}
std::cout << "DONE WITH EVALUATING FORCES"<<std::endl;
						}
						//no torque for obj1 nor obj2
						force_iter++;
					}
				}
				else
				{
std::cout << "OBJ 2 CANNOT BE COMAPPROXED" << '\n';
					for (int j = 0; j < tris2.size(); j++)
					{
						force_iter = forces->begin();
						while(!(force_iter == forces->end()))
						{
							FizForce* force = force_iter->second;
							std::string forcename = force_iter->first;
							if(!(*forceEvaled)[forcename])
							{
								if (!force->isDistributed()) clearDistributedCaches();
								dforce = force->getForce(obj1, obj1.rgetCOMTriangle(), obj2, *(tris2[j]));
								fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
								if (!fnan) (*evaluatedForces)[&obj1].first += dforce;
								//no torque for obj1
								if (force->isSymmetric())
								{
									if (!fnan) (*evaluatedForces)[&obj2].first -= dforce;
								}
								else
								{
									clearNonsymmetricCaches();
									dforce = force->getForce(obj2, *(tris2[j]), obj1, obj1.rgetCOMTriangle());
									fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
									if (!fnan) (*evaluatedForces)[&obj2].first += dforce;
								}
								vec3 radius = (tris2[j]->vertices[0]->p + tris2[j]->vertices[1]->p + tris2[j]->vertices[2]->p)/3; //vector from center of object to center of triangle
								rnan = isnan(radius[0]) || isnan(radius[1]) || isnan(radius[2]);
								if (!(fnan || rnan)) (*evaluatedForces)[&obj2].second += dforce.cross(radius); //T = F x r
							}
							force_iter++;
						}
					}
				}
			}
			else
			{
std::cout << "OBJ 1 CANNOT BE COMAPPROXED" << '\n';
				for (int i = 0; i < tris1.size(); i++)
				{
					if (obj2.comApprox())
					{
std::cout << "OBJ 2 CAN BE COMAPPROXED" << '\n';
						force_iter = forces->begin();
						while(!(force_iter == forces->end()))
						{
							FizForce* force = force_iter->second;
							std::string forcename = force_iter->first;
							if(!(*forceEvaled)[forcename])
							{
								if (!force->isDistributed()) clearDistributedCaches();
								dforce = force->getForce(obj1, *(tris1[i]), obj2, obj2.rgetCOMTriangle());
								fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
								vec3 radius = (tris1[i]->vertices[0]->p + tris1[i]->vertices[1]->p + tris1[i]->vertices[2]->p)/3;
								rnan = isnan(radius[0]) || isnan(radius[1]) || isnan(radius[2]);
								if (!fnan)
								{
									(*evaluatedForces)[&obj1].first += dforce;
									if (!rnan) (*evaluatedForces)[&obj1].second += dforce.cross(radius);
								}
								if (force->isSymmetric())
								{
									if (!fnan) (*evaluatedForces)[&obj2].first -= dforce;
								}
								else
								{
									clearNonsymmetricCaches();
									dforce = force->getForce(obj2, obj2.rgetCOMTriangle(), obj1, *(tris1[i]));
									fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
									if (!fnan) (*evaluatedForces)[&obj2].first += dforce;
								}
								//no torque for obj2
							}
							force_iter++;
						}
					}
					else
					{
std::cout << "OBJ 2 CANNOT BE COMAPPROXED" << '\n';
						for (int j = 0; j < tris2.size(); j++)
						{
							force_iter = forces->begin();
							while(!(force_iter == forces->end()))
							{
								FizForce* force = force_iter->second;
								std::string forcename = force_iter->first;
								if(!(*forceEvaled)[forcename])
								{
									if (!force->isDistributed()) clearDistributedCaches();
									dforce = force->getForce(obj1, *(tris1[i]), obj2, *(tris2[j]));
									fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
									vec3 radius = (tris1[i]->vertices[0]->p + tris1[i]->vertices[1]->p + tris1[i]->vertices[2]->p)/3;
									rnan = isnan(radius[0]) || isnan(radius[1]) || isnan(radius[2]);
									if (!fnan)
									{
										(*evaluatedForces)[&obj1].first += dforce;
										if (!rnan) (*evaluatedForces)[&obj1].second += dforce.cross(radius);
									}
									if (force->isSymmetric())
									{
										if (!fnan) (*evaluatedForces)[&obj2].first -= dforce;
									}
									else
									{
										clearNonsymmetricCaches();
										dforce = force->getForce(obj2, *(tris2[j]), obj1, *(tris1[i]));
										fnan = isnan(dforce[0]) || isnan(dforce[1]) || isnan(dforce[2]);
										if (!fnan) (*evaluatedForces)[&obj2].first += dforce;
									}
									radius = (tris2[j]->vertices[0]->p + tris2[j]->vertices[1]->p + tris2[j]->vertices[2]->p)/3;
									rnan = isnan(radius[0]) || isnan(radius[1]) || isnan(radius[2]);
									if (!(fnan || rnan)) (*evaluatedForces)[&obj2].second += dforce.cross(radius);
								}
								force_iter++;
							}
						}
					}
				}
			}
			
			
			std::cout << "GOING FOR NEXT OBJECT ... WOOT?"<<std::endl;
			inner_iter++;
			fcache.clear();
			mcache.clear();
			std::cout << "NEXT ITERATION PLEASE" <<std::endl;
		}

		//DO NOT CHANGE BELOW THIS POINT
		outer_iter++;
		//DONE
	}
std::cout << "DONE WITH EVALUATIONS "<<std::endl;
	//std::map<FizObject*, std::pair<vec3,vec3> >::iterator iter = evaluatedForces->begin();
	//for(;iter!= evaluatedForces->end();iter++)
	std::map<std::string, FizObject*>::iterator iter = thisStep->begin();
	while (iter != thisStep->end())
	{
		FizObject* obj = iter->second;
		std::pair<vec3,vec3> forcetorque = (*evaluatedForces)[obj];
		applyForceAndTorque(forcetorque.first, forcetorque.second, obj, dt);
		//this->applyForceAndTorque(iter->second.first,iter->second.second, iter->first, this->dt);
		iter++;
	}
}

/** Helps by calculating L x w + Torque
 */
vec3 torque_helper(vec3 w, std::vector<double> i, vec3 t)
{
	vec3 L( (i[0] * w[0] + i[3] * w[1] + i[5] * w[2]),
		(i[3] * w[0] + i[1] * w[1] + i[4] * w[2]),
		(i[5] * w[0] + i[4] * w[1] + i[2] * w[2]));
	return (L.cross(w) + t);
} 

/** Applys the force and torque on ob1 using a Runge-Kutta foruth order solver
 */

void FizEngine::applyForceAndTorque(vec3 force, vec3 torque, FizObject * ob1, double dt)
{
std::cout << "APPLYING FORCE OF "<<force[0] << ' ' << force[1] << ' ' << force[2] << '\n';
std::cout << "APPLYING TORQUE OF "<<torque[0] << ' ' << torque[1] << ' ' << torque[2] << '\n';
std::cout << "MOVING FROM " << ob1->getPos()[0] << ' ' <<ob1->getPos()[1] << ' ' << ob1->getPos()[2] << '\n';
	FizObject * new_object = new FizObject(*ob1);
	vec3 new_pos, new_vel, new_w;
	Quaternion new_quat;
	
	//F = dp/dt = m * dv/dt = m * a
	vec3 dvdt = force / ob1->getMass();
	//Inertia tensor inverse in the order xx,yy,zz,xy,yz,xz (symmetric)
	//TODO
	//I^-1 = R * I^-1 * R^T, not I^-1
	//NOTE I think I fixed it
	std::vector<double> i = ob1->getInertiaTensorInvWorld();
	vec3 t = torque_helper(ob1->getOme(),ob1->getInertiaTensor(),torque); // just for convenience
	//T = dL/dt = I * dw/dt = I * alpha
	vec3 dwdt = vec3(i[0] * t[0] + i[3] * t[1] + i[5] * t[2],
		       	 i[3] * t[0] + i[1] * t[1] + i[4] * t[2], 
			 i[5] * t[0] + i[4] + t[1] + i[2] + t[2]);
	//Step 1 
	vec3 dxdt1 = ob1->getVel();
	vec3 omega = ob1->getOme();
	Quaternion dqdt1 = (Quaternion(0.0, omega[0],omega[1], omega[2]) * ob1->getQuaternion()) * 0.5;
	new_pos = ob1->getPos() + (dxdt1 * (dt/2.0));
	new_quat = ob1->getQuaternion() + (dqdt1 * (dt/2.0));
	new_vel = ob1->getVel() + (dvdt * (dt/2.0));
	new_w = omega + (dwdt * (dt/2.0));
	
	//Step 2
  	vec3 dxdt2 = new_vel;
	Quaternion dqdt2 = (Quaternion(0.0, new_w[0],new_w[1], new_w[2]) * new_quat) * 0.5;
	new_pos = ob1->getPos() + (dxdt2 * (dt/2.0));
	new_quat = ob1->getQuaternion() + (dqdt2 * (dt/2.0));
	new_vel = ob1->getVel() + (dvdt * (dt/2.0));
	new_w = omega + (dwdt * (dt/2.0));
	
	//Step 3

  	vec3 dxdt3 = new_vel;
	Quaternion dqdt3 = (Quaternion(0.0, new_w[0],new_w[1], new_w[2]) * new_quat) * 0.5;
	new_pos = ob1->getPos() + (dxdt3 * (dt));
	new_quat = ob1->getQuaternion() + (dqdt3 * (dt));
	new_vel = ob1->getVel() + (dvdt * (dt));
	new_w = omega + (dwdt * (dt));
	
	//Step 4
  	vec3 dxdt4 = new_vel;
	Quaternion dqdt4 = (Quaternion(0.0, new_w[0],new_w[1], new_w[2]) * new_quat) * 0.5;
	new_object->setPos(ob1->getPos() + ((dxdt1 + (dxdt2 + dxdt3)*2.0 + dxdt4)*(dt/6.0)));
	new_object->setQuaternion(ob1->getQuaternion() + ((dqdt1 + (dqdt2 + dqdt3)*2.0 + dqdt4)*(dt/6.0)));
	new_object->setVel(ob1->getVel() + ((dvdt + (dvdt + dvdt)*2.0 + dvdt)*(dt/6.0)));
	new_object->setOme(ob1->getOme() + ((dwdt + (dwdt + dwdt)*2.0 + dwdt)*(dt/6.0)));
	(*nextStep)[new_object->getName()] = new_object;	
std::cout <<"TO POSITION" << new_object->getPos()[0] << ' '<< new_object->getPos()[1] << ' ' << new_object->getPos()[2] << '\n';
}	

void FizEngine::collisions(FizObject& obj1, FizObject& obj2)
{
	vec3 radius = obj1.getPos() - obj2.getPos();
	double distance = radius.mag();
	vec3 direction = radius/distance;
	if (distance <= obj1.getMaxRad() + obj2.getMaxRad()) //if within their bounding spheres
	{
		//TODO: check if actually colliding
		//TODO: find where collision is
		triangle tri1 = triangle();
		triangle tri2 = triangle();
		collisionDetect(obj1, obj2, direction, tri1, tri2);
		//TODO: call collide
		collide(obj1, tri1, obj2, tri2, direction, point());
	}
}

//currently assumes a sphere
void FizEngine::collisionDetect(FizObject& obj1, FizObject& obj2, vec3 direction, triangle& tri1, triangle& tri2)
{
	double delta = .1;
	std::vector<triangle*> tris1 = obj1.getVertices();
	std::vector<triangle*> tris2 = obj2.getVertices();
	double mag = 50;
	for (int i = 0; i < tris1.size(); i++)
	{
		triangle temptri = *(tris1[i]);
		double tempmag = temptri.unit_normal.cross(direction).mag();
		if (tempmag < delta)
		{
			if (tempmag < mag)
			{
				tri1 = temptri;
				mag = tempmag;
			}
		}
	}
	for (int i = 0; i < tris2.size(); i++)
	{
		triangle temptri = *(tris2[i]);
		double tempmag = temptri.unit_normal.cross(direction).mag();
		if (tempmag < delta)
		{
			if (tempmag < mag)
			{
				tri2 = temptri;
				mag = tempmag;
			}
		}
	}
}

double sub_collide(vec3 r, std::vector<double> i) //r is a 3x1 column vector, i is an inertia tensor symmetric matrix, returns r(T)*i*r
{
	return ( pow(r[0],2)*i[0] + pow(r[1],2)*i[1] + pow(r[2],2)*i[2] + 2*( r[0]*r[1]*i[3] + r[0]*r[2]*i[5] + r[1]*r[2]*i[4] ) );
}

//vec3 normal is the outward pointing normal of tri1 OR cross product of the edges
void FizEngine::collide(FizObject& obj1, triangle& tri1, FizObject& obj2, triangle& tri2, vec3 normal, point p) //not sure if all of these are necessary Eric - you can change if you need to
{
	vec3 r1 = (tri1.vertices[0]->p + tri1.vertices[1]->p + tri1.vertices[2]->p)/3;
	vec3 r2 = (tri2.vertices[0]->p + tri2.vertices[1]->p + tri2.vertices[2]->p)/3;
	
	vec3 r1n = r1.cross(normal);
	vec3 r2n = r2.cross(normal);
	
	vec3 relvel = obj1.getVel() - obj2.getVel();
	double velcomp = normal.dot(relvel);
	double rotcomp = obj1.getOme().dot(r1n) - obj2.getOme().dot(r2n);
	double rot1 = sub_collide(r1n, obj1.getInertiaTensorInvWorld());
	double rot2 = sub_collide(r2n, obj2.getInertiaTensorInvWorld());
	
	double forcemag = -2 * (velcomp + rotcomp) / ( 1/obj1.getMass() + 1/obj2.getMass() + rot1 + rot2 );
	
	vec3 f1 = normal*-forcemag;
	vec3 f2 = f1*-1;
	vec3 t1 = f1.cross(r1);
	vec3 t2 = f2.cross(r2);
	
	(*evaluatedForces)[&obj1].first += f1;
	(*evaluatedForces)[&obj1].second += t1;
	(*evaluatedForces)[&obj2].first += f2;
	(*evaluatedForces)[&obj2].second += t2;
}

// Get from cache or evaluate:	
fizdatum FizEngine::getForceVal(const std::string& force, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2)
{	
	if(contains(fcache,force))
	{		
		fizdatum& cachedVal=fcache[force];
		if(cachedVal.type==INPROGRESS)
		{
			throw std::logic_error("No circular references, please");
		}
		return cachedVal;
	}
	if(!contains(*forces,force))
	{
		throw std::logic_error("Invalid force");
	}
	fizdatum& cachedVal=fcache[force];
	cachedVal.type=INPROGRESS;
	(*forceEvaled)[force] = true;
	return cachedVal=(*forces)[force]->getForce(obj1, tri1, obj2, tri2);
}

fizdatum FizEngine::getMacroVal(const std::string& macro, const FizObject& obj1, const triangle& tri1, const FizObject& obj2, const triangle& tri2)
{
std::cout << &mcache <<std::endl;	
std::cout << "GONNA CHECK THE MCACHE" << '\n';
	if(contains(mcache,macro))
	{		
std::cout << "IT'S IN THERE" << '\n';
		fizdatum& cachedVal=mcache[macro];
		if(cachedVal.type==INPROGRESS)
		{
			throw std::logic_error("No circular references, please");
		}
		return cachedVal;
	}
std::cout << "IT'S NOT IN THERE" << '\n';
std::cout << "UH OH"<<macro<<std::endl;
std::cout << this->props <<std::endl;
std::cout << (*props)[macro]<<std::endl;
/*if (props == NULL) std::cout << "OH NO PROPS IS NULLS" << '\n';*/
	if(!contains(*props,macro))
	{
std::cout << "IT'S NOT IN THERE" << '\n';
		throw std::logic_error("Invalid macro");
	}
std::cout << "IT'S IN THERE" << '\n';
	fizdatum& cachedVal=mcache[macro];
	cachedVal.type=INPROGRESS;
	return cachedVal=(*props)[macro]->eval(obj1, tri1, obj2, tri2);
}

fizdatum FizEngine::getConstVal(const std::string& constant)
{
std::cout << "ABOUT TO CHECK THE CCACHE" << '\n';
	if(!contains(*ccache,constant))
	{
		throw std::logic_error("Invalid constant");
	}
std::cout << "IT'S IN THERE" << '\n';
	return (*ccache)[constant];
}

fizdatum FizEngine::getPropVal(const std::string& objectname, const std::string& identifier)
{
	return thisStep->find(objectname)->second->getProperty(identifier);
}

void FizEngine::clearDistributedCaches()
{
	for(std::set<std::string>::const_iterator it = macrodist.begin(); it != macrodist.end(); ++it)
	{
		mcache.erase(*it);
	}
	for(std::set<std::string>::const_iterator it = forcedist.begin(); it != forcedist.end(); ++it)
	{
		fcache.erase(*it);
	}
}

void FizEngine::clearNonsymmetricCaches()
{
	for(std::set<std::string>::const_iterator it = macrosymmetric.begin(); it != macrosymmetric.end(); ++it)
	{
		mcache.erase(*it);
	}

	for(std::set<std::string>::const_iterator it = forcesymmetric.begin(); it != forcesymmetric.end(); ++it)
	{
		fcache.erase(*it);
	}
}
#endif

