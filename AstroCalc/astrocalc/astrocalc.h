/***************************************************************************
                          astrocalc.h  -  description
                             -------------------
    begin                : Son Jun 17 17:20:29 CEST 2001
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

#ifndef ASTROCALC_H
#define ASTROCALC_H

// include files for QT
#include <qapp.h>
#include <qmainwindow.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qstatusbar.h>
#include <qwhatsthis.h>
#include <qstring.h>
#include <qpixmap.h>
#include <qmsgbox.h>
#include <qfiledialog.h>
#include <qprinter.h>
#include <qpainter.h>
#include <qlabel.h>
#include <qgroupbox.h>

#include "astrocalcbib.h"


/**
  * This Class is the base class for your application. It sets up the main
  * window and providing a menubar, toolbar
  * and statusbar. For the main view, an instance of class AstroCalcView is
  * created which creates your view.
  */
class AstroCalcApp : public QMainWindow
{
  Q_OBJECT
  
  public:
    /** construtor */
    AstroCalcApp();
    /** destructor */
    ~AstroCalcApp();

    /** initializes all QActions of the application */
    void initActions();

    /** initMenuBar creates the menu_bar and inserts the menuitems */
    void initMenuBar();

    /** this creates the toolbars. Change the toobar look and add new toolbars in this
     * function */
	void initToolBar();

    /** setup the statusbar */
    void initStatusBar();

    /** setup the main-label */
    void initMainLabel();

    /** updates the output */
    void refreshMainLabel();

    /** overloaded for Message box on last window exit */
    bool queryExit();

  public slots:
	
    /** exits the application */
    void slotFileQuit();

	/** Stammdaten des Teleskops */
	void slotDataTeleskop();
	
	/** Ermittelt Vergroesserung */
	void slotBerechneVergroesserung();
	/** Ermittelt notwendiges Okular */
	void slotBerechneOkular();
	/** Ermittelt die Gernzgroesse */
	void slotBerechneGrenzgroesse();

	/** Berechnet Helligkeitsunterschied zweier Objekte */
	void slotToolsMagnitude();
	/** Ermittelt das Julianische Datum */
	void slotToolsJulianDatum();
	
    /** toggle the toolbar*/
	void slotViewToolBar(bool toggle);
    /** toggle the statusbar*/
    void slotViewStatusBar(bool toggle);

    /** shows an about dlg*/
    void slotHelpAbout();


  private:

    /** view is the main widget which represents your working area. The View
     * class should handle all events of the view widget.  It is kept empty so
     * you can create your view according to your application's needs by
     * changing the view class.
     */

	/** file_menu contains all items of the menubar entry "File" */
    QPopupMenu *fileMenu;

	/** Stammdaten-Menue */
	QPopupMenu *dataMenu;
	/** Menue fuer die Berechnungen */
	QPopupMenu *berechneMenu;
	/** Menue fuer sonstige Berechnungen und Tools */
	QPopupMenu *toolsMenu;
	/** view_menu contains all items of the menubar entry "View" */
    QPopupMenu *viewMenu;
    /** view_menu contains all items of the menubar entry "Help" */
    QPopupMenu *helpMenu;
    /** the main toolbar */
	QToolBar *mainToolbar;
	
	
    /** actions for the application initialized in initActions() and used to en/disable them
      * according to your needs during the program */
    QAction *fileQuit;

    QAction *dataTeleskop;

    QAction *berechneVergroesserung;
    QAction *berechneOkular;
    QAction *berechneGrenzgroesse;

    QAction *toolsMagnitude;
    QAction *toolsJulianDatum;

	QAction *viewToolBar;
    QAction *viewStatusBar;

    QAction *helpAboutApp;

	QGroupBox *mainGroup;
    QLabel *mainLabel;

    AstroCalcBib *CalcBib;

};

#endif
