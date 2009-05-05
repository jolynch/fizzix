#ifndef CONSTANTEDITOR_H
#define CONSTANTEDITOR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QDoubleValidator>
#include <QDebug>

#include <libfizzix/gen_structs.h>

class ConstantEditor:public QWidget
{	Q_OBJECT
	private:
		bool isScalar;
		bool hChanges;
		QRadioButton * scalar_rb;
		QRadioButton * vector_rb;
		QLineEdit * s_edit;
		QLineEdit * v1_edit;
		QLineEdit * v2_edit;
		QLineEdit * v3_edit;
	public:
		ConstantEditor();
		fizdatum getData();
		bool hasChanges();
	public slots:
		void setData(fizdatum d);
		void changes();
		void radioButtonSelected(bool s); //true if scalar, false if vector.
	signals:
		void saveChanges();
};


#endif
