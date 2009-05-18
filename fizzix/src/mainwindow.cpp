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
	this->setMinimumSize(d->availableGeometry().width()/1.15, d->availableGeometry().height()/1.25);
	this->setDockNestingEnabled(false);
	this->setDockOptions(NULL);
	this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	this->setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
	
	databackend=new DataBackend();
	databackend->setDataInserter(new ChangeFactory(databackend));
	databrowser=new DataBrowser(databackend,d);
	dataeditor=new DataEditor(databackend,d);
	
	QObject::connect(databrowser,SIGNAL(editObject(QString)),dataeditor,SLOT(loadObject(QString)));
	QObject::connect(databrowser,SIGNAL(editForce(QString)),dataeditor,SLOT(loadForce(QString)));
	QObject::connect(databrowser,SIGNAL(editMacro(QString)),dataeditor,SLOT(loadMacro(QString)));
	QObject::connect(databrowser,SIGNAL(editConstant(QString)),dataeditor,SLOT(loadConstant(QString)));
	QObject::connect(databrowser,SIGNAL(deleteObject(QString)),dataeditor,SLOT(loadBlank()));
	QObject::connect(databrowser,SIGNAL(deleteForce(QString)),dataeditor,SLOT(loadBlank()));
	QObject::connect(databrowser,SIGNAL(deleteMacro(QString)),dataeditor,SLOT(loadBlank()));
	QObject::connect(databrowser,SIGNAL(deleteConstant(QString)),dataeditor,SLOT(loadBlank()));
	
	simcontrol=new SimulationControl(databackend);
	openglpane=new GLDrawPane(databackend,d);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), openglpane, SLOT(updateGL()));
	connect(qApp, SIGNAL(lastWindowClosed()),timer,SLOT(stop()));
	timer -> start(15);

	this->setCentralWidget(openglpane);

	this->addDockWidget(Qt::RightDockWidgetArea, databrowser);
	this->addDockWidget(Qt::RightDockWidgetArea, dataeditor);
	this->addDockWidget(Qt::BottomDockWidgetArea, simcontrol);
	
	QMenu * fileMenu = this->menuBar()->addMenu(tr("File"));
	QMenu * newMenu=fileMenu->addMenu("New Project");
	newMenu->addAction("Blank Project",databackend,SLOT(newFromBlank()));
	newMenu->addAction("From Default",databackend,SLOT(newFromDefault()));
	fileMenu->addAction("Open Project",databackend,SLOT(load()));
	fileMenu->addAction("Save Project",databackend,SLOT(save()));
	fileMenu->addAction("Save Project As",databackend,SLOT(saveAs()));
	QMenu * exportMenu=fileMenu->addMenu("Export");
	exportMenu->addAction("Object");
	exportMenu->addAction("Force");
	exportMenu->addAction("Macro");
	exportMenu->addAction("Constant");
	QMenu * importMenu=fileMenu->addMenu("Import");
	importMenu->addAction("Object");
	importMenu->addAction("Force");
	importMenu->addAction("Macro");
	exportMenu->addAction("Constant");
	fileMenu->addAction("Exit",qApp, SLOT(closeAllWindows()));
	QMenu * editMenu = this->menuBar()->addMenu(tr("Edit"));
	QAction * undo=databackend->getUndoStack()->createUndoAction(this);
	undo->setShortcut(QKeySequence(QKeySequence::Undo));
	editMenu->addAction(undo);
	QAction * redo=databackend->getUndoStack()->createRedoAction(this);
	redo->setShortcut(QKeySequence(QKeySequence::Redo));
	editMenu->addAction(redo);
//	editMenu->addAction("Cut");
//	editMenu->addAction("Copy");
//	editMenu->addAction("Paste");
//	editMenu->addAction("Find");
	QMenu * viewMenu = this->menuBar()->addMenu(tr("View"));
	QMenu * cameraMenu=viewMenu->addMenu("Camera Presets");
	cameraMenu->addAction("Isometric",this,SLOT(view_setIsometric()));
	cameraMenu->addAction("View XY Plane",this,SLOT(view_setXY()));
	cameraMenu->addAction("View XZ Plane",this,SLOT(view_setXZ()));
	cameraMenu->addAction("View YZ Plane",this,SLOT(view_setYZ()));
	QMenu * zoomMenu=viewMenu->addMenu("Zoom");
	QActionGroup * zoomGroup=new QActionGroup(NULL);
	//zoomGroup->addAction(zoomMenu->addAction("To Scale"))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("10%",this,SLOT(view_zoom10())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("50%",this,SLOT(view_zoom50())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("100%",this,SLOT(view_zoom100())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("150%",this,SLOT(view_zoom150())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("200%",this,SLOT(view_zoom200())))->setCheckable(true);
	//QAction * coordAxes = viewMenu->addAction("Show Coordinate Axes");
	//coordAxes->setCheckable(true);
	//coordAxes->setEnabled(false);
	viewMenu->addSeparator();
	viewMenu->addAction(databrowser->toggleViewAction());
	viewMenu->addAction(dataeditor->toggleViewAction());
	viewMenu->addAction(simcontrol->toggleViewAction());
	QMenu * simulationMenu = this->menuBar()->addMenu(tr("Simulation"));
	simulationMenu->addAction("Start");
	simulationMenu->addAction("Reset to Initial Conditions");
	simulationMenu->addAction("Change Timestep");
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
}


void MainWindow::view_setIsometric()
{openglpane->setRotation(ISOMETRIC);}

void MainWindow::view_setXY()
{openglpane->setRotation(XY);}

void MainWindow::view_setXZ()
{openglpane->setRotation(ZX);}

void MainWindow::view_setYZ()
{openglpane->setRotation(YZ);}

void MainWindow::view_zoom10()
{openglpane->setZoomPercent(10);}

void MainWindow::view_zoom50()
{openglpane->setZoomPercent(50);}

void MainWindow::view_zoom100()
{openglpane->setZoomPercent(100);}

void MainWindow::view_zoom150()
{openglpane->setZoomPercent(150);}

void MainWindow::view_zoom200()
{openglpane->setZoomPercent(200);}


#endif
