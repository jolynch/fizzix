#ifndef EDITPROPERTYDIALOG_H
#define EDITPROPERTYDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <libfizzix/gen_structs.h>
#include "constanteditor.h"

class EditPropertyDialog:public QDialog
{	Q_OBJECT
	private:
		QString loadName;
		QLineEdit * name;
};

#endif
