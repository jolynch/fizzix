/************************************************************************************************
This file is a part of the Fizzix project, which provides a physics engine and the visualization.
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


#ifndef DATAEDITOR_H
#define DATAEDITOR_H
#include <QLabel>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QStackedLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

#include "databackend/databackend.h"
#include "databackend/changefactory.h"
#include "constanteditor.h"
#include "objecteditor.h"
#include "forceeditor.h"
#include "formulaeditor.h"

/*@class DataEditor
 @brief Provides a panel to edit data
 *  The DataEditor lets the user change the properties of any element. For
 *  objects, it has two tabs, one for shape information and one for the system
 *  properties. It can also display a formula editor for forces and macros, or
 *  a simple set of text boxes for constants.
*/

class DataEditor:public QDockWidget
{	Q_OBJECT
	private:
		enum currentlyLoaded {none,objectLoaded,forceLoaded,macroLoaded,constantLoaded};
		currentlyLoaded curr;
		
		DataBackend * db;
		QLabel * nameL;
		QLineEdit * name;
		QString loadName;
		QStackedLayout * centerL;
		ConstantEditor * constEditor;
		ObjectEditor * objectEditor;
		ForceEditor * forceEditor;
		FormulaEditor * macroEditor;
	public:
		//Creates a widget to edit selected elements.
		DataEditor (DataBackend * _db, QDesktopWidget * d);
		//Checks if the editor needs to save changes.
		bool checkToSave();
	public slots:
		//Loads the default view.
		void loadBlank();
		//Loads an object.
		void loadObject(QString n);
		//Loads a force.
		void loadForce(QString n);
		//Loads a macro.
		void loadMacro(QString n);
		//Loads a constant.
		void loadConstant(QString n);
		//Saves changes.
		void saveChanges();
		//Reverts changes.
		void revertChanges();
};

#endif
