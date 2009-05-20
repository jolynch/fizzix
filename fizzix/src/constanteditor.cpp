/************************************************************************************************
This file is a part of libfizzix backend to the Fizzix project.
The website for this project is http://code.google.com/p/fizzix .
Copyright (C) 2009
	Joseph Lynch
	Anton Frolenkov
	Purnima Balakrishnan
	Daniel Stiles
	Eric Van Albert

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
************************************************************************************************/
#ifndef CONSTANTEDITOR_CPP
#define CONSTANTEDITOR_CPP
#include "constanteditor.h"

ConstantEditor::ConstantEditor(bool forceScalar, bool forceVector):QWidget()
{
	hChanges=false; isScalar=false;
	QGridLayout * layout = new QGridLayout();
	scalar_rb = new QRadioButton("Scalar", this);
	vector_rb = new QRadioButton("Vector", this);
	scalar_rb->setDown(true);
	QObject::connect(scalar_rb,SIGNAL(toggled(bool)),this,SLOT(radioButtonSelected(bool)));
	QObject::connect(scalar_rb,SIGNAL(toggled(bool)),this,SLOT(changes()));
	layout->addWidget(scalar_rb,0,0,1,2);
	layout->addWidget(vector_rb,2,0,1,2);
	QDoubleValidator * v=new QDoubleValidator(this);
	s_edit=new QLineEdit(this);
	QObject::connect(s_edit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	QObject::connect(s_edit,SIGNAL(returnPressed()),this,SIGNAL(saveChanges()));
	s_edit->setValidator(v);
	layout->addWidget(s_edit,1,1,1,3);
	v1_edit=new QLineEdit(this);
	QObject::connect(v1_edit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	QObject::connect(v1_edit,SIGNAL(returnPressed()),this,SIGNAL(saveChanges()));
	v1_edit->setValidator(v);
	layout->addWidget(v1_edit,3,1,1,1);
	v2_edit=new QLineEdit(this);
	QObject::connect(v2_edit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	QObject::connect(v2_edit,SIGNAL(returnPressed()),this,SIGNAL(saveChanges()));
	v2_edit->setValidator(v);
	layout->addWidget(v2_edit,3,2,1,1);
	v3_edit=new QLineEdit(this);
	QObject::connect(v3_edit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	QObject::connect(v3_edit,SIGNAL(returnPressed()),this,SIGNAL(saveChanges()));
	v3_edit->setValidator(v);
	layout->addWidget(v3_edit,3,3,1,1);
	s_edit->setText("0.0");
	v1_edit->setText("0.0");
	v2_edit->setText("0.0");
	v3_edit->setText("0.0");
	vector_rb->setEnabled(!forceScalar);
	scalar_rb->setEnabled(!forceVector);
	this->setLayout(layout);
	hChanges=false;
}

bool ConstantEditor::hasChanges()
{return hChanges;}

fizdatum ConstantEditor::getData()
{
	hChanges=false;
	if(isScalar)
		return fizdatum(s_edit->text().toDouble());
	else
		return fizdatum(vec3(v1_edit->text().toDouble(),v2_edit->text().toDouble(),v3_edit->text().toDouble()));
}

void ConstantEditor::setData(fizdatum d)
{
	switch(d.type)
	{
		case VECTOR:
			isScalar=false;
			radioButtonSelected(false);
			s_edit->setText("0.0");
			v1_edit->setText(QString::number(d.vector.x));
			v2_edit->setText(QString::number(d.vector.y));
			v3_edit->setText(QString::number(d.vector.z));
			break;
		case SCALAR:
			isScalar=true;
			radioButtonSelected(true);
			s_edit->setText(QString::number(d.scalar));
			v1_edit->setText("0.0");
			v2_edit->setText("0.0");
			v3_edit->setText("0.0");
			break;
		default:
			isScalar=true;
			radioButtonSelected(true);
			s_edit->setText("0.0");
			v1_edit->setText("0.0");
			v2_edit->setText("0.0");
			v3_edit->setText("0.0");
			break;
	};
	hChanges=false;
}

void ConstantEditor::radioButtonSelected(bool s)
{
	isScalar=s;
	if(isScalar)
		{
		s_edit->setEnabled(true);
		scalar_rb->setChecked(true);
		v1_edit->setEnabled(false);
		v2_edit->setEnabled(false);
		v3_edit->setEnabled(false);
		}
	else
		{
		s_edit->setEnabled(false);
		vector_rb->setChecked(true);
		v1_edit->setEnabled(true);
		v2_edit->setEnabled(true);
		v3_edit->setEnabled(true);
		}
}

void ConstantEditor::changes()
{hChanges=true;}

#endif
