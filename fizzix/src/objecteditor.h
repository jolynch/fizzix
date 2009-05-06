#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H
#include <QWidget>

#include "databackend/drawableobject.h"

class ObjectEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		
		DrawableObject * tempData;
	public:
		ObjectEditor();
		bool hasChanges();
		DrawableObject * getData();
	public slots:
		void changes();
		void setData(DrawableObject * o);
};
#endif
