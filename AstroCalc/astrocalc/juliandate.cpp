/***************************************************************************
                          juliandate.cpp  -  description
                             -------------------
    begin                : Tue Jun 19 2001
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

//#include <qgroupbox.h>
#include <qlabel.h>
#include <qlineedit.h>
//#include <qpushbutton.h>
//#include <qlayout.h>
//#include <qvariant.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
//#include <qimage.h>
//#include <qpixmap.h>
//#include <qstring.h>
#include <qmessagebox.h>
#include <qcheckbox.h>

#include "juliandate.h"


JulianDate::JulianDate(QWidget *parent, const char *name ) : JulianDateDlg(parent,name, true)
{
	CalcBib = new AstroCalcBib();
	
}


JulianDate::~JulianDate()
{
	delete CalcBib;
}


void JulianDate::Fehler( int a )
{	
	TLjuliandate->setText( "" );
	QString msg = "";
	
	if ( a == 0 )
		msg = "Datums-/Zeitformat ungültig.";
	if ( a == 1 )
		msg = "Datums-/Zeitformat ungültig.\n\nZeitrechnung beginnt am\n01.01.4713 v.Chr. 12:00 Uhr (UTC).";
	if ( a == 2 )
		msg = "Datums-/Zeitformat ungültig.\n\nDas Datum 05.10.1582 bis 14.10.1582 ist nicht definiert.";
	
	QMessageBox::information ( this, "Ungültige Eingabe", msg );
}


/**
  * Berechnet das Julianische Datum und prüft gleichzeitig,
  * ob das Format der Uhrzeit und des Datums korrekt sind
  */
void JulianDate::slotBerechneJD()
{
	bool dateOK = false;
	bool timeOK = false;
	bool allesOK = false;
	bool ok= false;
	
	int tag=0;
	int monat=0;
	int jahr=0;
	int stunden=0;
	int minuten=0;
	
	tag = LEtag->text().toInt( &ok );
	if ( ok )
	{
		monat = LEmonat->text().toInt( &ok );
		if ( ok )
		{
			jahr = LEjahr->text().toInt( &ok );
			if ( ok )
			{
				dateOK = true;
				stunden = LEstunden->text().toInt( &ok );
				if ( ok )
				{
					minuten = LEminuten->text().toInt( &ok );
					if ( ok )
						timeOK = true;	
				}	
	   		}
		}
	}
		
	/** Konvertierung erfolgreich abgeschlossen */
	if ( dateOK && timeOK )
	{
		allesOK = CalcBib->checkDate( tag, monat, jahr, stunden, minuten );
		
		/** Format des Datums und der Uhrzeit sind korrekt */
		if ( allesOK )
		{
			double JD = CalcBib->JulianDate( tag, monat, jahr, stunden, minuten, CBvorChristus->isChecked() );
			
			if ( JD < 0 && JD != -2 )
				Fehler( 1 );
			else if ( JD == -2 )
				Fehler( 2 );
			else
			{			
				QString s = "";
				QString strJD = s.number( JD, 'f', 5 );
				TLjuliandate->setText( strJD );
			}
		}	
	};
	
	/** Es liegen Eingabefehler und/oder Formatfehler vor */	
	if ( !dateOK || !timeOK || !allesOK ) Fehler( 0 );
}
