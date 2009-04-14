/************************************************************************************************
 This file is a part of the Fizzix project, which provides a physics engine and the visualization.
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

#ifndef MACROPANEL_H
#define MACROPANEL_H
#include <QListWidget>

/*@class MacroPanel
 @brief Provides a panel to show Macros*/

class MacroPanel:public QListWidget
{	Q_OBJECT
	public:
		MacroPanel();
};

#endif
