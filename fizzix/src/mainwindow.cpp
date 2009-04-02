#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"

MainWindow::MainWindow():QWidget()
{
	QGridLayout * layout=new QGridLayout();
	QTabWidget * tabs=new QTabWidget();
	tabs->addTab(new ObjectPanel(),"Objects");
	tabs->addTab(new PropertyPanel(),"Properties");
	tabs->addTab(new ForcePanel(),"Forces");
	tabs->addTab(new MacroPanel(),"Macros");
	layout->addWidget(new QLabel("OpenGL area"),0,0,1,1);
	layout->addWidget(tabs,0,1,2,1);
	layout->addWidget(new ButtonPanel(),1,0,1,1);
	this->setLayout(layout);
}

#endif
