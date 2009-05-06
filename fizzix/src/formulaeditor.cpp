#ifndef FORMULAEDITOR_CPP
#define FORMULAEDITOR_CPP
#include "formulaeditor.h"

FormulaEditor::FormulaEditor():QWidget()
{
	hChanges=false;
	QGridLayout * layout=new QGridLayout();
	layout->addWidget(new QLabel("Value ="),0,0);
	formEdit=new QTextEdit();
	formEdit->setAcceptRichText(false);
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
	return &tempData;
}

void FormulaEditor::changes()
{hChanges=true;}

void FormulaEditor::setData(FizFormula f)
{
	tempData=f;
	hChanges=false;
}

void FormulaEditor::showAvailableSymbolsDialog()
{
	return;
}

#endif
