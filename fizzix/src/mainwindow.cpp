#ifndef MAINWINDOW_CPP
#define MAINWINDOW_CPP

#include "mainwindow.h"

MainWindow::MainWindow():QWidget()
{
	QLabel * temp=new QLabel ("Hello, world.");
	QGridLayout * layout=new QGridLayout();
	layout->addWidget(temp,0,0);
	this->setLayout(layout);
}

#endif
