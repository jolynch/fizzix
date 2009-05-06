#ifndef SHAPEEDITOR_CPP
#define SHAPEEDITOR_CPP
#include "shapeeditor.h"

ShapeEditor::ShapeEditor():QWidget()
{
	QGridLayout * layout=new QGridLayout();
	shapeSelect=new QComboBox();
	shapeSelect->addItem("Prism");
	shapeSelect->addItem("Cylinder");
	shapeSelect->addItem("Sphere");
	QObject::connect(shapeSelect, SIGNAL(activated(int)),this,SLOT(selectedShape(int)));
	QObject::connect(shapeSelect, SIGNAL(activated(int)),this,SLOT(changes()));
	layout->addWidget(shapeSelect,0,0,1,2);
	rlabel=new QLabel("Radius");
	layout->addWidget(rlabel,1,0);
	wlabel=new QLabel("Width");
	layout->addWidget(wlabel,1,0);
	llabel=new QLabel("Length");
	layout->addWidget(llabel,3,0);
	hlabel=new QLabel("Height");
	layout->addWidget(hlabel,2,0);
	QDoubleValidator * v=new QDoubleValidator(this);
	redit=new QLineEdit("0");
	redit->setValidator(v);
	QObject::connect(redit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	layout->addWidget(redit,1,1);
	wedit=new QLineEdit("0");
	wedit->setValidator(v);
	QObject::connect(wedit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	layout->addWidget(wedit,1,1);
	ledit=new QLineEdit("0");
	ledit->setValidator(v);
	QObject::connect(ledit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	layout->addWidget(ledit,3,1);
	hedit=new QLineEdit("0");
	hedit->setValidator(v);
	QObject::connect(hedit,SIGNAL(textEdited(QString)),this,SLOT(changes()));
	layout->addWidget(hedit,2,1);
	this->setLayout(layout);
	hChanges=false;
	curr=PRISM;
	selectedShape(curr);
}

bool ShapeEditor::hasChanges()
{return hChanges;}

std::vector<triangle *> ShapeEditor::getData()
{
	hChanges=false;
	switch(curr)
	{
		case PRISM:return DrawableObject::makePrism(wedit->text().toDouble(),ledit->text().toDouble(),hedit->text().toDouble());
		case CYLINDER: return DrawableObject::makeCylinder(redit->text().toDouble(),hedit->text().toDouble());
		case SPHERE: return DrawableObject::makeSphere(redit->text().toDouble());
		default: return std::vector<triangle *> ();
	};
}

DrawableObject * ShapeEditor::getAdditionalData(DrawableObject * _o)
{
	FizObject * o = (FizObject *)(_o);
	o->setProperty("SYSTEM_preset_geomtype",fizdatum((double)curr));
	switch(curr)
	{
		case PRISM:
			o->setProperty("SYSTEM_width",fizdatum(wedit->text().toDouble()));
			o->setProperty("SYSTEM_length",fizdatum(ledit->text().toDouble()));
			o->setProperty("SYSTEM_height",fizdatum(hedit->text().toDouble()));
			break;
		case CYLINDER:
			o->setProperty("SYSTEM_radius",fizdatum(redit->text().toDouble()));
			o->setProperty("SYSTEM_height",fizdatum(hedit->text().toDouble()));
			break;
		case SPHERE: 
			o->setProperty("SYSTEM_radius",fizdatum(redit->text().toDouble()));
			break;
	};
	hChanges=false;
	return _o;
}

void ShapeEditor::changes()
{hChanges=true;}

void ShapeEditor::setData(DrawableObject f)
{
	redit->setText("0");
	wedit->setText("0");
	hedit->setText("0");
	ledit->setText("0");
	if(f.contains("SYSTEM_preset_geomtype"))
	{
		int c=(int)(f["SYSTEM_preset_geomtype"].scalar);
		selectedShape(c);
		switch(curr)
		{
			case PRISM:
				wedit->setText(QString::number(f["SYSTEM_width"].scalar));
				ledit->setText(QString::number(f["SYSTEM_length"].scalar));
				hedit->setText(QString::number(f["SYSTEM_height"].scalar));
				break;
			case CYLINDER:
				redit->setText(QString::number(f["SYSTEM_radius"].scalar));
				hedit->setText(QString::number(f["SYSTEM_height"].scalar));
				break;
			case SPHERE:
				redit->setText(QString::number(f["SYSTEM_radius"].scalar));
				break;
		};
	}
	else
	{
		curr=PRISM;
		selectedShape(curr);
	}
	hChanges=false;
}

void ShapeEditor::selectedShape(int s)
{
	shapeSelect->setCurrentIndex(s);
	switch(s)
	{
		case PRISM:
			curr=PRISM;
			redit->setVisible(false);
			wedit->setVisible(true);
			hedit->setVisible(true);
			ledit->setVisible(true);
			rlabel->setVisible(false);
			wlabel->setVisible(true);
			hlabel->setVisible(true);
			llabel->setVisible(true);
			break;
		case CYLINDER:
			curr=CYLINDER;
			redit->setVisible(true);
			wedit->setVisible(false);
			hedit->setVisible(true);
			ledit->setVisible(false);
			rlabel->setVisible(true);
			wlabel->setVisible(false);
			hlabel->setVisible(true);
			llabel->setVisible(false);
			break;
		case SPHERE:
			curr=SPHERE;
			redit->setVisible(true);
			wedit->setVisible(false);
			hedit->setVisible(false);
			ledit->setVisible(false);
			rlabel->setVisible(true);
			wlabel->setVisible(false);
			hlabel->setVisible(false);
			llabel->setVisible(false);
			break;
	};
	hChanges=false;
}

#endif
