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
  * Prüft, ob die ermittelte Vergrößerung sinnvoll ist. Es wird die maximale
  * und minimale Vergrößerung berücksichtigt.
  */
QString AstroCalcScope::MinMaxSinnvoll( QString Ausgabe, int Vergr, int MinSinnvoll, int MaxSinnvoll )
{
	QString addAusgabe = "";
	
	/** Max. sinnvolle Vergrößerung */
	if ( Vergr > MaxSinnvoll )
	{
		QString strVergr = strVergr.number( MaxSinnvoll );
			
		addAusgabe = "\n\nACHTUNG: Max. sinnvolle Vergrößerung " + strVergr
					+ "-fach überschritten !";
	}
	
	/** Min. sinvolle Vergrößerung */
	else if ( Vergr < MinSinnvoll )
	{
		QString strVergr = strVergr.number( MinSinnvoll );
			
		addAusgabe = "\n\nACHTUNG: Min. sinnvolle Vergrößerung " + strVergr
					+ "-fach unterschritten";
	}
	
	/** Kompletten Ausgabe-String zurückgeben */	
	return ( Ausgabe + addAusgabe );
}




/** Prüft, ob gültige Teleskopdaten vorhanden sind */
bool AstroCalcScope::TeleDataOK()
{
	return ( TeleData.Durchmesser > 0 && TeleData.Brennweite > 0 );
}
