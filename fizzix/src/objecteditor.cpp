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
	shape->setProperties(out);
	out=plist->getAdditionalData(out);
	out=shape->getAdditionalData(out);
	return out;
}

void ObjectEditor::changes()
{hChanges=true;}

void ObjectEditor::setData(DrawableObject f)
{
	const vec3 & pos = f.getPos();
	if(isnan(pos.x)||isnan(pos.y)||isnan(pos.z))
		f.setPos(vec3(0.0,0.0,0.0));
	shape->setData(f);
	plist->setData(f);
	hChanges=false;
}

#endif
