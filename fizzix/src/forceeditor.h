#ifndef FORCEEDITOR_H
#define FORCEEDITOR_H
#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include "formulaeditor.h"
#include <libfizzix/fizforce.h>

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
