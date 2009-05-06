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


#ifndef DATABROWSER_CPP
#define DATABROWSER_CPP

#include "databrowser.h"

DataBrowser::DataBrowser( DataBackend * _d,QDesktopWidget * d):QDockWidget(tr("Data browser"))
{
	db=_d;
	this->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
	this->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable);
	tabs=new QTabWidget();
	
	QWidget * owidget=new QWidget();
	QGridLayout * olayout=new QGridLayout();
	olayout->addWidget(new QLabel("Find:"),0,0);
	QLineEdit * osearch=new QLineEdit();
	QObject::connect(osearch,SIGNAL(textEdited(QString)),this,SLOT(textEntered(QString)));
	QObject::connect(osearch,SIGNAL(returnPressed()),this,SLOT(editElement()));
	olayout->addWidget(osearch,0,1,1,4);
	objects=new QListView();
	objects->setModel(db->getObjectModel()->getModel());
	objects->setSelectionMode(QAbstractItemView::SingleSelection);
	objects->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QObject::connect(objects,SIGNAL(clicked(QModelIndex)),this,SLOT(editElement()));
	QObject::connect(objects,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editElement()));
	olayout->addWidget(objects,1,0,1,5);
	QPushButton * oadd=new QPushButton("New");
	QObject::connect(oadd,SIGNAL(pressed()),this,SLOT(addElement()));
	olayout->addWidget(oadd,2,2);
	QPushButton * odel=new QPushButton("Delete");
	QObject::connect(odel,SIGNAL(pressed()),this,SLOT(deleteElement()));
	olayout->addWidget(odel,2,3);
	QPushButton * oed=new QPushButton("Edit");
	QObject::connect(oed,SIGNAL(pressed()),this,SLOT(editElement()));
	olayout->addWidget(oed,2,4);
	owidget->setLayout(olayout);
	tabs->addTab(owidget,"Objects");
	
	QWidget * fwidget=new QWidget();
	QGridLayout * flayout=new QGridLayout();
	flayout->addWidget(new QLabel("Find:"),0,0);
	QLineEdit * fsearch=new QLineEdit();
	QObject::connect(fsearch,SIGNAL(textEdited(QString)),this,SLOT(textEntered(QString)));
	QObject::connect(fsearch,SIGNAL(returnPressed()),this,SLOT(editElement()));
	flayout->addWidget(fsearch,0,1,1,4);
	forces=new QListView();
	forces->setModel(db->getForceModel()->getModel());
	forces->setSelectionMode(QAbstractItemView::SingleSelection);
	forces->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QObject::connect(forces,SIGNAL(clicked(QModelIndex)),this,SLOT(editElement()));
	QObject::connect(forces,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editElement()));
	flayout->addWidget(forces,1,0,1,5);
	QPushButton * fadd=new QPushButton("New");
	QObject::connect(fadd,SIGNAL(pressed()),this,SLOT(addElement()));
	flayout->addWidget(fadd,2,2);
	QPushButton * fdel=new QPushButton("Delete");
	QObject::connect(fdel,SIGNAL(pressed()),this,SLOT(deleteElement()));
	flayout->addWidget(fdel,2,3);
	QPushButton * fed=new QPushButton("Edit");
	QObject::connect(fed,SIGNAL(pressed()),this,SLOT(editElement()));
	flayout->addWidget(fed,2,4);
	fwidget->setLayout(flayout);
	tabs->addTab(fwidget,"Forces");
	
	QWidget * mwidget=new QWidget();
	QGridLayout * mlayout=new QGridLayout();
	mlayout->addWidget(new QLabel("Find:"),0,0);
	QLineEdit * msearch=new QLineEdit();
	QObject::connect(msearch,SIGNAL(textEdited(QString)),this,SLOT(textEntered(QString)));
	QObject::connect(msearch,SIGNAL(returnPressed()),this,SLOT(editElement()));
	mlayout->addWidget(msearch,0,1,1,4);
	macros=new QListView();
	macros->setModel(db->getMacroModel()->getModel());
	macros->setSelectionMode(QAbstractItemView::SingleSelection);
	macros->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QObject::connect(macros,SIGNAL(clicked(QModelIndex)),this,SLOT(editElement()));
	QObject::connect(macros,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editElement()));
	mlayout->addWidget(macros,1,0,1,5);
	QPushButton * madd=new QPushButton("New");
	QObject::connect(madd,SIGNAL(pressed()),this,SLOT(addElement()));
	mlayout->addWidget(madd,2,2);
	QPushButton * mdel=new QPushButton("Delete");
	QObject::connect(mdel,SIGNAL(pressed()),this,SLOT(deleteElement()));
	mlayout->addWidget(mdel,2,3);
	QPushButton * med=new QPushButton("Edit");
	QObject::connect(med,SIGNAL(pressed()),this,SLOT(editElement()));
	mlayout->addWidget(med,2,4);
	mwidget->setLayout(mlayout);
	tabs->addTab(mwidget,"Macros");
	
	QWidget * cwidget=new QWidget();
	QGridLayout * clayout=new QGridLayout();
	clayout->addWidget(new QLabel("Find:"),0,0);
	QLineEdit * csearch=new QLineEdit();
	QObject::connect(csearch,SIGNAL(textEdited(QString)),this,SLOT(textEntered(QString)));
	QObject::connect(csearch,SIGNAL(returnPressed()),this,SLOT(editElement()));
	clayout->addWidget(csearch,0,1,1,4);
	consts=new QListView();
	consts->setModel(db->getConstModel()->getModel());
	consts->setSelectionMode(QAbstractItemView::SingleSelection);
	consts->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QObject::connect(consts,SIGNAL(clicked(QModelIndex)),this,SLOT(editElement()));
	QObject::connect(consts,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editElement()));
	clayout->addWidget(consts,1,0,1,5);
	QPushButton * cadd=new QPushButton("New");
	QObject::connect(cadd,SIGNAL(pressed()),this,SLOT(addElement()));
	clayout->addWidget(cadd,2,2);
	QPushButton * cdel=new QPushButton("Delete");
	QObject::connect(cdel,SIGNAL(pressed()),this,SLOT(deleteElement()));
	clayout->addWidget(cdel,2,3);
	QPushButton * ced=new QPushButton("Edit");
	QObject::connect(ced,SIGNAL(pressed()),this,SLOT(editElement()));
	clayout->addWidget(ced,2,4);
	cwidget->setLayout(clayout);
	tabs->addTab(cwidget,"Constants");
	
	QObject::connect(this,SIGNAL(addObject(QString)),db->getDataInserter(),SLOT(addObject(QString)));
	QObject::connect(this,SIGNAL(deleteObject(QString)),db->getDataInserter(),SLOT(deleteObject(QString)));
	
	QObject::connect(this,SIGNAL(addForce(QString)),db->getDataInserter(),SLOT(addForce(QString)));
	QObject::connect(this,SIGNAL(deleteForce(QString)),db->getDataInserter(),SLOT(deleteForce(QString)));
	
	QObject::connect(this,SIGNAL(addMacro(QString)),db->getDataInserter(),SLOT(addMacro(QString)));
	QObject::connect(this,SIGNAL(deleteMacro(QString)),db->getDataInserter(),SLOT(deleteMacro(QString)));
	
	QObject::connect(this,SIGNAL(addConstant(QString)),db->getDataInserter(),SLOT(addConstant(QString)));
	QObject::connect(this,SIGNAL(deleteConstant(QString)),db->getDataInserter(),SLOT(deleteConstant(QString)));

	this->setWidget(tabs);
}

