#ifndef OBJECTEDITOR_CPP
#define OBJECTEDITOR_CPP
#include "objecteditor.h"

ObjectEditor::ObjectEditor():QTabWidget()
{
	shape=new ShapeEditor();
	this->addTab(shape,"Shape");
	plist=new PropertyListEditor();
	this->addTab(plist,"Properties");
	hChanges=false;
}

bool ObjectEditor::hasChanges()
{return hChanges||plist->hasChanges()||shape->hasChanges();}

DrawableObject * ObjectEditor::getData()
{
	hChanges=false;
	DrawableObject * out=new DrawableObject("Temp name",shape->getData());
	out=plist->getAdditionalData(out);
	out=shape->getAdditionalData(out);
	return out;
}

void ObjectEditor::changes()
{hChanges=true;}

void ObjectEditor::setData(DrawableObject f)
{
	shape->setData(f);
	plist->setData(f);
	hChanges=false;
}

#endif
