#ifndef EDITPROPERTYDIALOG_H
#define EDITPROPERTYDIALOG_H
#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <libfizzix/gen_structs.h>
#include "databackend/mapkeylistmodel.h"
#include "constanteditor.h"

class EditPropertyDialog:public QDialog
{	Q_OBJECT
	private:
		bool hChanges;
		QString loadName;;
		QLineEdit * name;
		ConstantEditor * constEditor;
	public:
		EditPropertyDialog(QString _name, fizdatum obj);
		bool hasChanges();
		QString saveName();
		fizdatum getData();
	public slots:
		void changes();
};

#endif
