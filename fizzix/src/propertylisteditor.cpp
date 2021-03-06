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
#ifndef PROPERTYLISTEDITOR_CPP
#define PROPERTYLISTEDITOR_CPP
#include "propertylisteditor.h"

PropertyListEditor::PropertyListEditor():QWidget()
{
	model=new MapKeyListModel <fizdatum>();
	QGridLayout * layout = new QGridLayout();
	plist=new QListView();
	plist->setModel(model->getModel());
	plist->setSelectionMode(QAbstractItemView::SingleSelection);
	plist->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QObject::connect(plist,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(editProp()));
	layout->addWidget(plist,0,0,1,4);
	QPushButton * newPB=new QPushButton("New");
	QObject::connect(newPB, SIGNAL(clicked()),this, SLOT(addProp()));
	QPushButton * delPB=new QPushButton("Delete");
	QObject::connect(delPB, SIGNAL(clicked()),this, SLOT(delProp()));
	QPushButton * edPB=new QPushButton("Edit");
	QObject::connect(edPB, SIGNAL(clicked()),this, SLOT(editProp()));
	layout->addWidget(newPB,1,1);
	layout->addWidget(delPB,1,2);
	layout->addWidget(edPB,1,3);
	this->setLayout(layout);
	hChanges=false;
}

bool PropertyListEditor::hasChanges()
{return hChanges;}

DrawableObject * PropertyListEditor::getAdditionalData(DrawableObject * _o)
{
	FizObject * o = (FizObject *)(_o);
	hChanges=false;
	QMap<QString, fizdatum> *m=model->getData();
	QList<QString> v=m->keys();
	for(int i=0; i<v.size(); i++)
		o->setProperty(v.at(i).toStdString(),m->value(v.at(i)));
	return _o;
}

void PropertyListEditor::changes()
{hChanges=true;}

void PropertyListEditor::setData(DrawableObject f)
{
	model->purge();
	std::vector<std::string> v=f.getSetProperties();
	for(unsigned int i=0; i<v.size(); i++)
		model->setElement(QString::fromStdString(v.at(i)),f[v.at(i)]);
	hChanges=false;
}

void PropertyListEditor::addProp()
{
	bool ok;
	QString name = QInputDialog::getText(this, "New Element","Enter name for new element", QLineEdit::Normal,QString(), &ok);
	if (!ok || name.isEmpty())
		{return;}
	if (name.simplified().contains(' '))
	{
		QMessageBox::information(this, "Invalid name", "Property names may not contain whitespace.");
		return;
	}
	model->setElement(name, fizdatum());
	hChanges=true;
}

void PropertyListEditor::delProp()
{
	QString s=model->getModel()->data(plist->currentIndex(), Qt::DisplayRole).toString();
	if(!(s.startsWith("SYSTEM_")))
	{
		model->delElement(s);
		hChanges=true;
	}
	else
		QMessageBox::information(this, "System property", "Properties beginning with SYSTEM_ may not be deleted once created.");
}

void PropertyListEditor::editProp()
{
	QString s=model->getModel()->data(plist->currentIndex(), Qt::DisplayRole).toString();
	fizdatum d=model->getData()->value(s);
	EditPropertyDialog * edit=new EditPropertyDialog(s,d);
	if(edit->exec()==QDialog::Accepted)
	{
		if(edit->saveName()!=s)
			model->delElement(s);
		model->setElement(edit->saveName(),edit->getData());
		hChanges=true;
	}
}

#endif
