TEMPLATE	= app
CONFIG		= qt warn_on release
HEADERS		= astrocalc.h \
		  astrocalcbib.h \
		  astrocalcscope.h \
		  juliandate.h \
		  magdlg.h \
		  teledlg.h \
		  vergrdlg.h
SOURCES		= astrocalc.cpp \
		  astrocalcbib.cpp \
		  astrocalcscope.cpp \
		  juliandate.cpp \
		  magdlg.cpp \
		  main.cpp \
		  teledlg.cpp \
		  vergrdlg.cpp
INTERFACES	= JulianDateDlg.ui \
		  MagnitudeDlg.ui \
		  TeleDataDlg.ui \
		  VergroesserungDlg.ui
TARGET		= astrocalc
