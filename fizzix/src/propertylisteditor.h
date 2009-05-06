#ifndef PROPERTYLISTEDITOR_H
#define PROPERTYLISTEDITOR_H
#include <QWidget>
#include <QListView>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QInputDialog>
#include "editpropertydialog.h"
#include "databackend/drawableobject.h"
#include "databackend/mapkeylistmodel.h"

class PropertyListEditor:public QWidget
{	Q_OBJECT
	private:
		bool hChanges;
		QListView * plist;
		MapKeyListModel <fizdatum> * model;
	public:
		PropertyListEditor();
		bool hasChanges();
		DrawableObject * getAdditionalData(DrawableObject * o);
	public slots:
		void changes();
		void addProp();
		void delProp();
		void editProp();
		void setData(DrawableObject _o);
};
#endif
