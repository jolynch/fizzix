#ifndef STEPENGINE_CPP
#define STEPENGINE_CPP
#include "stepengine.h"

StepEngine::StepEngine(DataBackend * _db) : QObject()
{
	dt=0.1;
	db=_db;
	eng=new FizEngine();
	timer=new QTimer();
	timer->setSingleShot(false);
	QObject::connect(timer,SIGNAL(timeout()),this,SLOT(step()));
	changesSaved=false;
	emit statusChanged("Engine ready", 0);
} 

double StepEngine::getDt()
{return dt;}

std::map<std::string, FizObject *> * StepEngine::castToFizObject(QMap<QString, DrawableObject *> param)
{
	std::map<std::string, FizObject *> * out=new std::map<std::string, FizObject *> ();
	QMapIterator<QString, DrawableObject *> i(param);
	while(i.hasNext()) 
	{
			i.next();
			(*out)[(i.key().toStdString())]=((FizObject *)i.value());
	}
	return out;
}

QMap<QString, DrawableObject *> * StepEngine::castFromFizObject(std::map<std::string, FizObject *> * param)
{
	QMap<QString, DrawableObject *> * out=new QMap<QString, DrawableObject *>();
	std::map<std::string, FizObject *>::iterator p;
	for(p = param->begin(); p != param->end(); p++)
	{
		out->insert(QString(p->first.c_str()),new DrawableObject(p->second));
	}
	return out;
}

void StepEngine::createUndoCommand()
{
	if(changesSaved)
	{
		db->applyUnpredictableDataChange(new ChangeFactory::DC_RunSimulation(db,initData,db->getObjectModel()->getData()), 1);
		changesSaved=false;
	}
}

void StepEngine::step()
{
	std::map <std::string, FizObject *> * oldObjs=castToFizObject(*(db->getObjectModel()->getData()));
	std::map <std::string, FizObject *> * newObjs=castToFizObject(*(db->getObjectModel()->getData()));
	std::map <std::string, FizForce *> * oldFrcs=MapUtil<FizForce>::qMapToStdMapCopy(*(db->getForceModel()->getData()));
	std::map <std::string, FizFormula *> * oldMcrs=MapUtil<FizFormula>::qMapToStdMapCopy(*(db->getMacroModel()->getData()));
	std::map <std::string, fizdatum> * oldCnst=MapUtil<fizdatum>::qMapToStdMapCopy(*(db->getConstModel()->getData()));
	try{eng->step(oldObjs,newObjs,oldFrcs,oldMcrs,oldCnst,dt);}
	catch(std::logic_error e)
	{
		QString errmsg("Engine stopped: ");
		errmsg.append(e.what());
		emit statusChanged(errmsg,true);
		timer->stop();
		db->toggleDataLock();
		return;
	}
	catch(std::exception e)
	{
		QString errmsg("Engine stopped: ");
		errmsg.append(e.what());
		emit statusChanged(errmsg,true);
		timer->stop();
		db->toggleDataLock();
		return;
	}
	MapUtil<FizObject>::deepDelete(oldObjs);
	delete oldCnst;
	MapUtil<FizFormula>::deepDelete(oldMcrs);
	MapUtil<FizForce>::deepDelete(oldFrcs);
	QMap<QString, DrawableObject *> * out=castFromFizObject(newObjs);
	MapUtil<FizObject>::deepDelete(newObjs);
	db->getDataInserter()->changeObjectsFromSim(out);
	changesSaved=true;
}

void StepEngine::setDt(double _dt)
{
	dt=_dt;
	if(timer->isActive())
	{
		timer->stop();
		timer->setInterval(dt);
		timer->start();
	}
	emit statusChanged("Engine dt changed sucessfully", 0);
}

void StepEngine::startPull()
{
	timer->setInterval(dt);
	timer->start();
	db->toggleDataLock();
	initData=db->getObjectModel()->getData();
	changesSaved=false;
	emit statusChanged("Engine started", 0);
}

void StepEngine::stopPull()
{
	timer->stop();
	db->toggleDataLock();
	emit statusChanged("Engine stopped", 0);
}

#endif
