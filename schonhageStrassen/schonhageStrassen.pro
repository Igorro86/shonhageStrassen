TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    modoperations.cpp
SOURCES += fft.cpp

HEADERS += fft.h \
    modoperations.h \
    main.h

