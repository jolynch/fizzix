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
};

#endif //CHANGEFACTORY_H

#ifndef CHANGES_CPP
#define CHANGES_CPP
template <class T>
ChangeFactory::DC_AddElement<T>::DC_AddElement(QString n, MapKeyListModel <T> * t, T i):QUndoCommand()
{
	this->setText("Create New Element");
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
	this->setText("Delete Element");
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

#endif
