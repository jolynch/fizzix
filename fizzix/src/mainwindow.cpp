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

#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"

MainWindow::MainWindow(QDesktopWidget * d):QMainWindow()
{
	this->setDockNestingEnabled(false);
	this->setDockOptions(NULL);
	this->setCentralWidget(new QLabel ("OpenGL"));
	this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
	
	databrowser=new DataBrowser(d);
	dataeditor=new DataEditor(d);
	simcontrol=new SimulationControl();
	QObject::connect(databrowser,SIGNAL(tabSelected(int)),dataeditor,SLOT(selectTab(int)));
	QObject::connect(databrowser,SIGNAL(newDataSelected(QString)),dataeditor,SLOT(newName(QString)));

	this->addDockWidget(Qt::RightDockWidgetArea, databrowser);
	this->addDockWidget(Qt::RightDockWidgetArea, dataeditor);
	this->addDockWidget(Qt::BottomDockWidgetArea, simcontrol);
	
	QMenu * fileMenu = this->menuBar()->addMenu(tr("File"));
	fileMenu->addAction("New Project");
	fileMenu->addAction("Open Project");
	fileMenu->addAction("Save Project");
	QMenu * exportMenu=fileMenu->addMenu("Export");
	exportMenu->addAction("Project as XML");
	exportMenu->addAction("Object");
	exportMenu->addAction("Force");
	exportMenu->addAction("Macro");
	exportMenu->addAction("Screenshot");
	QMenu * importMenu=fileMenu->addMenu("Import");
	importMenu->addAction("Project from XML");
	importMenu->addAction("Object");
	importMenu->addAction("Force");
	importMenu->addAction("Macro");
	fileMenu->addAction("Exit");
	QMenu * editMenu = this->menuBar()->addMenu(tr("Edit"));
	editMenu->addAction("Undo");
	editMenu->addAction("Redo");
	editMenu->addAction("Cut");
	editMenu->addAction("Copy");
	editMenu->addAction("Paste");
	editMenu->addAction("Find");
	QMenu * viewMenu = this->menuBar()->addMenu(tr("View"));
	QMenu * cameraMenu=viewMenu->addMenu("Camera Presets");
	cameraMenu->addAction("Isometric");
	cameraMenu->addAction("View XY Plane");
	cameraMenu->addAction("View XZ Plane");
	cameraMenu->addAction("View YZ Plane");
	QMenu * zoomMenu=viewMenu->addMenu("Zoom");
	QActionGroup * zoomGroup=new QActionGroup(NULL);
	zoomGroup->addAction(zoomMenu->addAction("To Scale"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("25%"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("50%"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("75&"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("100%"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("125%"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("150&"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("175&"))->setCheckable(true);
	viewMenu->addAction("Focus at Center");
	QAction * coordAxes = viewMenu->addAction("Show Coordinate Axes");
	coordAxes->setCheckable(true);
	QMenu * simulationMenu = this->menuBar()->addMenu(tr("Simulation"));
	simulationMenu->addAction("Start");
	simulationMenu->addAction("Reset to Initial Conditions");
	simulationMenu->addAction("Set Current Conditions as Initial");
	simulationMenu->addAction("Change Timestep");
	simulationMenu->addAction("Change Data Buffer Size");
	QMenu * dataMenu = this->menuBar()->addMenu(tr("Data"));
	QMenu * newDataMenu = dataMenu->addMenu("New");
	newDataMenu->addAction("Object");
	newDataMenu->addAction("Force");
	newDataMenu->addAction("Property");
	newDataMenu->addAction("Macro");
	QMenu * editDataMenu = dataMenu->addMenu("Edit");
	editDataMenu->addAction("Object");
	editDataMenu->addAction("Force");
	editDataMenu->addAction("Property");
	editDataMenu->addAction("Macro");
	QMenu * deleteDataMenu = dataMenu->addMenu("Delete");
	deleteDataMenu->addAction("Object");
	deleteDataMenu->addAction("Force");
	deleteDataMenu->addAction("Property");
	deleteDataMenu->addAction("Macro");
	QMenu * clearDataMenu = dataMenu->addMenu("Clear");
	clearDataMenu->addAction("All Objects");
	clearDataMenu->addAction("All Forces");
	clearDataMenu->addAction("All Properties");
	clearDataMenu->addAction("All Macros and Forces");
	QMenu * helpMenu = this->menuBar()->addMenu(tr("Help"));
	helpMenu->addAction("Manual");
	helpMenu->addAction("About");
	this->setMinimumSize(d->availableGeometry().width()/1.15, d->availableGeometry().height()/1.25);
}

#endif
