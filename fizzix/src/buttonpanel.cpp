#ifndef BUTTONPANEL_CPP
#define BUTTONPANEL_CPP
#include "buttonpanel.h"

ButtonPanel::ButtonPanel():QWidget()
	{
	QGridLayout * layout = new QGridLayout();
	layout->addWidget(new QPushButton("Buttons"),0,0);
	this->setLayout(layout);
	}

#endif
