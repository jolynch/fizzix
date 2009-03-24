#ifndef MACROPANEL_CPP
#define MACROPANEL_CPP
#include "macropanel.h"

MacroPanel::MacroPanel():QWidget()
{
	QGridLayout * layout = new QGridLayout();
	layout->addWidget(new QLabel ("Macros"),0,0);
	this->setLayout(layout);
}

#endif
