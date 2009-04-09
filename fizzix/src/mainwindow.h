#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLabel>
#include <QTabWidget>
#include <QMenu>
#include <QMenuBar>
#include <QDockWidget>
#include <QDesktopWidget>

#include "buttonpanel.h"
#include "forcepanel.h"
#include "macropanel.h"
#include "objectpanel.h"
#include "propertypanel.h"

class MainWindow:public QMainWindow
{	Q_OBJECT
	public:
		MainWindow (QDesktopWidget * d);
};

#endif
