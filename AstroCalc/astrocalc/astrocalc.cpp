/***************************************************************************
                          astrocalc.cpp  -  description
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <qaccel.h>
#include "astrocalc.h"
#include "astrocalcscope.h"
#include "juliandate.h"
#include "teledlg.h"
#include "magdlg.h"
#include "vergrdlg.h"


static const char* const imageApp_data[] = {
"32 32 5 1",
". c None",
"c c #000000",
"b c #000083",
"a c #ff0000",
"# c #ffffff",
"................................",
"......................##........",
".....................####..##...",
"......................##...##...",
"................................",
"........................aa......",
"........................aa..##..",
"...........................####.",
"............................##..",
"...................bb...........",
".................bbbb...........",
"...............bbbbbb...........",
".......bb....bbbbbbbb...........",
".....bb....bbbbbbbbbb...........",
"...bb.bb.bbbbbbbbbb.............",
".......bbbbbbbbbb...............",
".....bbbbbbbbbb.................",
".....bbbbbbbb...................",
"...bbbbbbbbcccc.................",
"..bbbbbbb..ccc.c................",
".....bb....ccc..c...............",
"...........ccc...ccc............",
"..........c.c.c..ccc............",
"..........c.c.c..cc.............",
".........c..c..c................",
".........c..c..c................",
"........c...c...c...............",
"........c...c...c...............",
".......c....c....c..............",
".......c....c....c..............",
"......c.....c.....c.............",
".....ccc...ccc...ccc............"};


static const char* const imageJD_data[] = {
"16 16 2 1",
". c None",
"# c #000000",
"................",
"................",
"....##..........",
"....##..........",
"....##..........",
"....##..........",
".#..##..........",
".#####..####....",
"..###...##..#...",
"........##...#..",
"........##...#..",
"........##...#..",
"........##..#...",
"........####....",
"................",
"................"};


static const char* const imageMag_data[] = {
"16 16 3 1",
". c None",
"a c #000000",
"# c #fffaff",
"................",
"...#............",
"..###...........",
"..###...........",
"...#............",
".....aaa........",
".....aa.........",
".....a.aa.......",
".......aa.a.....",
".........aa.....",
"........aaa.....",
"................",
"............##..",
"............##..",
"................",
"................"};



/**
  * Initialisiert die Komponenten der Anwendung
  */
AstroCalcApp::AstroCalcApp()
{
	CalcBib = new AstroCalcBib();

	QPixmap imageApp( ( const char** ) imageApp_data );
	setIcon( imageApp );	
	setCaption( tr( "AstroCalc" ));
	/* setCaption(tr("AstroCalc " VERSION)); */
	/* Fenster laesst sich dennoch verkleinern... Any hints ?! */
	setFixedSize( 400, 240 );
	
	///////////////////////////////////////////////////////////////////
	// call inits to invoke all other construction parts
  	initActions();
  	initMenuBar();
	initToolBar();
  	initMainLabel();
  	initStatusBar();
  	
  	viewToolBar->setOn(true);
  	viewStatusBar->setOn(true);
}


/**
  * Desktruktor
  */
AstroCalcApp::~AstroCalcApp()
{
	delete CalcBib;
}


/**
  * Initialisiert alle QActions der Anwendung incl.
  * aller connects zu den jeweiligen Slots
  */
