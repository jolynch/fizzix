#ifndef FORCEPANEL_CPP
#define FORCEPANEL_CPP
#include "forcepanel.h"

ForcePanel::ForcePanel():QWidget()
{
	QGridLayout * layout = new QGridLayout();
	layout->addWidget(new QLabel ("Forces"),0,0);
	this->setLayout(layout);
}

#endif
