/***************************************************************************
                          magdlg.cpp  -  description
                             -------------------
    begin                : Wed Jul 18 2001
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

#include <qlabel.h>
#include <qlineedit.h>
#include "magdlg.h"

MagDlg::MagDlg(QWidget *parent, const char *name ) : MagnitudeDlg(parent,name, true)
{
	CalcBib = new AstroCalcBib();
}

MagDlg::~MagDlg()
{
	delete CalcBib;
}


/** Ermittelt die Magnituden-Differenz zweier Objekte */
void MagDlg::slotMagDiff()
{
	bool tausche = false;
	bool ok = false;
	QString str = "";
	
	double h1 = LEobj1->text().toDouble( &ok );
	if ( ok )
	{
		double h2 = LEobj2->text().toDouble( &ok );
		if ( ok )
		{
			double diff = CalcBib->Magnitude( h1, h2 );
			if ( h2 > h1 )
				tausche = true;
			
			QString s = "";
			QString strDiff = s.number( diff, 'g', 6 );
			if ( tausche )
				str = "Das 1. Objekt ist " + strDiff + "-mal heller als das 2. Objekt";
			else
				str = "Das 2. Objekt ist " + strDiff + "-mal heller als das 1. Objekt";
				
			TLdiff->setText( str );
		}
	}
}
