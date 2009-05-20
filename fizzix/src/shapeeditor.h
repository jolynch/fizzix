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
#ifndef SHAPEEDITOR_H
#define SHAPEEDITOR_H
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>

#include "databackend/drawableobject.h"

// This class lets the user change the shape of their objects. For example, it allows them to change radius and height of a cylinder, and may be used to redefine the geometry of custom objects.
class ShapeEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		PredefinedShapeType curr;
		QComboBox * shapeSelect;
		QLabel * rlabel;
		QLabel * wlabel;
		QLabel * llabel;
		QLabel * hlabel;
		QLineEdit * redit;
		QLineEdit * hedit;
		QLineEdit * wedit;
		QLineEdit * ledit;
		QCheckBox * approxCOM;
	public:
		ShapeEditor();
		bool hasChanges();
		std::vector<triangle *> getData();
		void setProperties(DrawableObject * _o);
		DrawableObject * getAdditionalData(DrawableObject * _o);
	public slots:
		void changes();
		void setData(DrawableObject o);
		void selectedShape(int s);
};
#endif
