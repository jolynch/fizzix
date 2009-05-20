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
		//Creates an Object from an XML node.
		void createObject(QDomNode d_);
		//Creates a Force from an XML node.
		void createForce(QDomNode d_);
		//Creates a Macro from an XML node.
		void createMacro(QDomNode d_);
		//Creates a Constant from an XML node.
		void createConstant(QDomNode d_);
		//Creates an XML node from information about an Object.
		QDomNode createObjectNode(QString name, DrawableObject n, QDomDocument * d);
		//Creates an XML node from information about an Constant.
		QDomNode createConstantNode(QString name, fizdatum n, QDomDocument * d);
		//Creates an XML node from information about an Force.
		QDomNode createForceNode(QString name, FizForce n, QDomDocument * d);
		//Creates an XML node from information about an Formula.
		QDomNode createFormulaNode(QString name, FizFormula n, QDomDocument * d);
		//Saves data to an XML file.
		void saveDataAsXML(QString filename);
		//Loads data from an XML file.
		void loadDataFromXML(QString filename);
		
	public:
		//Creates a DataBackend, which holds all the data and functions that need to be distributed throughout the program.
		DataBackend();
		//Returns true if data is locked and simulation is running.
		bool isDataLocked();
		//Checks is data should be saved, and saves it if so.
		bool checkBeforeDataUnload();
		//Returns true if the undo stack is volatile.
		bool haveUnpredicatableChanges();
		//Returns the current Object data.
		MapKeyListModel <DrawableObject *> * getObjectModel();
		//Returns the current Force data.
		MapKeyListModel <FizForce *> * getForceModel();
		//Returns the current Macro data.
		MapKeyListModel <FizFormula *> * getMacroModel();
		//Returns the current Const data.
		MapKeyListModel <fizdatum> * getConstModel();
		//Returns the current undo stack.
		QUndoStack * getUndoStack();	
		//Sets the data inserter, which must be created after DataBackend.
		void setDataInserter(ChangeFactory * di);
		//Returns the data inserter.
		ChangeFactory * getDataInserter();
		//Parses a QString to a fizstack, catching any parse errors.
		fizstack parse(QString in);
		
	public slots:
		//Checks if the data can be reset from simulations.
		void dataUndone(int index);
		//Toggles data lock, if the simulation is running.
		void toggleDataLock();
		//Applies a data change that is predictable, adding it to the undo stack.
		void applyDataChange(QUndoCommand * c);
		//Applies a data change that is unpredictable, optionally adding it to the undo stack.
		void applyUnpredictableDataChange(QUndoCommand * c, bool addToStack);
		//Allows the user to ignore the warnings about clearing the stack.
		void setWarning(bool b);
		//Allows the user to select where to save the data.
		void saveAs();
		//Saves the data.
		void save();
		//Allows the user to select what scenario to load.
		void load();
		//Loads a new blank scenario.
		void newFromBlank();
		//Loads a new default scenario.
		void newFromDefault();
		//Clears data for a new file.
		void purgeData();
		//Checks if we need to save and quits.
		void quit();

	signals:
		//Emits when new unpredicatable changes are inserted.
		void gainedUnpredicatableChanges(bool);
		//Emits when the simulation begins running or is locked.
		void dataLocked(bool locked);
		//Emits when there are parser errors.
		void statusChanged(QString, int);
		//Emits when data is deleted.
		void unloadData();
};


#endif
