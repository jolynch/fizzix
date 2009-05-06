#ifndef SHAPEEDITOR_H
#define SHAPEEDITOR_H
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>

#include "databackend/drawableobject.h"

enum PredefinedShapeType {PRISM,SPHERE,CYLINDER};

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
	public:
		ShapeEditor();
		bool hasChanges();
		std::vector<triangle *> getData();
		DrawableObject * getAdditionalData(DrawableObject * _o);
	public slots:
		void changes();
		void setData(DrawableObject o);
		void selectedShape(int s);
};
#endif
