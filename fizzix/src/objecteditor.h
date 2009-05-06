#ifndef OBJECTEDITOR_H
#define OBJECTEDITOR_H
#include <QWidget>
#include <QTabWidget>

#include "shapeeditor.h"
#include "propertylisteditor.h"
#include "databackend/drawableobject.h"

class ObjectEditor:public QTabWidget
{	Q_OBJECT
	private:
		bool hChanges;
		ShapeEditor * shape;
		PropertyListEditor * plist;
	public:
		ObjectEditor();
		bool hasChanges();
		DrawableObject * getData();
	public slots:
		void changes();
		void setData(DrawableObject o);
};
#endif
