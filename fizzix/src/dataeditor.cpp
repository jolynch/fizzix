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
	QObject::connect(name,SIGNAL(returnPressed()),this,SLOT(saveChanges()));
	layout->addWidget(name,0,1,1,4);
	layout->addWidget(new QLabel("Name:"),0,0);
	QPushButton * save_PB=new QPushButton("Save");
	QObject::connect(save_PB,SIGNAL(clicked()),this,SLOT(saveChanges()));
	QPushButton * cancel_PB=new QPushButton("Cancel");
	QObject::connect(cancel_PB,SIGNAL(clicked()),this,SLOT(revertChanges()));
	layout->addWidget(save_PB,2,3);
	layout->addWidget(cancel_PB,2,4);
	
	centerL=new QStackedLayout();
	QLabel * blankLabel=new QLabel("Nothing selected to edit");
	blankLabel->setAlignment(Qt::AlignCenter);
	centerL->insertWidget(none, blankLabel);
	objectEditor=new ObjectEditor();
	centerL->insertWidget(objectLoaded, objectEditor);
	forceEditor=new ForceEditor();
	centerL->insertWidget(forceLoaded, forceEditor);
	macroEditor=new FormulaEditor();
	centerL->insertWidget(macroLoaded,macroEditor);
	constEditor=new ConstantEditor();
	QObject::connect(constEditor,SIGNAL(saveChanges()),this,SLOT(saveChanges()));
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
		case objectLoaded: needsSave=objectEditor->hasChanges(); break;
		case forceLoaded: needsSave=forceEditor->hasChanges(); break;
		case macroLoaded: needsSave=macroEditor->hasChanges(); break;
		case constantLoaded: needsSave=constEditor->hasChanges(); break;
		default: break;
	};
	if(needsSave)
	{
		switch(QMessageBox::question(this,"Save Changes?", "You have modified the currently selected element. Save Changes?",
						QMessageBox::Cancel|QMessageBox::Yes|QMessageBox::No))
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
	this->setWindowTitle("Object editor");
	loadName=n;
	name->setText(loadName);
	if(db->getObjectModel()->getData()->value(loadName)==NULL)
		objectEditor->setData(DrawableObject());
	else
		objectEditor->setData(*(db->getObjectModel()->getData()->value(loadName)));
	curr=objectLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::loadForce(QString n)
{
	if(!checkToSave()) return;
	this->setWindowTitle("Force editor");
	loadName=n;
	name->setText(loadName);
	if(db->getForceModel()->getData()->value(loadName)==NULL)
		forceEditor->setData(FizForce(FizFormula()));
	else
		forceEditor->setData(*(db->getForceModel()->getData()->value(loadName)));
	curr=forceLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::loadMacro(QString n)
{
	if(!checkToSave()) return;
	this->setWindowTitle("Macro editor");
	loadName=n;
	name->setText(loadName);
	if(db->getMacroModel()->getData()->value(loadName)==NULL)
		macroEditor->setData(FizFormula());
	else
		macroEditor->setData(*(db->getMacroModel()->getData()->value(loadName)));
	curr=macroLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::loadConstant(QString n)
{
	if(!checkToSave()) return;
	this->setWindowTitle("Constant editor");
	loadName=n;
	name->setText(loadName);
	constEditor->setData(db->getConstModel()->getData()->value(loadName));
	curr=constantLoaded;
	centerL->setCurrentIndex(curr);
}

void DataEditor::saveChanges()
{
	QString newName=name->text();
	switch(curr)
	{
		case objectLoaded:
			if(name->text()!=loadName)
				db->getDataInserter()->renameObject(loadName,newName);
			if(objectEditor->hasChanges())
				db->getDataInserter()->modifyObject(newName,objectEditor->getData());
			this->loadObject(newName);
			break;
		case forceLoaded:
			if(name->text()!=loadName)
				db->getDataInserter()->renameForce(loadName,newName);
			if(forceEditor->hasChanges())
				db->getDataInserter()->modifyForce(newName,forceEditor->getData());
			this->loadForce(newName);
			break;
		case macroLoaded:
			if(name->text()!=loadName)
				db->getDataInserter()->renameMacro(loadName,newName);
			if(macroEditor->hasChanges())
				db->getDataInserter()->modifyMacro(newName,macroEditor->getData());
			this->loadMacro(newName);
			break;
		case constantLoaded:
			if(name->text()!=loadName)
				db->getDataInserter()->renameConstant(loadName,newName);
			if(constEditor->hasChanges())
				db->getDataInserter()->modifyConstant(newName,constEditor->getData());
			this->loadConstant(newName);
			break;
		default: break;
	};
}

void DataEditor::revertChanges()
{
	switch(curr)
	{
		case objectLoaded:  break;
		case forceLoaded: break;
		case macroLoaded: break;
		case constantLoaded: constEditor->setData(db->getConstModel()->getData()->value(loadName)); break;
		default: break;
	};
}

#endif
