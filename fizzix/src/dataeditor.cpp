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

DataEditor::DataEditor(DataBackend * _db,QDesktopWidget * d):QDockWidget(tr("Data editor"))
{
	db=_db;
	QWidget * container=new QWidget();
	QGridLayout * layout=new QGridLayout();
	name=new QLineEdit();
	layout->addWidget(name,0,1,1,4);
	layout->addWidget(new QLabel("Name:"),0,0);
	QPushButton * save_PB=new QPushButton("Save");
	QObject::connect(save_PB,SIGNAL(clicked()),this,SLOT(saveChanges()));
	QPushButton * cancel_PB=new QPushButton("Cancel");
	QObject::connect(cancel_PB,SIGNAL(clicked()),this,SLOT(revertChanges()));
	layout->addWidget(save_PB,2,3);
	layout->addWidget(cancel_PB,2,4);
	
	centerL=new QStackedLayout();
	centerL->insertWidget(none, new QLabel("Nothing selected to edit"));
	centerL->insertWidget(objectLoaded, new QLabel("Object Editor Goes Here"));
	centerL->insertWidget(forceLoaded, new QLabel("Formula Editor Goes Here"));
	centerL->insertWidget(macroLoaded, new QLabel("Formula Editor Goes Here"));
	constEditor=new ConstantEditor();
	centerL->insertWidget(constantLoaded,constEditor);
	layout->addLayout(centerL,1,0,1,5);
	
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	container->setLayout(layout);
	container->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
	this->setWidget(container);
	this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
}

bool DataEditor::checkToSave()
{
	bool needsSave=false;
	switch(curr)
	{
		case constantLoaded: needsSave=constEditor->hasChanges(); break;
	};
	if(needsSave)
	{
		switch(QMessageBox::question(this,"Save Changes?", "You have modified the currently selected element. Save Changes?",
						QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel))
		{
			case QMessageBox::Yes:
				saveChanges();
			case QMessageBox::No:
				return true;
			default:
				return false;
		}
	}
	return true;
}
	
void DataEditor::loadObject(QString n)
{
	if(!checkToSave()) return;
	loadName=n;
	name->setText(n);
	curr=objectLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::loadForce(QString n)
{
	if(!checkToSave()) return;
	loadName=n;
	name->setText(n);
	curr=forceLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::loadMacro(QString n)
{
	if(!checkToSave()) return;
	loadName=n;
	name->setText(n);
	curr=macroLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::loadConstant(QString n)
{
	if(!checkToSave()) return;
	loadName=n;
	name->setText(n);
	constEditor->setData(db->getConstModel()->getData()->value(loadName));
	curr=constantLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::saveChanges()
{
	switch(curr)
	{
		case constantLoaded:
			QString newName=name->text();
			if(name->text()!=loadName)
				db->getDataInserter()->renameConstant(loadName,newName);
			if(constEditor->hasChanges())
				db->getDataInserter()->modifyConstant(newName,constEditor->getData());
			this->loadConstant(newName);
			break;
	};
}

void DataEditor::revertChanges()
{
	switch(curr)
	{
		case constantLoaded: constEditor->setData(db->getConstModel()->getData()->value(loadName)); break;
	};
}

#endif
