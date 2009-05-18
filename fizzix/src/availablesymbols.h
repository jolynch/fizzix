#ifndef AVAILABLESYMBOLS_H
#define AVAILABLESYMBOLS_H

#include <QLabel>
#include <QComboBox>
#include <QListWidget>
#include <QListView>
#include <QStackedWidget>
#include "databackend/databackend.h"

class AvailableSymbols:public QWidget
{	Q_OBJECT
	private:
		QComboBox * switcher;
		QListWidget * presets;
		QListView * objects;

};

#endif
