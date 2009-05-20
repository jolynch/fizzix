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
#ifndef FORCEEDITOR_CPP
#define FORCEEDITOR_CPP
#include "forceeditor.h"

ForceEditor::ForceEditor(DataBackend * _db):QWidget()
{
	db=_db;
	QGridLayout * layout=new QGridLayout();
	layout->addWidget(new QLabel("Force evaluated acting"),0,0,1,2);
	layout->addWidget(new QLabel("$FROM = "),1,0);
	layout->addWidget(new QLabel("@ON = "),2,0);
	fromField=new QLineEdit("All Objects");
	fromField->setEnabled(false);
	layout->addWidget(fromField,1,1);
	onField=new QLineEdit("All Objects");
	onField->setEnabled(false);
	layout->addWidget(onField,2,1);
	formEdit=new FormulaEditor(db);
	layout->addWidget(formEdit,3,0,1,2);
	this->setLayout(layout);
	hChanges=false;
}

bool ForceEditor::hasChanges()
{return hChanges||formEdit->hasChanges();}

FizForce * ForceEditor::getData()
{
	hChanges=false;
	return new FizForce(*(formEdit->getData()));
}

void ForceEditor::changes()
{hChanges=true;}

void ForceEditor::setData(FizForce f)
{
	formEdit->setData(f.getFormula());
	hChanges=false;
}

#endif
