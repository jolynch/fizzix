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
#ifndef EDITPROPERTYDIALOG_H
#define EDITPROPERTYDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <libfizzix/gen_structs.h>
#include "databackend/mapkeylistmodel.h"
#include "constanteditor.h"

// This class provides a dialog with which the user can edit an object's properties. It is launched from the data editor when the user wants to edit a property.
class EditPropertyDialog:public QDialog
{	Q_OBJECT
	private:
		bool hChanges;
		QString loadName;;
		QLineEdit * name;
		ConstantEditor * constEditor;
	public:
		//Contructs a popup dialog containing a constant editor to object properties.
		EditPropertyDialog(QString _name, fizdatum obj);
		//Returns true if changes have been made.
		bool hasChanges();
		//Returns the name under which the edited property will be saved.
		QString saveName();
		//Returns the GUI as a property
		fizdatum getData();
	public slots:
		//Notifies the widget of changes.
		void changes();
};

#endif
