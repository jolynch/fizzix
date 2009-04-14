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


#ifndef DATAEDITOR_CPP
#define DATAEDITOR_CPP

#include "dataeditor.h"

DataEditor::DataEditor(QDesktopWidget * d):QDockWidget(tr("Data editor"))
{
	layout=new QGridLayout();
	QWidget * container=new QWidget();
	QLabel * tabLabel=new QLabel("Editing:");
	currentTab=new QLabel();
	this->selectTab(0);
	layout->addWidget(tabLabel,0,0);
	layout->addWidget(currentTab,0,1);
	name=new QLineEdit();
	layout->addWidget(name,1,1,1,4);
	QWidget * a =new QWidget();
	a->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	layout->addWidget(new QLabel("Name:"),1,0);
	layout->addWidget(a,2,0,1,5);
	container->setLayout(layout);
	layout->addWidget(new QPushButton("Save"),3,3);
	layout->addWidget(new QPushButton("Clear"),3,4);
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->setWidget(container);
	this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}

void DataEditor::selectTab(int tab)
{
	switch (tab) {
		case 0:
			currentTab->setText("Object");
			break;
		case 1:
			currentTab->setText("Property");
			break;
		case 2:
			currentTab->setText("Force");
			break;
		case 3:
			currentTab->setText("Macro");
			break;
		default:
			break;
	}
}

void DataEditor::newName(QString n)
{
	name->setText(n);
}

#endif
