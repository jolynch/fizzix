#ifndef FORMULAEDITOR_H
#define FORMULAEDITOR_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <libfizzix/fizformula.h>
#include "databackend/databackend.h"

class FormulaEditor:public QWidget
{	Q_OBJECT
	private:
		DataBackend * db;
		bool hChanges;
		QTextEdit * formEdit;
		FizFormula tempData;
	public:
		FormulaEditor(DataBackend * _db);
		bool hasChanges();
		FizFormula * getData();
	public slots:
		void changes();
		void setData(FizFormula f);
		void showAvailableSymbolsDialog();
};

#endif
