#ifndef STEPENGINE_H
#define STEPENGINE_H
#include <QThread>
#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>
#include <QUndoCommand>
#include <map>
#include <libfizzix/fizengine.h>
#include "databackend.h"
#include "changefactory.h"
#include "maputil.h"

class StepEngine:public QObject
{	Q_OBJECT
	private:
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
