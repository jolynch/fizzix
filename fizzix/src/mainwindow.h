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


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QTabWidget>
#include <QMenu>
#include <QMenuBar>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QApplication>
#include <QTimer>
#include <QTextBrowser>
#include <QGridLayout>
#include <QUrl>

#include "GLdrawpane.h"
#include "databrowser.h"
#include "dataeditor.h"
#include "simulationcontrol.h"
#include "databackend/databackend.h"
#include "databackend/changefactory.h"

/*@class MainWindow
 @brief The overhead window class.
 *  The MainWindow class contains the four big parts of Fizzix: the universe,
 *  the editor, the browser, and the control bar. These components are dockable.
 *  It handles some communication with the backend.
*/

class MainWindow:public QMainWindow
{	Q_OBJECT
	private:
		DataBackend * databackend;
		DataBrowser * databrowser;
		DataEditor * dataeditor;
		SimulationControl * simcontrol;
		GLDrawPane * openglpane;
		QTimer * timer;
	public:
		//Creates a mainwindow for fizzix.
		MainWindow (QDesktopWidget * d);
		//Checks for a needs to save data if the x button is pressed.
		void closeEvent(QCloseEvent *event);
	public slots:
		//Sets the view to isometric.
		void view_setIsometric();
		//Sets the view to the xy-plane.
		void view_setXY();
		//Sets the view to the xz-plane.
		void view_setXZ();
		//Sets the view to the yz-plane.
		void view_setYZ();
		//Zooms out to 10%.
		void view_zoom10();
		//Zooms out to 50%.
		void view_zoom50();
		//Zooms to scale.
		void view_zoom100();
		//Zooms in to 150%.
		void view_zoom150();
		//Zooms in to 200%.
		void view_zoom200();
		//Shows the manual.
		void showManual();
		//Shows the about popup.
		void showAbout();
		//Checks if there is an available reset.
		void checkResetAction();
};

#endif
