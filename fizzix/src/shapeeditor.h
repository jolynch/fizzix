#ifndef SHAPEEDITOR_H
#define SHAPEEDITOR_H
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>

#include "databackend/drawableobject.h"



class ShapeEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		PredefinedShapeType curr;
		QComboBox * shapeSelect;
		QLabel * rlabel;
		QLabel * wlabel;
		QLabel * llabel;
		QLabel * hlabel;
		QLineEdit * redit;
		QLineEdit * hedit;
		QLineEdit * wedit;
		QLineEdit * ledit;
		QCheckBox * approxCOM;
	public:
		ShapeEditor();
		bool hasChanges();
		std::vector<triangle *> getData();
		void setProperties(DrawableObject * _o);
		DrawableObject * getAdditionalData(DrawableObject * _o);
	public slots:
		void changes();
		void setData(DrawableObject o);
		void selectedShape(int s);
};
#endif