void DataBrowser::textEntered(QString s)
{
	if(s.isEmpty()) {return;}
	switch(tabs->currentIndex())
	{
		case 0: objects->keyboardSearch(s); break;
		case 1: forces->keyboardSearch(s); break;
		case 2: macros->keyboardSearch(s); break;
		case 3: consts->keyboardSearch(s); break;
	};
}
	
void DataBrowser::addElement()
{
	bool ok;
	QString name = QInputDialog::getText(this, "New Element","Enter name for new element", QLineEdit::Normal,QString(), &ok);
	if (!ok || name.isEmpty())
		{return;}
	switch(tabs->currentIndex())
	{
		case 0: emit addObject(name);
			break;
		case 1: emit addForce(name);
			break;
		case 2: emit addMacro(name);
			break;
		case 3: emit addConstant(name);
			break;
	};
}
	
void DataBrowser::deleteElement()
{
	switch(tabs->currentIndex())
	{
		case 0: emit deleteObject(db->getObjectModel()->getModel()->data(objects->currentIndex(), Qt::DisplayRole).toString());
			break;
		case 1: emit deleteForce(db->getForceModel()->getModel()->data(forces->currentIndex(), Qt::DisplayRole).toString());
			break;
		case 2: emit deleteMacro(db->getMacroModel()->getModel()->data(macros->currentIndex(), Qt::DisplayRole).toString());
			break;
		case 3: emit deleteConstant(db->getConstModel()->getModel()->data(consts->currentIndex(), Qt::DisplayRole).toString());
			break;
	};
}
	
void DataBrowser::editElement()
{
	switch(tabs->currentIndex())
	{
		case 0: emit editObject(db->getObjectModel()->getModel()->data(objects->currentIndex(), Qt::DisplayRole).toString());
			break;
		case 1: emit editForce(db->getForceModel()->getModel()->data(forces->currentIndex(), Qt::DisplayRole).toString());
			break;
		case 2: emit editMacro(db->getMacroModel()->getModel()->data(macros->currentIndex(), Qt::DisplayRole).toString());
			break;
		case 3: emit editConstant(db->getConstModel()->getModel()->data(consts->currentIndex(), Qt::DisplayRole).toString());
			break;
	};
}


#endif
