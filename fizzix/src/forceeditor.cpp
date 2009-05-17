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
