/***************************************************************************
                          astrocalcscope.h  -  description
                             -------------------
    begin                : Sun Jun 17 2001
    copyright            : (C) 2001 by Michael Cebak
    email                : sternensaal@web.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef ASTROCALCSCOPE_H
#define ASTROCALCSCOPE_H

#include <qstring.h>

/**
  *@author Michael Cebak
  */


struct TeleskopDaten
{
	double Durchmesser;
	double Brennweite;
	double typMod;
};	

	
class AstroCalcScope
{

public:
	AstroCalcScope();
	~AstroCalcScope();
	
	/** Pr�ft, ob die ermittelte Vergr��erung sinnvoll ist. Es wird die maximale und
	  *	minimale Vergr��erung ber�cksichtigt.
	  */
  	QString MinMaxSinnvoll( QString Ausgabe, int Vergr, int MinSinnvoll, int MaxSinnvoll );

	/** Pr�ft, ob g�ltige Teleskopdaten vorhanden sind */
  	bool TeleDataOK();

};

extern TeleskopDaten TeleData;
extern AstroCalcScope Teleskop;

#endif
