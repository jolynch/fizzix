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
#ifndef CONSTANTEDITOR_H
#define CONSTANTEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QDebug>

#include <libfizzix/gen_structs.h>

// This class is a dialog that can edit constants. It has an option to switch between scalar and vector,
// and text boxes to enter numerical floating-point values.
class ConstantEditor:public QWidget
{	Q_OBJECT
	private:
		bool isScalar;
		bool hChanges;
		QRadioButton * scalar_rb;
		QRadioButton * vector_rb;
		QLineEdit * s_edit;
		QLineEdit * v1_edit;
		QLineEdit * v2_edit;
		QLineEdit * v3_edit;
	public:
		//Returns a graphical widget to edit fizdatums.
		ConstantEditor(bool forceScalar=false, bool forceVector=false);
		//Retrieves the data.
		fizdatum getData();
		//Is set when there are changes to be saved.
		bool hasChanges();
	public slots:
		//Loads data.
		void setData(fizdatum d);
		//Utility slot when changes are made.
		void changes();
		//Responds to a change in type of constant.
		void radioButtonSelected(bool s); //true if scalar, false if vector.
	signals:
		//Saves the changes of the program.
		void saveChanges();
};


#endif
