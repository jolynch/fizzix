#ifndef FORCEEDITOR_H
#define FORCEEDITOR_H
#include <QWidget>

#include <libfizzix/fizforce.h>

class ForceEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		
		FizForce * tempData;
	public:
		ForceEditor();
		bool hasChanges();
		FizForce * getData();
	public slots:
		void changes();
		void setData(FizForce * f);
};

#endif
