#ifndef CHANGEFACTORY_H
#define CHANGEFACTORY_H
#include <QObject>
#include <QUndoCommand>
#include "databackend.h"
#include "mapkeylistmodel.h"
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizforce.h>
#include <libfizzix/fizobject.h>
#include <libfizzix/fizformula.h>

// All of these classes are nodes that can be added to the undo stack. ChangeFactory gives some nice commands for constructing them and adding them to the undo stack. Each internal class is a different action that can be undone.
class ChangeFactory : public QObject
{	Q_OBJECT
private:
	DataBackend * db;
protected:
#ifndef CHANGES_H
#define CHANGES_H
	template <class T>
	class DC_AddElement : public QUndoCommand
	{
	private:
		MapKeyListModel <T> * target;
		QString name;
		T initVal;
	public:
		//Creates a change adding an element that can be pushed onto the undo stack.
		DC_AddElement(QString n, MapKeyListModel <T> * t, T i=NULL);
		void undo(); //Undoes the change.
		void redo(); //Does the change.
	};
	
	template <class T>
	class DC_DeleteElement : public QUndoCommand
	{
	private:
		MapKeyListModel <T> * target;
		QString name;
		T val;
	public:
		//Creates a change deleting an element that can be pushed onto the undo stack.
		DC_DeleteElement(QString n, MapKeyListModel <T> * t);
		void undo(); //Undoes the change.
		void redo(); //Does the change.
	};
	
	template <class T>
	class DC_ClearElements : public QUndoCommand
	{
	private:
		MapKeyListModel <T> * target;
		QMap<QString, T> * old;
	public:
		//Creates a change clearing an element that can be pushed onto the undo stack.
		DC_ClearElements(MapKeyListModel <T> * t);
		//WARNING: CURRENTLY DOES NOT UNDO CORRECTLY
		void undo(); //Undoes the change.
		void redo(); //Does the change.
	};
	
	template <class T>
	class DC_RenameElement : public QUndoCommand
	{
	private:
		MapKeyListModel <T> * target;
		QString newName;
		QString oldName;
		T val;
	public:
		//Creates a change renaming an element that can be pushed onto the undo stack.
		DC_RenameElement(QString on, QString nn, MapKeyListModel <T> * t);
		void undo(); //Undoes the change.
		void redo(); //Does the change.
	};
	
	
	template <class T>
	class DC_ModifyElement : public QUndoCommand
	{
	private:
		MapKeyListModel <T> * target;
		QString name;
		T oldVal;
		T newVal;
	public:
		//Creates a change modifying an element that can be pushed onto the undo stack.
		DC_ModifyElement(QString n, MapKeyListModel <T> * t, T nv);
		void undo(); //Undoes the change.
		void redo(); //Does the change.
	};

public:
	class DC_RunSimulation : public QUndoCommand
	{
	private:
		DataBackend * db;
		bool constructor1;
		QMap<QString, DrawableObject *> * oldData;
		QMap<QString, DrawableObject *> * newData;
	public:
		//Creates a change running a simulation that can be pushed onto the undo stack.
		DC_RunSimulation(DataBackend * db, QMap<QString, DrawableObject *> * _newData);
		DC_RunSimulation(DataBackend * db, QMap<QString, DrawableObject *> * _oldData, QMap<QString, DrawableObject *> * _newData);
		void undo(); //Undoes the change.
		void redo(); //Does the change.
	};
	
#endif //CHANGES_H
public:
	//Creates a data inserter that contains utility functions to edit data, inserting it onto the undo stack.
	ChangeFactory(DataBackend * _db);
public slots:
	//Utility function to add an Object.
	void addObject(QString n);
	//Utility function to add a Force.
	void addForce(QString n);
	//Utility function to add a Constant.
	void addConstant(QString n);
	//Utility function to add a Macro.
	void addMacro(QString n);
	//Utility function to delete an Object.
	void deleteObject(QString n);
	//Utility function to delete a Force.
	void deleteForce(QString n);
	//Utility function to delete a Constant.
	void deleteConstant(QString n);
	//Utility function to delete a Macro.
	void deleteMacro(QString n);
	//Utility function to rename an Object.
	void renameObject(QString on, QString nn);
	//Utility function to rename a Force.
	void renameForce(QString on, QString nn);
	//Utility function to rename a Constant.
	void renameConstant(QString on, QString nn);
	//Utility function to rename a Macro.
	void renameMacro(QString on, QString nn);
	//Utility function to modify an Object.
	void modifyObject(QString n, DrawableObject * nv);
	//Utility function to modify a Force.
	void modifyForce(QString n, FizForce * nv);
	//Utility function to modify a Constant.
	void modifyConstant(QString n, fizdatum nv);
	//Utility function to modify a Macro.
	void modifyMacro(QString n, FizFormula * nv);
	//Changes the Objects with new data.
	void changeObjectsFromSim(QMap<QString, DrawableObject *> * newData);
	//Utility function to clear all Objects.
	void clearObjects();
	//Utility function to clear all Forces.
	void clearForces();
	//Utility function to clear all Macros.
	void clearMacros();
	//Utility function to clear all Constants.
	void clearConstants();
};

