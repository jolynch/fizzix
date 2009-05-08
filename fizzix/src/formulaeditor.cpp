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
	int i;
	return new FizFormula (Parser::parse(formEdit->toPlainText(),i));
}

void FormulaEditor::changes()
{hChanges=true;}

void FormulaEditor::setData(FizFormula f)
{
//	formEdit->setPlainText("String not available");
	formEdit->setPlainText(QString::fromStdString(f.toString()));
	hChanges=false;
}

void FormulaEditor::showAvailableSymbolsDialog()
{
	return;
}

#endif
