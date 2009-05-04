#ifndef DATABACKEND_H
#define DATABACKEND_H

#include <QObject>
#include <QUndoStack>
#include <QUndoCommand>
#include <QFile>
#include <QString>
#include "mapkeylistmodel.h"
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizforce.h>
#include <libfizzix/fizobject.h>
#include <libfizzix/fizformula.h>

class DataBackend:public QObject
{	Q_OBJECT
	private:
		bool dataLock;
		bool lastChangeUnpredictable;
		MapKeyListModel <FizObject *> * objects;
		MapKeyListModel <FizForce *> * forces;
		MapKeyListModel <FizFormula *> * macros;
		MapKeyListModel <fizdatum> * constants;
		QUndoStack * dataChanges;
		
	public:
		DataBackend();
		bool isDataLocked();
		MapKeyListModel <FizObject *> * getObjectModel();
		MapKeyListModel <FizForce *> * getForceModel();
		MapKeyListModel <FizFormula *> * getMacroModel();
		MapKeyListModel <fizdatum> * getConstModel();
		QUndoStack * getUndoStack();
		
	public slots:
		void toggleDataLock();
		void applyDataChange(QUndoCommand * c);
		void applyUnpredictableDataChange(QUndoCommand * c);
};

#endif
