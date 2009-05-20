#ifndef STEPENGINE_H
#define STEPENGINE_H
#include <QThread>
#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QUndoCommand>
#include <QDebug>
#include <map>
#include <libfizzix/fizengine.h>
#include "databackend.h"
#include "changefactory.h"
#include "maputil.h"

// StepEngine calls the library's "step()" in a loop-ed manner.
class StepEngine:public QObject
{	Q_OBJECT
	private:
		bool lockstep;
		bool changesSaved;
		DataBackend * db;
		FizEngine *eng;
		QTimer * timer;
		QMap<QString, DrawableObject *> * initData; //Data to be saved on the undo stack.
		double dt;
	private slots:
		//This is the function that actually calls step in the FizEngine.
		void step();
	private:
		//Utility function to cast maps with DrawableObjects to FizObjects.
		std::map<std::string, FizObject *> * castToFizObject(QMap<QString, DrawableObject *> param);
		//Utility function to cast maps with FizObjects to DrawableObjects.
		QMap<QString, DrawableObject *> * castFromFizObject(std::map<std::string, FizObject *> * param);
		//Goes through all FizFormulas, and enforces a valid engine pointer.
		void setCorrectFizEngines();
		//Utility function to set all the engine pointers in the fizstack to eng.
		void setCorrectFizEngine(fizstack f);
		//Creates a data structure to push onto the UndoStack, and does so.
		void createUndoCommand();
	public:
		//Creates a StepEngine that is a handler loop to call step over periods of time.
		StepEngine(DataBackend * _db);
		//Retrieves the time delta.
		double getDt();
	public slots:
		//Sets the time delta of the simulation.
		void setDt(double _dt);
		//Begins the loop to call step.
		void startPull();
		//Ends the loop to call step.
		void stopPull();
	signals:
		//This signal is emitted when the data structure changes.
		void newDataAvailable();
		//This signal is emitted with errors or status changes.
		void statusChanged(QString info, int error);
};


#endif
