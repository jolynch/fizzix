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
#ifndef PROPERTYLISTEDITOR_H
#define PROPERTYLISTEDITOR_H
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "editpropertydialog.h"
#include "databackend/drawableobject.h"
#include "databackend/mapkeylistmodel.h"

// This constitutes a tab of the Object Editor, and shows a list of an objects' properties that the user can change.
class PropertyListEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		QListView * plist;
		MapKeyListModel <fizdatum> * model;
	public:
		PropertyListEditor();
		bool hasChanges();
		DrawableObject * getAdditionalData(DrawableObject * o);
	public slots:
		void changes();
		void addProp();
		void delProp();
		void editProp();
		void setData(DrawableObject _o);
};
#endif
