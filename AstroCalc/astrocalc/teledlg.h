/***************************************************************************
                          teledlg.h  -  description
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

#ifndef TELEDLG_H
#define TELEDLG_H

#include <qwidget.h>
#include "TeleDataDlg.h"

/**
  *@author Michael Cebak
  */

class TeleDlg : public TeleDataDlg  {
   Q_OBJECT
public: 
	TeleDlg(QWidget *parent=0, const char *name=0);
	~TeleDlg();
public slots: // Public slots
  /** Konvertiert die Teleskopdaten in mm */
  void slotConvertTeleData();
};

#endif
