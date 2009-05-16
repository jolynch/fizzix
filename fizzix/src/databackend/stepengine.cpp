#ifndef STEPENGINE_CPP
#define STEPENGINE_CPP
#include "stepengine.h"

StepEngine::StepEngine(DataBackend * _db) : QObject()
{
	dt=0.1;
	db=_db;
	eng=new FizEngine();
} 

double StepEngine::getDt()
{return dt;}

void StepEngine::step()
{
}

void StepEngine::setDt(double _dt)
{
}

void StepEngine::startPull()
{
}

void StepEngine::stopPull()
{
}

#endif
