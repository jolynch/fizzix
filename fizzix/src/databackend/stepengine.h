#ifndef STEPENGINE_H
#define STEPENGINE_H
#include <QThread>
#include <QObject>
#include <QMap>
#include <QString>
#include <libfizzix/fizengine.h>
#include "databackend.h"
#include "maputil.h"


class StepEngine:public QObject
{	Q_OBJECT
	private:
		DataBackend * db;
		double dt;
		void step();
	public:
		FizEngine(double _dt, DataBackend * _db);
		void run();
	signals:
		void newDataAvailable();s
};


#endif
