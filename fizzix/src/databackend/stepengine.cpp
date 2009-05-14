#ifndef STEPENGINE_CPP
#define STEPENGINE_CPP
#include "stepengine.h"


	StepEngine::StepEngine(double _dt, DataBackend * _db) : QObject()
	{
		dt=_dt;
		db=_db;
		eng=new FizEngine();
	} 

	void StepEngine::run()
	{
		step();
	}

	void StepEngine::step()
	{
		// Get out of databackend
		// Need: thisStep, nextStep, forces, macros, ccache, dt:
		//std::map<std::string, FizObject*> * new_data;
		/*eng->step
		(
			MapUtil<DrawableObject *>::qMapToStdMap(*(db->getObjectModel()->getData())), // Need to do create FizObject from DrawableObject
			new_data,
			MapUtil<FizForce *>::qMapToStdMap(*(db->getForceModel()->getData())),
			MapUtil<FizFormula *>::qMapToStdMap(*(db->getMacroModel()->getData())),
			MapUtil<fizdatum>::qMapToStdMap(*(db->getConstModel()->getData())),
		);*/
		//db->getObjectModel()->setData(QMap(new_data)); // Need to create DrawableObject from FizObject
		// Put back in databackend
		emit newDataAvailable();
	}

#endif
