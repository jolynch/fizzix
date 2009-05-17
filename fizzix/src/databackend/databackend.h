#ifndef DATABACKEND_H
#define DATABACKEND_H

#include <QObject>
#include <QUndoStack>
#include <QUndoCommand>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include "mapkeylistmodel.h"
#include "drawableobject.h"
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizforce.h>
#include <libfizzix/fizobject.h>
#include <libfizzix/fizformula.h>

class ChangeFactory;

class DataBackend:public QObject
{	Q_OBJECT
	private:
		bool dataLock;
		bool lastChangeUnpredictable;
		int unpredictableChange;
		MapKeyListModel <DrawableObject *> * objects;
		MapKeyListModel <FizForce *> * forces;
		MapKeyListModel <FizFormula *> * macros;
		MapKeyListModel <fizdatum> * constants;
		ChangeFactory * dataInserter;
		QUndoStack * dataChanges;
		
	public:
		DataBackend();
		bool isDataLocked();
		MapKeyListModel <DrawableObject *> * getObjectModel();
		MapKeyListModel <FizForce *> * getForceModel();
		MapKeyListModel <FizFormula *> * getMacroModel();
		MapKeyListModel <fizdatum> * getConstModel();
		QUndoStack * getUndoStack();
		void setDataInserter(ChangeFactory * di);
		ChangeFactory * getDataInserter();
		
	public slots:
		void dataUndone(int index);
		void toggleDataLock();
		void applyDataChange(QUndoCommand * c);
		void applyUnpredictableDataChange(QUndoCommand * c, bool addToStack);

	signals:
		void dataLocked(bool locked);
};

#endif
