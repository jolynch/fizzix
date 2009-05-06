#ifndef FORCEEDITOR_CPP
#define FORCEEDITOR_CPP
#include "forceeditor.h"

ForceEditor::ForceEditor():QWidget()
{
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
	formEdit=new FormulaEditor();
	layout->addWidget(formEdit,3,0,1,2);
	this->setLayout(layout);
	hChanges=false;
}

bool ForceEditor::hasChanges()
{return hChanges;}

FizForce * ForceEditor::getData()
{
	return new FizForce(*(formEdit->getData()));
	hChanges=false;
}

void ForceEditor::changes()
{hChanges=true;}

void ForceEditor::setData(FizForce f)
{
	formEdit->setData(f.getFormula());
	hChanges=false;
}

#endif
