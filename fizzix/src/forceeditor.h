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
#ifndef FORCEEDITOR_H
#define FORCEEDITOR_H
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "formulaeditor.h"
#include <libfizzix/fizforce.h>

// This panel lets the user edit a force by entering a formula. They have a large text box with which to enter a prefix LISP-style equation, and can reference properties with $ and @.
class ForceEditor:public QWidget
{	Q_OBJECT
	private:
		DataBackend * db;
		bool hChanges;
		FormulaEditor * formEdit;
		QLineEdit * fromField;
		QLineEdit * onField;
	public:
		ForceEditor(DataBackend * _db);
		bool hasChanges();
		FizForce * getData();
	public slots:
		void changes();
		void setData(FizForce f);
};

#endif
