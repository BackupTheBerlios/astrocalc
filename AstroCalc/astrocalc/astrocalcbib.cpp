/***************************************************************************
                          astrocalcbib.cpp  -  description
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

#include <math.h>
#include "astrocalcscope.h"
#include "astrocalcbib.h"


AstroCalcBib::AstroCalcBib()
{
	result = 0;
}


AstroCalcBib::~AstroCalcBib()
{
}


/** Ermittelt das Auflösungsvermögen des Teleskops */
double AstroCalcBib::Aufloesung()
{
	result = 13.8 / ( TeleData.Durchmesser / 10 );
	return result;
}


/** Errechnet das Julianische Datum */
double AstroCalcBib::JulianDate( int Tag, int Monat, int Jahr, int h, int m, bool vorChristus)
{
	
	bool vor1582 = false;
	bool date_ndef = false;
	double b;
	
	/** Das Datum liegt in einem nicht definiertem Zeitraum */
	if ( (Tag >= 5 && Tag <= 14) && Monat == 10 && Jahr == 1582 && !vorChristus)
		date_ndef = true;
		
	/** Datum-Zeitraum in Ordnung */
	else
	{
		/** Genauen Zeitraum ermitteln */
		if ( (Jahr <= 1582 && !vorChristus) || vorChristus )
			vor1582 = true;
		if ( !vorChristus && Jahr > 1582 )
			vor1582 = false;
		if ( Jahr == 1582 && Monat > 10 && !vorChristus)
			vor1582 = false;
		if ( Jahr == 1582 && ( Tag > 14 && Monat == 10 ) && !vorChristus )
			vor1582 = false;
			
		/** Für Jahre vor Christus */
		if ( Jahr > 0 && vorChristus )
			Jahr = 1 - Jahr;
		
		/** Modifizierung des Monats */	
		if ( Monat <= 2 )
		{
			Jahr -= 1;
			Monat += 13;
		}
		else
			Monat += 1;
		
		/** Kalenderdatum bis 04.10.1582 n.Chr. */			
		if ( vor1582 )
			b = floor( (( (double) Jahr + 4716) / 4 ) - 1181 );
	
	
		/** Kalenderdatum ab 15.10.1582 n.Chr. */	
		if ( !vor1582 )
			b = floor( ( Jahr / 400 ) - ( Jahr / 100 ) + ( Jahr / 4 ) );
		
		/** Uhrzeit umrechnen */
		double modStunden = h;
		double modMinuten = m;
		double modUhrzeit = modStunden + ((( modMinuten * 100 ) / 60) / 100);
	
		double modMon = floor( 30.6 * (double) Monat );
		
		/** Julianisches Datum berechnen */
		result = ( 365 * Jahr ) - 679004 + b + modMon  + Tag + ( modUhrzeit / 24 ) + 2400000.5;
	
	}; /** else if ( !date_ndef ) */
	
	
	if ( date_ndef )
		return -2;  /** Kalender-Zeitraum nicht definiert */
	else
		return result;
}


/** Prüft das Datum und die Uhrzeit auf korrekte Werte */
bool AstroCalcBib::checkDate( int Tag, int Monat, int Jahr, int h, int m )
{
	bool dateOK = false;
	bool timeOK = false;
	bool istSchaltjahr = false;
	bool jahrOK = false;
	
	/** Jahreszahl positiv ? */
	if ( Jahr >= 0)
	{
		jahrOK = true;
		istSchaltjahr = ( ( Jahr%4 == 0 && Jahr%100 != 0 ) || Jahr%400 == 0 );
	
		/** Tag und Monat prüfen */
		if ( Tag >= 1 )
		{
			if ( Monat == 1 && Tag <= 31 )
				dateOK = true;
			if ( Monat == 2 && ( Tag <= 28 || ( Tag <= 29 && istSchaltjahr )))
				dateOK = true;
			if ( Monat == 3 && Tag <= 31 )
				dateOK = true;
			if ( Monat == 4 && Tag <= 30 )
				dateOK = true;
			if ( Monat == 5 && Tag <= 31 )
				dateOK = true;
			if ( Monat == 6 && Tag <= 30 )
				dateOK = true;
			if ( Monat == 7 && Tag <= 31 )
				dateOK = true;
			if ( Monat == 8 && Tag <= 31 )
				dateOK = true;
			if ( Monat == 9 && Tag <= 30 )
				dateOK = true;
			if ( Monat == 10 && Tag <= 31 )
				dateOK = true;
			if ( Monat == 11 && Tag <= 30 )
				dateOK = true;
			if ( Monat == 12 && Tag <= 31 )
				dateOK = true;
		}
	};
	
	/** Uhrzeit prüfen */
	timeOK = ( ( h >= 0 && h <= 23 ) && ( m >= 0 && m <= 59 ) );
	
	return( dateOK && timeOK && jahrOK );
}


/** Ermittelt den Helligkeitsunterschied zweier Objekte ( Sterne, Planeten etc.) */
double AstroCalcBib::Magnitude( double h1, double h2 )
{
	double diff;
	
	if ( h1 < h2 )
		diff = h2 - h1;
	else
		diff = h1 - h2;
		
	//result = pow( 2.5119, diff );
	result = pow( pow( 10, 0.4), diff );
	
	return result;	
}


/** Errechnet die erzielbare Vergrößerung anhand des Okulars */
double AstroCalcBib::Vergroesserung( double Okular )
{
	result = TeleData.Brennweite / Okular;
	return result;
}


/** Ermittelt das notwendige Okular für die gewünschte Vergrößerung */
double AstroCalcBib::Okular( double Vergr )
{
	result = TeleData.Brennweite / Vergr;
	return result;
}


/** Ermittelt die Grenzgröße in 'mag' anhand der Vergrößerung */
double AstroCalcBib::Grenzgroesse ( double Vergr )
{	
	result = ( 5.5 + 2.5 * log10(( TeleData.Durchmesser / 10 )) + 2.5 * log10( Vergr )) * TeleData.typMod;
	return result;
}


/** Ermittelt die maximal sinnvolle Vergrößerung */
int AstroCalcBib::MaxSinnvoll()
{
	return TeleData.Durchmesser * 2;
}
	

/** Ermittelt die minimal sinnvolle Vergrößerung */
int AstroCalcBib::MinSinnvoll()
{
	return TeleData.Durchmesser / 7;
}


/** Ermittelt das Öffnungsverhältnis f/x */
double AstroCalcBib::Oeffnungsverhaeltnis()
{
	return TeleData.Brennweite / TeleData.Durchmesser;
}

