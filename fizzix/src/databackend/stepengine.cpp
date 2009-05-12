#ifndef STEPENGINE_CPP
#define STEPENGINE_CPP
#include "stepengine.h"


	StepEngine::StepEngine(double _dt, DataBackend * _db, FizEngine _eng) : dt(_dt),db(_db),eng(_eng) {} 

	StepEngine::run()
	{
		// Anton's part
	}

	StepEngine::step()
	{
		// Get out of databackend
		// Need: thisStep, nextStep, forces, macros, ccache, dt:
		std::map<std::string, FizObject*> * new_data;
		eng.step
		(
			qMapToStdMap(db->getObjectModel()->getData()), // Need to do create FizObject from DrawableObject
			new_data,
			qMapToStdMap(db->getForceModel()->getData()),
			qMapToStdMap(db->getMacroModel()->getData()),
			qMapToStdMap(db->getConstModel()->getData()),
		);
		db->getObjectModel()->setData(QMap(new_data)); // Need to create DrawableObject from FizObject
		// Put back in databackend
		emit newDataAvailable();
	}

#endif
