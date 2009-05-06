#ifndef FORMULAEDITOR_H
#define FORMULAEDITOR_H
#include <QWidget>

#include <libfizzix/fizformula.h>

class FormulaEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		
		FizFormula * tempData;
	public:
		FormulaEditor();
		bool hasChanges();
		FizFormula * getData();
	public slots:
		void changes();
		void setData(FizFormula * f);
};

#endif
