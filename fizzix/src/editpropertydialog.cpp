/************************************************************************************************
This file is a part of libfizzix backend to the Fizzix project.
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
#ifndef EDITPROPERTYDIALOG_CPP
#define EDITPROPERTYDIALOG_CPP
#include "editpropertydialog.h"

EditPropertyDialog::EditPropertyDialog(QString _name, fizdatum obj):QDialog()
{
	hChanges=false;
	loadName=_name;
	bool systemProperty=loadName.startsWith("SYSTEM_");
	QGridLayout * layout=new QGridLayout();
	if(!systemProperty)
	{
	   QLabel * nameL=new QLabel("Name:");
	   name=new QLineEdit(loadName);
	   QObject::connect(name,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	   layout->addWidget(nameL,0,0);
	   layout->addWidget(name,0,1,1,3);
	   constEditor=new ConstantEditor();
	   constEditor->setData(obj);
	   layout->addWidget(constEditor,1,0,1,4);
	}
	else
	{
	   bool scalar=obj.type==SCALAR;
	   constEditor=new ConstantEditor(scalar,!scalar);
	   constEditor->setData(obj);
	   layout->addWidget(constEditor,1,0,1,4);
	}
	QPushButton * okay=new QPushButton("OK");
	QObject::connect(okay,SIGNAL(clicked()),this,SLOT(accept()));
	QPushButton * cancel=new QPushButton("Cancel");
	QObject::connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
	layout->addWidget(okay, 2, 2);
	layout->addWidget(cancel, 2, 3);
	this->setLayout(layout);
}

bool EditPropertyDialog::hasChanges()
{return hChanges||constEditor->hasChanges();}

fizdatum EditPropertyDialog::getData()
{return constEditor->getData();}

void EditPropertyDialog::changes()
{hChanges=true;}

QString EditPropertyDialog::saveName()
{
	if(hChanges)
		return name->text();
	else
		return loadName;
}
#endif
