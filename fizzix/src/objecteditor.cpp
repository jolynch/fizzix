#ifndef OBJECTEDITOR_CPP
#define OBJECTEDITOR_CPP
#include "objecteditor.h"

ObjectEditor::ObjectEditor():QWidget()
{
	hChanges=false;
}

bool ObjectEditor::hasChanges()
{return hChanges;}

DrawableObject * ObjectEditor::getData()
{
	return tempData;
}

void ObjectEditor::changes()
{hChanges=true;}

void ObjectEditor::setData(DrawableObject * f)
{
	tempData=f;
	hChanges=false;
}

#endif
