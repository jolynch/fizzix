#ifndef FORMULAEDITOR_H
#define FORMULAEDITOR_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QGridLayout>
#include <libfizzix/fizformula.h>

class FormulaEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		QTextEdit * formEdit;
		FizFormula tempData;
	public:
		FormulaEditor();
		bool hasChanges();
		FizFormula * getData();
	public slots:
		void changes();
		void setData(FizFormula f);
		void showAvailableSymbolsDialog();
};

#endif
