TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    modoperations.cpp \
    numberpiece.cpp \
    integerfile.cpp \
    integerfilehandler.cpp
SOURCES += fft.cpp

HEADERS += fft.h \
    modoperations.h \
    main.h \
    numberpiece.h \
    integerfile.h \
    integerfilehandler.h

