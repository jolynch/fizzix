#ifndef PROPERTYLISTEDITOR_CPP
#define PROPERTYLISTEDITOR_CPP
#include "propertylisteditor.h"

PropertyListEditor::PropertyListEditor():QWidget()
{
	hChanges=false;
}

bool PropertyListEditor::hasChanges()
{return hChanges;}

void PropertyListEditor::getAdditionalData(DrawableObject * o)
{
	hChanges=false;
}

void PropertyListEditor::changes()
{hChanges=true;}

void PropertyListEditor::setData(DrawableObject f)
{

	hChanges=false;
}

#endif