void AstroCalcApp::initActions()
{
	QPixmap JulianDateIcon( ( const char** ) imageJD_data );
	QPixmap MagnitudeIcon( ( const char** ) imageMag_data );
	
	//JulianDateIcon = QPixmap( "toolJulianDate.xpm" );
	//MagnitudeIcon = QPixmap( "toolMagnitude.xpm" );

	fileQuit = new QAction(tr("Exit"), tr("E&xit"), QAccel::stringToKey(tr("Ctrl+Q")), this);
  	fileQuit->setStatusTip(tr("Beendet das Programm"));
  	fileQuit->setWhatsThis(tr("Exit\n\nBeendet das Programm"));
  	connect(fileQuit, SIGNAL(activated()), this, SLOT(slotFileQuit()));
	
	dataTeleskop = new QAction( tr( "Teleskop" ), tr( "Teleskop" ), QAccel::stringToKey( tr( "Ctrl+T" )), this );
	dataTeleskop->setStatusTip( tr( "Eingabe der Teleskopdaten" ) );
	dataTeleskop->setWhatsThis( tr( "Teleskop\n\nFragt die Teleskopdaten (Öffnung / Brennweite) ab" ) );
	connect( dataTeleskop, SIGNAL( activated() ), this, SLOT( slotDataTeleskop() ));
	
	berechneVergroesserung = new QAction( tr( "Vergrößerung" ), tr( "Vergrößerung" ), 0, this );
	berechneVergroesserung->setStatusTip( tr( "Berechnet die Vergrößerung" ) );
	berechneVergroesserung->setWhatsThis( tr( "Vergrößerung\n\nErmittelt anhand des Okulars die erzielte Vergrößerung" ) );
	connect( berechneVergroesserung, SIGNAL( activated() ), this, SLOT( slotBerechneVergroesserung() ));
	
	berechneOkular = new QAction( tr( "Okular" ), tr( "Okular" ), 0, this );
	berechneOkular->setStatusTip( tr( "Ermittelt das Okular" ) );
	berechneOkular->setWhatsThis( tr( "Okular\n\nErmittelt das Okular anhand der Vergrößerung" ) );
	connect( berechneOkular, SIGNAL( activated() ), this, SLOT( slotBerechneOkular() ));
	
	berechneGrenzgroesse = new QAction( tr( "Grenzgröße" ), tr( "Grenzgröße" ), 0, this );
	berechneGrenzgroesse->setStatusTip( tr( "Ermittelt die Grenzgröße" ) );
	berechneGrenzgroesse->setWhatsThis( tr( "Grenzgröße\n\nErmittelt die Grenzgröße anhand der Vergrößerung" ) );
	connect( berechneGrenzgroesse, SIGNAL( activated() ), this, SLOT( slotBerechneGrenzgroesse() ));
	
	toolsMagnitude = new QAction( tr( "Magnitude" ), MagnitudeIcon, tr( "Magnitude" ), QAccel::stringToKey( tr( "Ctrl+M" )), this );
	toolsMagnitude->setStatusTip( tr( "Helligkeitsunterschied zweier Objekte" ) );
	toolsMagnitude->setWhatsThis( tr( "Magnitude\n\nErmittelt den Helligkeitsunterschied zweier Objekte" ) );
	connect( toolsMagnitude, SIGNAL( activated() ), this, SLOT( slotToolsMagnitude() ));
	
	toolsJulianDatum = new QAction( tr( "Julian. Datum" ), JulianDateIcon, tr( "Julian. Datum" ), QAccel::stringToKey( tr( "Ctrl+J" )), this );
	toolsJulianDatum->setStatusTip( tr( "Berechnet das Julianische Datum" ) );
	toolsJulianDatum->setWhatsThis( tr( "Julianisches Datum\n\nBerechnet das Julianische Datum" ) );
	connect( toolsJulianDatum, SIGNAL( activated() ), this, SLOT( slotToolsJulianDatum() ));
		
	viewToolBar = new QAction(tr("Toolbar"), tr("Tool&bar"), 0, this, 0, true);
  	viewToolBar->setStatusTip(tr("Toolbar ein-/ausschalten"));
  	viewToolBar->setWhatsThis(tr("Toolbar\n\nToolbar ein-/ausschalten"));
  	connect(viewToolBar, SIGNAL(toggled(bool)), this, SLOT(slotViewToolBar(bool)));

  	viewStatusBar = new QAction(tr("Statusbar"), tr("&Statusbar"), 0, this, 0, true);
  	viewStatusBar->setStatusTip(tr("Statusbar ein-/ausschalten"));
  	viewStatusBar->setWhatsThis(tr("Statusbar\n\nStatusbar ein-/ausschalten"));
  	connect(viewStatusBar, SIGNAL(toggled(bool)), this, SLOT(slotViewStatusBar(bool)));

	helpAboutApp = new QAction(tr("Über"), tr("Über..."), 0, this);
  	helpAboutApp->setStatusTip(tr("Über das Programm"));
  	helpAboutApp->setWhatsThis(tr("Über\n\nÜber das Programm"));
  	connect(helpAboutApp, SIGNAL(activated()), this, SLOT(slotHelpAbout()));
  	
  	if ( !Teleskop.TeleDataOK() )
	{
		berechneVergroesserung->setEnabled( false );
		berechneOkular->setEnabled( false );
		berechneGrenzgroesse->setEnabled( false );
	}
}


/**
  * Erstellt die Menuezeile mit den jeweiligen Eintraegen
  */
