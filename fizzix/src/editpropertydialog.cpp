#ifndef EDITPROPERTYDIALOG_CPP
#define EDITPROPERTYDIALOG_CPP
#include "editpropertydialog.h"

EditPropertyDialog::EditPropertyDialog(QString _name, fizdatum obj):QDialog()
{
	hChanges=false;
	loadName=_name;
	bool systemProperty=loadName.startsWith("SYSTEM_");
	QGridLayout * layout=new QGridLayout();
	if(!systemProperty)
	{
	   QLabel * nameL=new QLabel("Name:");
	   name=new QLineEdit(loadName);
	   QObject::connect(name,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	   layout->addWidget(nameL,0,0);
	   layout->addWidget(name,0,1,1,3);
	   constEditor=new ConstantEditor();
	   constEditor->setData(obj);
	   layout->addWidget(constEditor,1,0,1,4);
	}
	else
	{
	   bool scalar=obj.type==SCALAR;
	   constEditor=new ConstantEditor(scalar,!scalar);
	   constEditor->setData(obj);
	   layout->addWidget(constEditor,1,0,1,4);
	}
	QPushButton * okay=new QPushButton("OK");
	QObject::connect(okay,SIGNAL(clicked()),this,SLOT(accept()));
	QPushButton * cancel=new QPushButton("Cancel");
	QObject::connect(cancel,SIGNAL(clicked()),this,SLOT(reject()));
	layout->addWidget(okay, 2, 2);
	layout->addWidget(cancel, 2, 3);
	this->setLayout(layout);
}

bool EditPropertyDialog::hasChanges()
{return hChanges||constEditor->hasChanges();}

fizdatum EditPropertyDialog::getData()
{return constEditor->getData();}

void EditPropertyDialog::changes()
{hChanges=true;}

QString EditPropertyDialog::saveName()
{
	if(hChanges)
		return name->text();
	else
		return loadName;
}
#endif
