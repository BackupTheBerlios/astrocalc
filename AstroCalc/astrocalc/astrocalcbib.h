/***************************************************************************
                          astrocalcbib.h  -  description
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

#ifndef ASTROCALCBIB_H
#define ASTROCALCBIB_H


/**Main-Lib for the calculations
  *@author Michael Cebak
  */

class AstroCalcBib
{

public:
	AstroCalcBib();
	~AstroCalcBib();
	
  	/** Ermittelt das Auflösungsvermögen des Teleskops */
  	double Aufloesung();
  	
  	/** Errechnet das Julianische Datum */
  	double JulianDate( int Tag, int Monat, int Jahr, int h, int m, bool vorChristus );
	
	/** Prüft das Datum und die Uhrzeit auf korrekte Werte */
  	bool checkDate( int Tag, int Monat, int Jahr, int h, int m );
  	
  	/** Ermittelt den Helligkeitsunterschied zweier Objekte ( Sterne, Planeten etc.) */
  	double Magnitude( double h1, double h2 );
  	
  	/** Ermittelt das notwendige Okular für die gewünschte Vergrößerung */
  	double Okular( double Vergr );
  	
  	/** Errechnet die erzielbare Vergrößerung anhand des Okulars */
  	double Vergroesserung( double Okular );
  	
  	/** Ermittelt die Grenzgröße in mag anhand der Vergrößerung */
	double Grenzgroesse ( double Vergr );
	
	/** Ermittelt die maximal sinnvolle Vergrößerung */
	int MaxSinnvoll();
	
	/** Ermittelt die minimal sinnvolle Vergrößerung */
	int MinSinnvoll();
	
	/** Ermittelt das Öffnungsverhältnis f/x */
	double Oeffnungsverhaeltnis();

private: // Private attributes
	/**  */
	double result;
};

#endif
