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
	
  	/** Ermittelt das Aufl�sungsverm�gen des Teleskops */
  	double Aufloesung();
  	
  	/** Errechnet das Julianische Datum */
  	double JulianDate( int Tag, int Monat, int Jahr, int h, int m, bool vorChristus );
	
	/** Pr�ft das Datum und die Uhrzeit auf korrekte Werte */
  	bool checkDate( int Tag, int Monat, int Jahr, int h, int m );
  	
  	/** Ermittelt den Helligkeitsunterschied zweier Objekte ( Sterne, Planeten etc.) */
  	double Magnitude( double h1, double h2 );
  	
  	/** Ermittelt das notwendige Okular f�r die gew�nschte Vergr��erung */
  	double Okular( double Vergr );
  	
  	/** Errechnet die erzielbare Vergr��erung anhand des Okulars */
  	double Vergroesserung( double Okular );
  	
  	/** Ermittelt die Grenzgr��e in mag anhand der Vergr��erung */
	double Grenzgroesse ( double Vergr );
	
	/** Ermittelt die maximal sinnvolle Vergr��erung */
	int MaxSinnvoll();
	
	/** Ermittelt die minimal sinnvolle Vergr��erung */
	int MinSinnvoll();
	
	/** Ermittelt das �ffnungsverh�ltnis f/x */
	double Oeffnungsverhaeltnis();

private: // Private attributes
	/**  */
	double result;
};

#endif
