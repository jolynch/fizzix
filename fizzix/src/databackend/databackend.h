#ifndef DATABACKEND_H
#define DATABACKEND_H

#include <QObject>
#include <QUndoStack>
#include <QUndoCommand>
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include <QtXml>
#include <QDebug>
#include "mapkeylistmodel.h"
#include "drawableobject.h"
#include "parser.h"
#include <libfizzix/gen_structs.h>
#include <libfizzix/fizforce.h>
#include <libfizzix/fizobject.h>
#include <libfizzix/fizformula.h>

class ChangeFactory;

// This class eases the interface with the backend. It does all the non-graphical work of the frontend.
class DataBackend:public QObject
{	Q_OBJECT
	private:
		bool dataLock;
		bool lastChangeUnpredictable;
		bool warnClear;
		int unpredictableChange;
		QString currentName;
		MapKeyListModel <DrawableObject *> * objects;
		MapKeyListModel <FizForce *> * forces;
		MapKeyListModel <FizFormula *> * macros;
		MapKeyListModel <fizdatum> * constants;
		ChangeFactory * dataInserter;
		QUndoStack * dataChanges;
		
	private:
		void createObject(QDomNode d_);
		void createForce(QDomNode d_);
		void createMacro(QDomNode d_);
		void createConstant(QDomNode d_);
		QDomNode createObjectNode(QString name, DrawableObject n, QDomDocument * d);
		QDomNode createConstantNode(QString name, fizdatum n, QDomDocument * d);
		QDomNode createForceNode(QString name, FizForce n, QDomDocument * d);
		QDomNode createFormulaNode(QString name, FizFormula n, QDomDocument * d);
		void saveDataAsXML(QString filename);
		void loadDataFromXML(QString filename);
		
	public:
		DataBackend();
		bool isDataLocked();
		bool checkBeforeDataUnload();
		bool haveUnpredicatableChanges();
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
		void setWarning(bool b);
		void saveAs();
		void save();
		void load();
		void newFromBlank();
		void newFromDefault();
		void purgeData();
		void quit();

	signals:
		void gainedUnpredicatableChanges(bool);
		void dataLocked(bool locked);
		void statusChanged(QString, int);
		void unloadData();
};


#endif
