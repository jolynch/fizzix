/************************************************************************************************
This file is a part of the Fizzix project, which provides a physics engine and the visualization.
The website for this project is http://code.google.com/p/fizzix .
Copyright (C) 2009
	Joseph Lynch
	Anton Frolenkov
	Purnima Balakrishnan
	Daniel Stiles
	Eric Van Albert

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
************************************************************************************************/


#ifndef SIMULATIONCONTROL_CPP
#define SIMULATIONCONTROL_CPP

#include "simulationcontrol.h"

SimulationControl::SimulationControl(DataBackend * _db):QDockWidget(tr("Simulation control"))
{
	db=_db;
	eng=new StepEngine(db);
	
	QWidget * container=new QWidget();
	QGridLayout * layout=new QGridLayout();
	status=new QLabel();
	statusChanged("Engine ready",false);
	status->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
	status->setAutoFillBackground(true);
	layout->addWidget(status,0,0);
	layout->addWidget(new QLabel("Time delta:"),0,1);
	dt=new QDoubleSpinBox();
	dt->setValue(0.1);
	QObject::connect(dt,SIGNAL(valueChanged(double)),eng,SLOT(setDt(double)));
	layout->addWidget(dt,0,2);
	start=new QPushButton("Start");
	QObject::connect(start,SIGNAL(clicked()),eng,SLOT(startPull()));
	QObject::connect(db,SIGNAL(dataLocked(bool)),start,SLOT(setDisabled(bool)));
	layout->addWidget(start,0,3);
	stop=new QPushButton("Stop");
	stop->setEnabled(false);
	QObject::connect(stop,SIGNAL(clicked()),eng,SLOT(stopPull()));
	QObject::connect(db,SIGNAL(dataLocked(bool)),stop,SLOT(setEnabled(bool)));
	layout->addWidget(stop,0,4);
	reset=new QPushButton("Reset");
	layout->addWidget(reset,0,5);
	container->setLayout(layout);
	
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->setWidget(container);
	this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
	QObject::connect(eng,SIGNAL(statusChanged(QString, int)),this,SLOT(statusChanged(QString, int)));
	QObject::connect(db,SIGNAL(statusChanged(QString, int)),this,SLOT(statusChanged(QString, int)));
}

void SimulationControl::statusChanged(QString newString, int errorSource)
{
	status->setText(newString);
	QPalette pal=status->palette();
	switch(errorSource)
	{
		case 0: pal.setColor(QPalette::Window,QColor::fromRgb(128,128,128,128));
			break;
		case 1: pal.setColor(QPalette::Window,QColor::fromRgb(255,128,128,128));
			break;
		case 2: pal.setColor(QPalette::Window,QColor::fromRgb(200,150,128,128));
			break;
		default:pal.setColor(QPalette::Window,QColor::fromRgb(100,100,100,128));
			break;
	};
	status->setPalette(pal);
}

#endif
