#ifndef FORMULAEDITOR_CPP
#define FORMULAEDITOR_CPP
#include "formulaeditor.h"

FormulaEditor::FormulaEditor():QWidget()
{
	hChanges=false;
}

bool FormulaEditor::hasChanges()
{return hChanges;}

FizFormula * FormulaEditor::getData()
{
	return tempData;
}

void FormulaEditor::changes()
{hChanges=true;}

void FormulaEditor::setData(FizFormula * f)
{
	tempData=f;
	hChanges=false;
}

#endif
