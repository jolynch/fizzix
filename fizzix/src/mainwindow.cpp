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
	
	QDockWidget * panelsDockWidget = new QDockWidget(tr("Data browser"), this);
	panelsDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	QTabWidget * tabs=new QTabWidget();
	tabs->setMinimumWidth((d->availableGeometry().width()/2)/2);
	panelsDockWidget->setWidget(tabs);
	panelsDockWidget->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
	this->addDockWidget(Qt::RightDockWidgetArea, panelsDockWidget);
	
	QDockWidget * buttonDockWidget = new QDockWidget(tr("Simulation control"), this);
	buttonDockWidget->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
	buttonDockWidget->setWidget(new ButtonPanel());
	buttonDockWidget->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
	this->addDockWidget(Qt::BottomDockWidgetArea, buttonDockWidget);
	
	tabs->addTab(new ObjectPanel(),tr("Objects"));
	tabs->addTab(new PropertyPanel(),tr("Properties"));
	tabs->addTab(new ForcePanel(),tr("Forces"));
	tabs->addTab(new MacroPanel(),tr("Macros"));
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
	this->setMinimumSize(d->availableGeometry().width()/1.25, d->availableGeometry().height()/1.25);
}

#endif
