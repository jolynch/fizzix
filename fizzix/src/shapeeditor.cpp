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
	QObject::connect(shapeSelect, SIGNAL(currentIndexChanged(int)),this,SLOT(selectedShape(int)));
	QObject::connect(shapeSelect, SIGNAL(currentIndexChanged(int)),this,SLOT(changes()));
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

void ShapeEditor::getAdditionalData(DrawableObject * o)
{
	hChanges=false;
}

void ShapeEditor::changes()
{hChanges=true;}

void ShapeEditor::setData(DrawableObject f)
{
	redit->setText("0");
	wedit->setText("0");
	hedit->setText("0");
	ledit->setText("0");
	hChanges=false;
}

void ShapeEditor::selectedShape(int s)
{
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
