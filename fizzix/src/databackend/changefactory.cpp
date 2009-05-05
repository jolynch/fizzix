#ifndef CHANGEFACTORY_CPP
#define CHANGEFACTORY_CPP
#include "changefactory.h"

ChangeFactory::ChangeFactory(DataBackend * _db):QObject()
{
	db=_db;
}

void ChangeFactory::addObject(QString n)
{
	DC_AddElement <DrawableObject *> * dc=new DC_AddElement <DrawableObject *> (n, db->getObjectModel());
	db->applyDataChange(dc);
}

void ChangeFactory::deleteObject(QString n)
{
	DC_DeleteElement <DrawableObject *> * dc=new DC_DeleteElement <DrawableObject *> (n, db->getObjectModel());
	db->applyDataChange(dc);
}

void ChangeFactory::addForce(QString n)
{
	DC_AddElement <FizForce *> * dc=new DC_AddElement <FizForce *> (n, db->getForceModel());
	db->applyDataChange(dc);
}

void ChangeFactory::deleteForce(QString n)
{
	DC_DeleteElement <FizForce *> * dc=new DC_DeleteElement <FizForce *> (n, db->getForceModel());
	db->applyDataChange(dc);
}

void ChangeFactory::addMacro(QString n)
{
	DC_AddElement <FizFormula *> * dc=new DC_AddElement <FizFormula *> (n, db->getMacroModel());
	db->applyDataChange(dc);
}

void ChangeFactory::deleteMacro(QString n)
{
	DC_DeleteElement <FizFormula *> * dc=new DC_DeleteElement <FizFormula *> (n, db->getMacroModel());
	db->applyDataChange(dc);
}

void ChangeFactory::addConstant(QString n)
{
	DC_AddElement <fizdatum> * dc=new DC_AddElement <fizdatum> (n, db->getConstModel(), fizdatum());
	db->applyDataChange(dc);
}

void ChangeFactory::deleteConstant(QString n)
{
	DC_DeleteElement <fizdatum> * dc=new DC_DeleteElement <fizdatum> (n, db->getConstModel());
	db->applyDataChange(dc);
}

#endif
