////////////////////////////////////////////////////////////////////////////////////////////////////
/// \file		SUi\SUiLblLed.h
/// 		
/// \author		Sylvain Martin
/// \version	1.0
/// \date		02/24/2011
///
/// \brief	Declares the SUiLblLed class
/// 		
/// \section LICENSE
///
/// This program is free software; you can redistribute it and/or
/// modify it under the terms of the GNU General Public License as
/// published by the Free Software Foundation; either version 2 of
/// the License, or (at your option) any later version.
/// 
/// This program is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
/// General Public License for more details at
/// http://www.gnu.org/copyleft/gpl.html
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef SUILBLLED_H
#define SUILBLLED_H

#include <QLabel>


//////////////////////////////////////////////////////////////////////////////////////////////
/// \class SUiLblLed
///
/// \ingroup SUiMod
/// \brief this class provides a Qt Widget that display a "LED" which can change its color
//////////////////////////////////////////////////////////////////////////////////////////////////////
class SUiLblLed : public QLabel
{
	Q_OBJECT;

public:
	enum ledColor{
		red,
		green,
		grey,
		yellow,
		blue
	};

public slots:
	/// (SLOT) Puts the color red.
	void setRed(){setColor(red);}
	/// (SLOT) Puts the color green.
	void setGreen(){setColor(green);}
	/// (SLOT) Puts the color grey.
	void setGrey(){setColor(grey);}
	/// (SLOT) Puts the color yellow.
	void setYellow(){setColor(yellow);}
	/// (SLOT) Puts the color blue.
	void setBlue(){setColor(blue);}
	// (SLOT) Puts one color
	void setColor( SUiLblLed::ledColor c);

signals:
	//////////////////////////////////////////////////////////////////////////
	/// \fn  SUiLblLed::colorChanged(SUiLblLed::ledColor c)
	///
	/// \brief	(SIGNAL)Emitted when the color is changed.
	///
	/// \param c The new color.
	//////////////////////////////////////////////////////////////////////////
	void colorChanged(SUiLblLed::ledColor c);

public:
	SUiLblLed(QWidget * parent = NULL);

	SUiLblLed::ledColor color();

	
	//@name isColor 
	//@{
	bool isRed();
	bool isGreen();
	bool isYellow();
	bool isGrey();
	bool isBlue();
	//@}
private:
	ledColor color_;
};





#endif //SUILBLLED_H