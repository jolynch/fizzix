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
	newMenu->addAction("Blank Project",databackend,SLOT(newFromBlank()),QKeySequence("Ctrl+N"));
	newMenu->addAction("From Default",databackend,SLOT(newFromDefault()),QKeySequence("Ctrl+Shift+N"));
	fileMenu->addAction("Open Project",databackend,SLOT(load()),QKeySequence("Ctrl+O"));
	fileMenu->addAction("Save Project",databackend,SLOT(save()),QKeySequence("Ctrl+S"));
	fileMenu->addAction("Save Project As",databackend,SLOT(saveAs()),QKeySequence("Ctrl+Shift+S"));
	fileMenu->addAction("Exit",databackend, SLOT(quit()));
	QMenu * editMenu = this->menuBar()->addMenu(tr("Edit"));
	QAction * undo=databackend->getUndoStack()->createUndoAction(this);
	undo->setShortcut(QKeySequence(QKeySequence::Undo));
	editMenu->addAction(undo);
	QAction * redo=databackend->getUndoStack()->createRedoAction(this);
	redo->setShortcut(QKeySequence(QKeySequence::Redo));
	editMenu->addAction(redo);
	QMenu * viewMenu = this->menuBar()->addMenu(tr("View"));
	QMenu * cameraMenu=viewMenu->addMenu("Camera Presets");
	cameraMenu->addAction("Isometric",this,SLOT(view_setIsometric()));
	cameraMenu->addAction("View XY Plane",this,SLOT(view_setXY()));
	cameraMenu->addAction("View XZ Plane",this,SLOT(view_setXZ()));
	cameraMenu->addAction("View YZ Plane",this,SLOT(view_setYZ()));
	QMenu * zoomMenu=viewMenu->addMenu("Zoom");
	QActionGroup * zoomGroup=new QActionGroup(NULL);
	zoomGroup->addAction(zoomMenu->addAction("10%",this,SLOT(view_zoom10())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("50%",this,SLOT(view_zoom50())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("100%",this,SLOT(view_zoom100())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("150%",this,SLOT(view_zoom150())))->setCheckable(true);
	zoomGroup->addAction(zoomMenu->addAction("200%",this,SLOT(view_zoom200())))->setCheckable(true);
	view_zoom50();
	viewMenu->addSeparator();
	viewMenu->addAction(databrowser->toggleViewAction());
	viewMenu->addAction(dataeditor->toggleViewAction());
	viewMenu->addAction(simcontrol->toggleViewAction());
	QMenu * simulationMenu = this->menuBar()->addMenu(tr("Simulation"));
	simulationMenu->addAction("Run",simcontrol->getStepEngine(),SLOT(startPull()),QKeySequence("Ctrl+R"));
	simulationMenu->addAction("Pause",simcontrol->getStepEngine(),SLOT(stopPull()),QKeySequence("Ctrl+P"));
	simulationMenu->addAction("Reset to Initial Conditions",databackend->getUndoStack(),SLOT(undo()),QKeySequence("Ctrl+Shift+R"));
	QAction * a=simulationMenu->addAction("Warn Before Clearing Undo Stack");
	a->setCheckable(true);
	a->setChecked(true);
	QObject::connect(a,SIGNAL(toggled(bool)),databackend,SLOT(setWarning(bool)));
	QMenu * dataMenu = this->menuBar()->addMenu(tr("Data"));
	dataMenu->addAction("Clear All Objects",databackend->getDataInserter(),SLOT(clearObjects()));
	dataMenu->addAction("Clear All Forces",databackend->getDataInserter(),SLOT(clearForces()));
	dataMenu->addAction("Clear All Macros",databackend->getDataInserter(),SLOT(clearMacros()));
	dataMenu->addAction("Clear All Constants",databackend->getDataInserter(),SLOT(clearConstants()));
	QMenu * helpMenu = this->menuBar()->addMenu(tr("Help"));
	helpMenu->addAction("Manual",this,SLOT(showManual()));
	helpMenu->addAction("About",this,SLOT(showAbout()));
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

void MainWindow::showManual()
{
	QTextBrowser * tb=new QTextBrowser(NULL);
	tb->setSource(QUrl(":data/man/manual.html"));
	tb->setMinimumSize(650,550);
	tb->setWindowTitle("fizzix Manual");
	tb->show();
}

void MainWindow::showAbout()
{
	QWidget * about=new QWidget(NULL);
	about->setVisible(false);
	about->setWindowTitle("About fizzix");
	QGridLayout * layout=new QGridLayout();
	QLabel * image=new QLabel();
	image->setPixmap(QPixmap::fromImage(QImage(":images/logo.png")));
	image->setAlignment(Qt::AlignCenter);
	layout->addWidget(image, 0,0);
	QLabel * text=new QLabel();
	text->setText("A physics simulation engine of variable accuracy. \nVersion 0.1\n (C) 2009 \n Joseph Lynch, Anton Frolenkov, Purnima Balakrishnan, Daniel Stiles, Eric Van Albert ");
	text->setAlignment(Qt::AlignCenter);
	layout->addWidget(text, 1,0);
	QTextEdit * tb=new QTextEdit(NULL);
	tb->setTextInteractionFlags(Qt::TextBrowserInteraction);
	QFile f(":gpl.txt");
	f.open(QIODevice::ReadOnly);
	tb->setPlainText(QString(f.readAll()));
	f.close();
	layout->addWidget(tb, 2,0);
	about->setLayout(layout);
	about->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if(databackend->checkBeforeDataUnload())
		event->accept();
	else
		event->ignore();
}


void MainWindow::checkResetAction()
{
	if(databackend->haveUnpredicatableChanges())
		databackend->getUndoStack()->undo();
}

#endif
