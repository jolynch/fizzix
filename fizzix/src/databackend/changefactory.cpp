#ifndef CHANGEFACTORY_CPP
#define CHANGEFACTORY_CPP
#include "changefactory.h"

ChangeFactory::ChangeFactory(DataBackend * _db):QObject()
{
	db=_db;
}

void ChangeFactory::addObject(QString n)
{
	DC_AddElement <DrawableObject *> * dc=new DC_AddElement <DrawableObject *> (n, db->getObjectModel(),new DrawableObject(n.toStdString()));
	db->applyDataChange(dc);
}

void ChangeFactory::deleteObject(QString n)
{
	DC_DeleteElement <DrawableObject *> * dc=new DC_DeleteElement <DrawableObject *> (n, db->getObjectModel());
	db->applyDataChange(dc);
}

void ChangeFactory::addForce(QString n)
{
	DC_AddElement <FizForce *> * dc=new DC_AddElement <FizForce *> (n, db->getForceModel(), new FizForce(FizFormula()));
	db->applyDataChange(dc);
}

void ChangeFactory::deleteForce(QString n)
{
	DC_DeleteElement <FizForce *> * dc=new DC_DeleteElement <FizForce *> (n, db->getForceModel());
	db->applyDataChange(dc);
}

void ChangeFactory::addMacro(QString n)
{
	DC_AddElement <FizFormula *> * dc=new DC_AddElement <FizFormula *> (n, db->getMacroModel(), new FizFormula());
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

void ChangeFactory::renameObject(QString on, QString nn)
{
	DC_RenameElement <DrawableObject *> * dc=new DC_RenameElement <DrawableObject *> (on, nn, db->getObjectModel());
	db->applyDataChange(dc);
}

void ChangeFactory::renameForce(QString on, QString nn)
{
	DC_RenameElement <FizForce *> * dc=new DC_RenameElement <FizForce *> (on, nn, db->getForceModel());
	db->applyDataChange(dc);
}

void ChangeFactory::renameConstant(QString on, QString nn)
{
	DC_RenameElement <fizdatum> * dc=new DC_RenameElement <fizdatum> (on, nn, db->getConstModel());
	db->applyDataChange(dc);
}

void ChangeFactory::renameMacro(QString on, QString nn)
{
	DC_RenameElement <FizFormula *> * dc=new DC_RenameElement <FizFormula *> (on, nn, db->getMacroModel());
	db->applyDataChange(dc);
}

void ChangeFactory::modifyObject(QString n, DrawableObject * nv)
{
	DC_ModifyElement <DrawableObject *> * dc=new DC_ModifyElement <DrawableObject *> (n, db->getObjectModel(), nv);
	db->applyDataChange(dc);
}

void ChangeFactory::modifyForce(QString n, FizForce * nv)
{
	DC_ModifyElement <FizForce *> * dc=new DC_ModifyElement <FizForce *> (n, db->getForceModel(), nv);
	db->applyDataChange(dc);
}

void ChangeFactory::modifyConstant(QString n, fizdatum nv)
{
	DC_ModifyElement <fizdatum> * dc=new DC_ModifyElement <fizdatum> (n, db->getConstModel(), nv);
	db->applyDataChange(dc);
}

void ChangeFactory::modifyMacro(QString n, FizFormula * nv)
{
	DC_ModifyElement <FizFormula *> * dc=new DC_ModifyElement <FizFormula *> (n, db->getMacroModel(), nv);
	db->applyDataChange(dc);
}


void ChangeFactory::changeObjectsFromSim(QMap<QString, DrawableObject *> * newData)
{
	DC_RunSimulation * dc=new DC_RunSimulation(db,newData);
	db->applyUnpredictableDataChange(dc,false);
}

ChangeFactory::DC_RunSimulation::DC_RunSimulation(DataBackend * _db, QMap<QString, DrawableObject *> * _newData)
{
	this->setText("Run Simulation");
	constructor1=true;
	db=_db;
	oldData=db->getObjectModel()->getData();
	newData=_newData;
}

ChangeFactory::DC_RunSimulation::DC_RunSimulation(DataBackend * _db, QMap<QString, DrawableObject *> * _oldData, QMap<QString, DrawableObject *> * _newData)
{
	this->setText("Run Simulation");
	constructor1=false;
	db=_db;
	oldData=_oldData;
	newData=_newData;
}

void ChangeFactory::DC_RunSimulation::redo()
{
	db->getObjectModel()->setData(newData,constructor1);
}

void ChangeFactory::DC_RunSimulation::undo()
{
	db->getObjectModel()->setData(oldData,constructor1);
}

#endif
