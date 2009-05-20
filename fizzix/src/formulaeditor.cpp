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
#ifndef FORMULAEDITOR_CPP
#define FORMULAEDITOR_CPP
#include "formulaeditor.h"

FormulaEditor::FormulaEditor(DataBackend * _db):QWidget()
{
	db=_db;
	hChanges=false;
	QGridLayout * layout=new QGridLayout();
	layout->addWidget(new QLabel("Value ="),0,0);
	formEdit=new QTextEdit();
	formEdit->setAcceptRichText(false);
	QObject::connect(formEdit,SIGNAL(textChanged()),this,SLOT(changes()));
	layout->addWidget(formEdit,1,0,1,3);
	QPushButton * showAvailSym=new QPushButton("Show Available Symbols");
	showAvailSym->setEnabled(false);
	layout->addWidget(showAvailSym,2,2);
	this->setLayout(layout);
}

bool FormulaEditor::hasChanges()
{return hChanges;}

FizFormula * FormulaEditor::getData()
{
	hChanges=false;
	return new FizFormula (db->parse(formEdit->toPlainText()));
}

void FormulaEditor::changes()
{hChanges=true;}

void FormulaEditor::setData(FizFormula f)
{
	formEdit->setPlainText(QString::fromStdString(f.toString()));
	hChanges=false;
}

void FormulaEditor::showAvailableSymbolsDialog()
{
	return;
}

#endif
