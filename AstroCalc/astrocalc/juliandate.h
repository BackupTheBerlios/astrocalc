/***************************************************************************
                          juliandate.h  -  description
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

#ifndef JULIANDATE_H
#define JULIANDATE_H

#include <qwidget.h>
#include "JulianDateDlg.h"
#include "astrocalcbib.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;

/**
  *@author Michael Cebak
  */

class JulianDate : public JulianDateDlg
{
   Q_OBJECT

public:
	JulianDate(QWidget *parent=0, const char *name=0);
	~JulianDate();
	void Fehler( int a );
	
private:
	AstroCalcBib *CalcBib;
	
public slots: // Public slots
	/** No descriptions */

public slots: // Public slots
	/** No descriptions */
  	void slotBerechneJD();
};

#endif
