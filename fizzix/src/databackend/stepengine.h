#ifndef STEPENGINE_H
#define STEPENGINE_H
#include <QThread>
#include <QObject>
#include <QMap>
#include <QString>
#include <QTimer>
#include <libfizzix/fizengine.h>
#include "databackend.h"
#include "maputil.h"

class StepEngine:public QObject
{	Q_OBJECT
	private:
		DataBackend * db;
		FizEngine *eng;
		QTimer * timer;
		double dt;
	private slots:
		void step();
	public:
		StepEngine(DataBackend * _db);
		double getDt();
	public slots:
		void setDt(double _dt);
		void startPull();
		void stopPull();
	signals:
		void newDataAvailable();
		void statusChanged(QString info, bool error);
		
};


#endif