void AstroCalcApp::initMenuBar()
{
  	// menuBar entry fileMenu
  	fileMenu=new QPopupMenu();
	fileQuit->addTo(fileMenu);

	// menuBar entry dataMenu
	dataMenu = new QPopupMenu();
	dataTeleskop->addTo( dataMenu );
	
	// menuBar entry berechneMenu
	berechneMenu = new QPopupMenu();
	berechneVergroesserung->addTo( berechneMenu );
	berechneOkular->addTo( berechneMenu );
	berechneGrenzgroesse->addTo( berechneMenu );
	
	// menuBar entry toolsMenu
	toolsMenu = new QPopupMenu();
	toolsMagnitude->addTo( toolsMenu );
	toolsJulianDatum->addTo( toolsMenu );  	

	// menuBar entry viewMenu
	viewMenu=new QPopupMenu();
  	viewMenu->setCheckable(true);
	viewToolBar->addTo(viewMenu);
  	viewStatusBar->addTo(viewMenu);
  	
  	// menuBar entry helpMenu
  	helpMenu=new QPopupMenu();
  	helpAboutApp->addTo(helpMenu);

   	// MENUBAR CONFIGURATION
  	menuBar()->insertItem(tr("&Datei"), fileMenu);
	menuBar()->insertItem( tr( "&Stammdaten" ), dataMenu );
	menuBar()->insertItem( tr( "&Berechnung" ), berechneMenu );
	menuBar()->insertItem( tr( "&Tools" ), toolsMenu );
  	menuBar()->insertItem(tr("&Ansicht"), viewMenu);
  	menuBar()->insertSeparator();
  	menuBar()->insertItem(tr("&Hilfe"), helpMenu);
}

/**
  * Initialisierung der ToolBar
  */
void AstroCalcApp::initToolBar()
{
	mainToolbar = new QToolBar(this, "Toolbar");
	toolsMagnitude->addTo( mainToolbar );
	toolsJulianDatum->addTo( mainToolbar );
	mainToolbar->addSeparator();
	QWhatsThis::whatsThisButton( mainToolbar );
}


/**
  * Initialisierung der StatusBar
  */
void AstroCalcApp::initStatusBar()
{
	statusBar()->message(tr("Bereit."), 2000);
}



/**
  * Aktualisiert die Ausgabe der Teleskopdaten
  */
void AstroCalcApp::refreshMainLabel()
{	
	/* Gueltige Teleskopdaten vorhanden ? */
	if ( !Teleskop.TeleDataOK() )
	{
		mainGroup->setTitle( "" );
		mainLabel->setText( "<center><b>Bitte erst Ihre Teleskopdaten eingeben</b></center>" );
	}
	else
	{
		mainGroup->setTitle( "Aktuelle Teleskopdaten" );
		QString s1 = "";
		QString strDurchm = s1.number( TeleData.Durchmesser, 'g', 6 );
		QString strBrennw = s1.number( TeleData.Brennweite, 'g', 6 );
		QString strAuflg = s1.number( CalcBib->Aufloesung(), 'g', 6 );
		QString strMax = s1.number( CalcBib->MaxSinnvoll() );
		QString strMin = s1.number( CalcBib->MinSinnvoll() );
		QString strOeffVer = s1.number( CalcBib->Oeffnungsverhaeltnis(), 'f', 0 );
	
		QString aktTeleData = "<b>Öffnung:</b> " + strDurchm + " mm  ( f/" + strOeffVer + " )"
								+ "<br/><b>Brennweite:</b> " + strBrennw + " mm"
								+ "<br/><b>Auflösungsvermögen:</b> " + strAuflg + " Bogensekunden"
								+ "<br/><b>Max. Vergrößerung:</b> " + strMax + "-fach"
								+ "<br/><b>Min. Vergrößerung:</b> " + strMin + "-fach";
								
		mainLabel->setText( aktTeleData );
		
		/** Enables menu entries for calculations */
		berechneVergroesserung->setEnabled( true );
		berechneOkular->setEnabled( true );
		berechneGrenzgroesse->setEnabled( true );
		
		
		/** debug calls BEGIN*/
		QString warnings = "";
		warnings = warnings.number( CalcBib->Magnitude( 6, 1 ), 'g', 6 );
		warnings = "AstroCalcBib::Magnitude() = " + warnings;
		qWarning( warnings );
		
		warnings = warnings.number( CalcBib->Grenzgroesse( 204 ), 'g', 6 );
		warnings = "AstroCalcBib::Grenzgroesse() = " + warnings;
		qWarning( warnings );
		/** debug calls END */
		
	}
}


