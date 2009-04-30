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
	this->selectTab(0);
	name=new QLineEdit();
	layout->addWidget(name,0,1,1,4);
	QWidget * a =new QWidget();
	a->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	layout->addWidget(new QLabel("Name:"),0,0);
	layout->addWidget(a,1,0,1,5);
	container->setLayout(layout);
	layout->addWidget(new QPushButton("Save"),2,3);
	layout->addWidget(new QPushButton("Clear"),2,4);
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->setWidget(container);
	this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
	QObject::connect(name, SIGNAL(textEdited()), this, SLOT(changeDetected()));
	modified=false;
}

void DataEditor::selectTab(int tab)
{
	switch (tab) {
		case 0:
			this->setWindowTitle("Object Editor");
			break;
		case 1:
			this->setWindowTitle("Property Editor");
			break;
		case 2:
			this->setWindowTitle("Force Editor");
			break;
		case 3:
			this->setWindowTitle("Macro Editor");
			break;
		default:
			break;
	}
}

void DataEditor::newName(QString n)
{
	name->setText(n);
	if(modified)
	{
		emit holdSwitchForUserConfirmation();
		modified=false;
	}
}


void DataEditor::changeDetected()
{
	modified=true;
}
#endif
