/***************************************************************************
                          magdlg.h  -  description
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

#ifndef MAGDLG_H
#define MAGDLG_H

#include <qwidget.h>
#include "MagnitudeDlg.h"
#include "astrocalcbib.h"

/**
  *@author Michael Cebak
  */

class MagDlg : public MagnitudeDlg  {
   Q_OBJECT
public: 
	MagDlg(QWidget *parent=0, const char *name=0);
	~MagDlg();
	
public slots: // Public slots
  /** Ermittelt die Magnituden-Differenz zweier Objekte */
  void slotMagDiff();

private:
	AstroCalcBib *CalcBib;
};

#endif
