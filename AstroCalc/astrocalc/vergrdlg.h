/***************************************************************************
                          vergrdlg.h  -  description
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

#ifndef VERGRDLG_H
#define VERGRDLG_H

#include <qwidget.h>
#include "VergroesserungDlg.h"
#include "astrocalcbib.h"

/**
  *@author Michael Cebak
  */

class VergrDlg : public VergroesserungDlg  {
   Q_OBJECT
public: 
	VergrDlg(QWidget *parent=0, const char *name=0);
	~VergrDlg();
	
private:
	AstroCalcBib *CalcBib;
	int barlow;
	
public slots: // Public slots
  /** No descriptions */
  void slotVergroesserung();
};

#endif
