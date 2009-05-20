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


#ifndef DATABROWSER_H
#define DATABROWSER_H
#include <QTabWidget>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QListView>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QInputDialog>
#include <QStringListModel>
#include "databackend/databackend.h"
#include "databackend/changefactory.h"

/*@class DataBrowser
 @brief Provides a panel to browse data
 *  The DataBrowser is a graphical component that has five tabs: one for
 *  objects, one for forces, macros, and constants. Each tab shows a list of the
 *  given element, and a search box to locate elements. New elements can be
 *  added, and old one deleted and edited.
*/
class DataBrowser:public QDockWidget
{	Q_OBJECT
	private:
		QTabWidget * tabs;
		QListView * objects;
		QListView * forces;
		QListView * macros;
		QListView * consts;
		DataBackend * db;
	public:
		//Creates a graphical data browser.
		DataBrowser ( DataBackend * _d,QDesktopWidget * d);
	public slots:
		//Is called when text is entered to search.
		void textEntered(QString);
		//Adds an element based on the selected tab.
		void addElement();
		//Deletes the selected element.
		void deleteElement();
		//Edits the selected element in the DataEditor.
		void editElement();
		//Disconnects the objects pane during editing to prevent editing without pausing.
		void disconnectObjects(bool discon);
	signals:
		//These signals are emitted to inform of actions, and represent their names.
		void addObject(QString);
		void deleteObject(QString);
		void editObject(QString);
		
		void addForce(QString);
		void deleteForce(QString);
		void editForce(QString);
		
		void addMacro(QString);
		void deleteMacro(QString);
		void editMacro(QString);
		
		void addConstant(QString);
		void deleteConstant(QString);
		void editConstant(QString);
};

#endif
