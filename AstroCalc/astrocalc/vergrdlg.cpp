/***************************************************************************
                          vergrdlg.cpp  -  description
                             -------------------
    begin                : Wed Oct 3 2001
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
#include <qbuttongroup.h>
#include <qcheckbox.h>
#include <qradiobutton.h>
#include <qmessagebox.h>
#include "vergrdlg.h"

VergrDlg::VergrDlg(QWidget *parent, const char *name ) : VergroesserungDlg(parent,name, true)
{
	CalcBib = new AstroCalcBib();
	barlow = 1;
}

VergrDlg::~VergrDlg()
{
	delete CalcBib;
}

/** Ermittelt die Vergroesserung anhand des Okulars */
void VergrDlg::slotVergroesserung()
{
	bool ok = false;
	
	double Okular = LEokular->text().toDouble( &ok );
		
	if ( ok )
	{
	
		if ( CBbarlow->isChecked() )
		{
			//BGbarlow->setEnabled( true );
			if ( RBbarlow2x->isChecked() )
				barlow = 2;
			else if ( RBbarlow3x->isChecked() )
				barlow = 3;
			else if ( RBbarlow4x->isChecked() )
				barlow = 4;
		};
		
		double Vergr = CalcBib->Vergroesserung( Okular );
		Vergr *= (double) barlow;
		QString strVergr = strVergr.number( Vergr, 'f', 0 );
		strVergr += "-fach.";
		TLvergroesserung->setText( strVergr );
	}
	
	else QMessageBox::information ( this, "Ungültige Eingabe", "Bitte einen Wert eingeben" );
}
