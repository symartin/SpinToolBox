/*
Copyright (C) 2012 Sylvain Martin (Spintec - CEA/CNRS/UJF/G-INP)
All rights reserved.

This file is part of the SpinToolBox

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
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/


#include "SScriptZlib.h"

#include <QScriptExtensionPlugin>
#include <QScriptExtensionPlugin>
#include <QScriptable>
#include <QScriptContext>
#include <QScriptEngine>

Q_EXPORT_PLUGIN2(SScriptZlib,SScriptZlib)


SScriptZlib::SScriptZlib()
{

}

SScriptZlib::~SScriptZlib()
{

}

void SScriptZlib::initialize ( const QString & key, QScriptEngine * engine ){
	if(key == "stb.scriptzlib"){


	}



}


QStringList SScriptZlib::keys () const{


	QStringList res;
	res.append("stb.scriptzlib");
	return res;
} 