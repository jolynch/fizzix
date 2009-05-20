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
		QMap<QString, DrawableObject *> * initData;
		double dt;
	private slots:
		void step();
	private:
		std::map<std::string, FizObject *> * castToFizObject(QMap<QString, DrawableObject *> param);
		QMap<QString, DrawableObject *> * castFromFizObject(std::map<std::string, FizObject *> * param);
		void setCorrectFizEngines();
		void setCorrectFizEngine(fizstack f);
		void createUndoCommand();
	public:
		StepEngine(DataBackend * _db);
		double getDt();
	public slots:
		void setDt(double _dt);
		void startPull();
		void stopPull();
	signals:
		void newDataAvailable();
		void statusChanged(QString info, int error);
};


#endif
