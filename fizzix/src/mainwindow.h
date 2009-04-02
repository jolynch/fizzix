#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTabWidget>

#include "buttonpanel.h"
#include "forcepanel.h"
#include "macropanel.h"
#include "objectpanel.h"
#include "propertypanel.h"

class MainWindow:public QWidget
{	Q_OBJECT
	public:
		MainWindow ();
};

#endif
