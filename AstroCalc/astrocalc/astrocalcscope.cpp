/***************************************************************************
                          astrocalcscope.cpp  -  description
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

#include "astrocalcscope.h"

struct TeleskopDaten TeleData = { 0, 0, 1 };
AstroCalcScope Teleskop;

AstroCalcScope::AstroCalcScope()
{
}

AstroCalcScope::~AstroCalcScope()
{
}


/**
  * Pr�ft, ob die ermittelte Vergr��erung sinnvoll ist. Es wird die maximale
  * und minimale Vergr��erung ber�cksichtigt.
  */
QString AstroCalcScope::MinMaxSinnvoll( QString Ausgabe, int Vergr, int MinSinnvoll, int MaxSinnvoll )
{
	QString addAusgabe = "";
	
	/** Max. sinnvolle Vergr��erung */
	if ( Vergr > MaxSinnvoll )
	{
		QString strVergr = strVergr.number( MaxSinnvoll );
			
		addAusgabe = "\n\nACHTUNG: Max. sinnvolle Vergr��erung " + strVergr
					+ "-fach �berschritten !";
	}
	
	/** Min. sinvolle Vergr��erung */
	else if ( Vergr < MinSinnvoll )
	{
		QString strVergr = strVergr.number( MinSinnvoll );
			
		addAusgabe = "\n\nACHTUNG: Min. sinnvolle Vergr��erung " + strVergr
					+ "-fach unterschritten";
	}
	
	/** Kompletten Ausgabe-String zur�ckgeben */	
	return ( Ausgabe + addAusgabe );
}




/** Pr�ft, ob g�ltige Teleskopdaten vorhanden sind */
bool AstroCalcScope::TeleDataOK()
{
	return ( TeleData.Durchmesser > 0 && TeleData.Brennweite > 0 );
}
