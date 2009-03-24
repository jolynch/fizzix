#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"

MainWindow::MainWindow():QWidget()
{
	QGridLayout * layout=new QGridLayout();
	QTabWidget * tabs=new QTabWidget();
	tabs->addTab(new QLabel("Objects"),"Objects");
	tabs->addTab(new QLabel("Properties"),"Properties");
	tabs->addTab(new QLabel("Forces"),"Forces");
	tabs->addTab(new QLabel("Macros"),"Macros");
	layout->addWidget(new QLabel("OpenGL area"),0,0,1,1);
	layout->addWidget(tabs,0,1,2,1);
	layout->addWidget(new QLabel("Button panel"),1,0,1,1);
	this->setLayout(layout);
}

#endif
