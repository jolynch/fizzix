#ifndef FORCEEDITOR_CPP
#define FORCEEDITOR_CPP
#include "forceeditor.h"

ForceEditor::ForceEditor():QWidget()
{
	hChanges=false;
}

bool ForceEditor::hasChanges()
{return hChanges;}

FizForce * ForceEditor::getData()
{
	return tempData;
}

void ForceEditor::changes()
{hChanges=true;}

void ForceEditor::setData(FizForce * f)
{
	tempData=f;
	hChanges=false;
}

#endif
