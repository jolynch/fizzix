#ifndef CHANGEFACTORY_H
#define CHANGEFACTORY_H
#include <QObject>
#include <QUndoCommand>
#include <QString>
#include "databackend.h"
#include "mapkeylistmodel.h"
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizforce.h>
#include <libfizzix/fizobject.h>
#include <libfizzix/fizformula.h>

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
		DC_AddElement(QString n, MapKeyListModel <T> * t, T i=NULL);
		void undo();
		void redo();
	};
	
	template <class T>
	class DC_DeleteElement : public QUndoCommand
	{
	private:
		MapKeyListModel <T> * target;
		QString name;
		T val;
	public:
		DC_DeleteElement(QString n, MapKeyListModel <T> * t);
		void undo();
		void redo();
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
		DC_RenameElement(QString on, QString nn, MapKeyListModel <T> * t);
		void undo();
		void redo();
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
		DC_ModifyElement(QString n, MapKeyListModel <T> * t, T nv);
		void undo();
		void redo();
	};
#endif //CHANGES_H
public:
	ChangeFactory(DataBackend * _db);
public slots:
	void addObject(QString n);
	void addForce(QString n);
	void addConstant(QString n);
	void addMacro(QString n);
	void deleteObject(QString n);
	void deleteForce(QString n);
	void deleteConstant(QString n);
	void deleteMacro(QString n);
	void renameObject(QString on, QString nn);
	void renameForce(QString on, QString nn);
	void renameConstant(QString on, QString nn);
	void renameMacro(QString on, QString nn);
	void modifyObject(QString n, DrawableObject * nv);
	void modifyForce(QString n, FizForce * nv);
	void modifyConstant(QString n, fizdatum nv);
	void modifyMacro(QString n, FizFormula * nv);
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

#endif
