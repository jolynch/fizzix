#ifndef PROPERTYLISTEDITOR_H
#define PROPERTYLISTEDITOR_H
#include <QWidget>
#include "databackend/drawableobject.h"

class PropertyListEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
	public:
		PropertyListEditor();
		bool hasChanges();
		void getAdditionalData(DrawableObject * o);
	public slots:
		void changes();
		void setData(DrawableObject o);
};
#endif
