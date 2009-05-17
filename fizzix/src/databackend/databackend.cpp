#ifndef DATABACKEND_CPP
#define DATABACKEND_CPP
#include "databackend.h"

DataBackend::DataBackend():QObject()
{
	dataLock=false;
	lastChangeUnpredictable=false;
	unpredictableChange=0;
	objects=new MapKeyListModel <DrawableObject *> ();
	forces=new MapKeyListModel <FizForce *> ();
	macros=new MapKeyListModel <FizFormula *> ();
	constants=new MapKeyListModel <fizdatum> ();
	dataChanges=new QUndoStack();
	QObject::connect(dataChanges,SIGNAL(indexChanged(int)),this,SLOT(dataUndone(int)));
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

void DataBackend::setDataInserter(ChangeFactory * di)
{dataInserter=di;}

ChangeFactory * DataBackend::getDataInserter()
{return dataInserter;}

void DataBackend::toggleDataLock()
{
	dataLock=!dataLock;
	emit dataLocked(dataLock);
}

void DataBackend::applyDataChange(QUndoCommand * c)
{
	if(!lastChangeUnpredictable)
	{
		c->redo();
		dataChanges->push(c);
	}
	else
	{
		if(QMessageBox::question(NULL, "Clear Undo Stack?", 
			"Making changes to the input data will prevent you from resetting to the state before the engine ran. Make changes?",
			QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
		{
			dataChanges->clear(); //MASSIVE UTTERLY ENORMOUS MEMORY LEAK.
			c->redo();
			dataChanges->push(c);
			lastChangeUnpredictable=false;
		}
	}
}

void DataBackend::applyUnpredictableDataChange(QUndoCommand * c, bool addToStack)
{
	lastChangeUnpredictable=true;
	c->redo();
	if(addToStack)
	{
		dataChanges->push(c);
		unpredictableChange=dataChanges->index();
	}
}


void DataBackend::dataUndone(int index)
{
	if(index<unpredictableChange)
		lastChangeUnpredictable=false;
}

fizstack DataBackend::parse(QString in)
{
	fizstack out;
	int i=0;
	try{
		out=Parser::parse(in,i);
	}
	catch(std::logic_error e)
	{
		QString errmsg("Parser error: ");
		errmsg.append(e.what());
		emit statusChanged(errmsg,2);
		return out;
	}
	catch(std::exception e)
	{
		QString errmsg("Parser error: ");
		errmsg.append(e.what());
		emit statusChanged(errmsg,2);
		return out;
	}
	return out;
}
#endif
