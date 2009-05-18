#ifndef DATABACKEND_H
#define DATABACKEND_H

#include <QObject>
#include <QUndoStack>
#include <QUndoCommand>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QtXml>
#include "mapkeylistmodel.h"
#include "drawableobject.h"
#include "parser.h"
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
		QString currentName;
		MapKeyListModel <DrawableObject *> * objects;
		MapKeyListModel <FizForce *> * forces;
		MapKeyListModel <FizFormula *> * macros;
		MapKeyListModel <fizdatum> * constants;
		ChangeFactory * dataInserter;
		QUndoStack * dataChanges;
		
	private:
		//QDomNode createObjectNode(QString name, DrawableObject * n, QDomDocument * d);
		//QDomNode createConstantNode(QString name, fizdatum n, QDomDocument * d);
		//QDomNode createForceode(QString name, FizForce * n, QDomDocument * d);
		//QDomNode createFormulaNode(QString name, FizFormula * n, QDomDocument * d);
		//void saveDataAsXML(QString filename);
		//void loadDataFromXML(QString filename);
		
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
		fizstack parse(QString in);
		
	public slots:
		void dataUndone(int index);
		void toggleDataLock();
		void applyDataChange(QUndoCommand * c);
		void applyUnpredictableDataChange(QUndoCommand * c, bool addToStack);
		//void saveAs();
		//void save();

	signals:
		void dataLocked(bool locked);
		void statusChanged(QString, int);
};


#endif
