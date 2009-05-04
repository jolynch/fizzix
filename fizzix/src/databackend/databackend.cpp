#ifndef DATABACKEND_CPP
#define DATABACKEND_CPP
#include "databackend.h"

DataBackend::DataBackend():QObject()
{
	dataLock=false;
	lastChangeUnpredictable=false;
	
	objects=new MapKeyListModel <DrawableObject *> ();
	forces=new MapKeyListModel <FizForce *> ();
	macros=new MapKeyListModel <FizFormula *> ();
	constants=new MapKeyListModel <fizdatum> ();
	dataChanges=new QUndoStack();
}

bool DataBackend::isDataLocked()
{return dataLock;}

MapKeyListModel <DrawableObject *> * DataBackend::getObjectModel()
{return objects;}

MapKeyListModel <FizForce *> * DataBackend::getForceModel()
{return forces;}

MapKeyListModel <FizFormula *> * DataBackend::getMacroModel()
{return macros;}

MapKeyListModel <fizdatum> * DataBackend::getConstModel()
{return constants;}

QUndoStack * DataBackend::getUndoStack()
{return dataChanges;}

void DataBackend::toggleDataLock()
{dataLock=!dataLock;}

void DataBackend::applyDataChange(QUndoCommand * c)
{
	if(!lastChangeUnpredictable)
	{
		c->redo();
		dataChanges->push(c);
	}
	else
	{
		//Popup, you lose previous undo stack.
		//Tell stepengine to ditch init conditions.
		c->redo();
		dataChanges->push(c);
	}
}

void DataBackend::applyUnpredictableDataChange(QUndoCommand * c)
{
	lastChangeUnpredictable=true;
	c->redo();
	dataChanges->push(c);
}

#endif
