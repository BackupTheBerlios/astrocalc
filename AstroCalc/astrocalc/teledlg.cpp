/***************************************************************************
                          teledlg.cpp  -  description
                             -------------------
    begin                : Thu Jun 21 2001
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

//#include <qbuttongroup.h>
//#include <qgroupbox.h>
#include <qlineedit.h>
//#include <qpushbutton.h>
#include <qradiobutton.h>
//#include <qlayout.h>
//#include <qvariant.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>

#include "teledlg.h"
#include "astrocalcscope.h"

TeleDlg::TeleDlg(QWidget *parent, const char *name ) : TeleDataDlg(parent,name, true)
{
}


TeleDlg::~TeleDlg()
{
}


/** Konvertiert die Teleskopdaten in mm */
void TeleDlg::slotConvertTeleData()
{
	bool ok;
	double typ = 1;
	
	/** Modifikator anhand des Teleskoptyps setzen */
	if ( RBtypNewton->isOn() )
		typ = 0.95;
	else if ( RBtypSC->isOn() )
		typ = 0.9;
		
	TeleData.typMod = typ;
		
	double durch = LEdurchmesser->text().toDouble( &ok );
	if ( ok )
	{
		TeleData.Durchmesser = durch;
		
		/** Konvertierung für die Öffnung */
		if ( RBdurchZoll->isOn() )
			TeleData.Durchmesser = durch * 25.4;
	};
	
	double brenn = LEbrennweite->text().toDouble( &ok );
	if ( ok )
	{
		TeleData.Brennweite = brenn;
		
		/** Konvertierung für die Brennweite */
		if ( RBbrennMeter->isOn() )
			TeleData.Brennweite = brenn * 1000;
	}
}