#endif //CHANGEFACTORY_H

#ifndef CHANGES_CPP
#define CHANGES_CPP
template <class T>
ChangeFactory::DC_AddElement<T>::DC_AddElement(QString n, MapKeyListModel <T> * t, T i):QUndoCommand()
{
	QString te="Create ";
	te.append(n);
	this->setText(te);
	name=n;
	target=t;
	initVal=i;
}

template <class T>
void ChangeFactory::DC_AddElement<T>::redo()
{
	target->setElement(name, initVal);
}

template <class T>
void ChangeFactory::DC_AddElement<T>::undo()
{
	target->delElement(name);
}

template <class T>
ChangeFactory::DC_DeleteElement<T>::DC_DeleteElement(QString n, MapKeyListModel <T> * t):QUndoCommand()
{
	QString te="Delete ";
	te.append(n);
	this->setText(te);
	name=n;
	target=t;
	val=target->getData()->value(name);
}

template <class T>
void ChangeFactory::DC_DeleteElement<T>::redo()
{
	target->delElement(name);
}

template <class T>
void ChangeFactory::DC_DeleteElement<T>::undo()
{
	target->setElement(name, val);
}

template <class T>
ChangeFactory::DC_RenameElement<T>::DC_RenameElement(QString on, QString nn, MapKeyListModel <T> * t):QUndoCommand()
{
	QString te="Rename "; te.append(on); te.append(" to "); te.append(nn);
	this->setText(te);
	oldName=on;
	newName=nn;
	target=t;
	val=target->getData()->value(oldName);
}

template <class T>
void ChangeFactory::DC_RenameElement<T>::redo()
{
	target->setElement(newName, val);
	target->delElement(oldName);
}

template <class T>
void ChangeFactory::DC_RenameElement<T>::undo()
{
	target->setElement(oldName, val);
	target->delElement(newName);
}

template <class T>
ChangeFactory::DC_ModifyElement<T>::DC_ModifyElement(QString n, MapKeyListModel <T> * t, T nv):QUndoCommand()
{
	QString te="Modify "; te.append(n);
	this->setText(te);
	name=n;
	target=t;
	oldVal=target->getData()->value(name);
	newVal=nv;
}

template <class T>
void ChangeFactory::DC_ModifyElement<T>::redo()
{
	target->setElement(name,newVal);
}

template <class T>
void ChangeFactory::DC_ModifyElement<T>::undo()
{
	target->setElement(name,oldVal);
}

template <class T>
ChangeFactory::DC_ClearElements<T>::DC_ClearElements(MapKeyListModel <T> * t):QUndoCommand()
{
	target=t;
	old=t->getData();
	this->setText("Clear Elements");
}

template <class T>
void ChangeFactory::DC_ClearElements<T>::redo()
{
	target->purge();
}

template <class T>
void ChangeFactory::DC_ClearElements<T>::undo()
{
	target->setData(old,false);
}


#endif
