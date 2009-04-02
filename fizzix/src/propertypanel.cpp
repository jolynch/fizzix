#ifndef PROPERTYPANEL_CPP
#define PROPERTYPANEL_CPP
#include "propertypanel.h"

PropertyPanel::PropertyPanel():QWidget()
{
	QGridLayout * layout = new QGridLayout();
	layout->addWidget(new QLabel ("Properties"),0,0);
	this->setLayout(layout);
}

#endif