/**
  * Initialisierung und Ausgabe der aktuellen Teleskopdaten
  */
void AstroCalcApp::initMainLabel()
{
	mainGroup = new QGroupBox( this, "mainGroup" );		
	mainGroup->setGeometry( QRect( 40, 65, 320, 120 ) );
	mainGroup->setAlignment( int( QGroupBox::AlignLeft ) );	
		
	mainLabel = new QLabel( mainGroup, "mainLabel" );
	mainLabel->setGeometry( QRect( 10, 20, 300, 90 ) );
	mainLabel->setAlignment( int( QLabel::WordBreak | QLabel::AlignVCenter | QLabel::AlignLeft ) );
	
	// just for debug purposes */
	refreshMainLabel();
}	


/**
  * Abfrage, ob Programm beendet werden soll
  */
bool AstroCalcApp::queryExit()
{
  int exit=QMessageBox::information(this, tr("Programm beenden..."),
                                    tr("Möchten Sie das Programm wirklich beenden ?"),
                                    QMessageBox::Ok, QMessageBox::Cancel);

  if (exit==1){}
  else {};

  return (exit==1);
}


/**
  * Alle SLOT Implementationen
  */


void AstroCalcApp::slotFileQuit()
{
  statusBar()->message(tr("Programm beenden..."));
  ///////////////////////////////////////////////////////////////////
  // exits the Application

/*
  if(doc->isModified())
  {
    if(queryExit())
    {
      qApp->quit();
    }
    else
    {

    };
  }
  else
  {
*/
    qApp->quit();
//  };

  statusBar()->message(tr("Bereit."));
}


void AstroCalcApp::slotDataTeleskop()
{
	statusBar()->message( tr( "Teleskopdaten eingeben..." ) );
	
	TeleDlg *Tdlg = new TeleDlg( this, 0 );
	Tdlg->exec();
	delete Tdlg;
	
	refreshMainLabel();
	
	statusBar()->message( tr( "Bereit." ) );
}


void AstroCalcApp::slotBerechneVergroesserung()
{
	statusBar()->message( tr( "Vergrößerung berechnen..." ) );
	
	
	VergrDlg *Vdlg = new VergrDlg( this, 0 );
	Vdlg->exec();
	delete Vdlg;	
	
	statusBar()->message( tr( "Bereit." ) );
}


void AstroCalcApp::slotBerechneOkular()
{
	statusBar()->message( tr( "Okular ermitteln..." ) );
	
	statusBar()->message( tr( "Bereit." ) );
}


void AstroCalcApp::slotBerechneGrenzgroesse()
{
	statusBar()->message( tr( "Grenzgöße ermitteln..." ) );
	
	statusBar()->message( tr( "Bereit." ) );
}


void AstroCalcApp::slotToolsMagnitude()
{
	statusBar()->message( tr( "Helligkeitsunterschied zweier Objekte..." ) );
	
	MagDlg *Mag = new MagDlg( this, 0 );
	Mag->exec();
	delete Mag;
	
	statusBar()->message( tr( "Bereit." ) );
}


void AstroCalcApp::slotToolsJulianDatum()
{
	statusBar()->message( tr( "Julianisches Datum..." ) );
	
	JulianDate *JDdlg = new JulianDate( this, 0 );
	JDdlg->exec();
	delete JDdlg;	
	
	statusBar()->message( tr( "Bereit." ) );
}


void AstroCalcApp::slotViewToolBar(bool toggle)
{
	statusBar()->message(tr("Toggle toolbar..."));
	
	// turn Toolbar on or off
	if (toggle== false)
  	{
    	mainToolbar->hide();
  	}
  	else
  	{
    	mainToolbar->show();
  	};

  	statusBar()->message(tr("Bereit."));
}


void AstroCalcApp::slotViewStatusBar(bool toggle)
{
	statusBar()->message(tr("Toggle statusbar..."));

  	//turn Statusbar on or off
	if (toggle == false)
  	{
    	statusBar()->hide();
  	}
  	else
  	{
    	statusBar()->show();
  	};

  	statusBar()->message(tr("Bereit."));
}


void AstroCalcApp::slotHelpAbout()
{
	QMessageBox::about(this,tr("Über..."),
					tr( "AstroCalc\nBeta Version\n(c) 2001 by Michael Cebak" ) );
					
                    /*  tr("AstroCalc\nVersion " VERSION "\n(c) 2001 by Michael Cebak") ); */
}

