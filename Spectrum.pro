TEMPLATE = app

TARGET = Spectrum

QT += core gui widgets opengl

LIBS += -ljack -lfftw3f -lm

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    jackclient.cpp \
    spectrumwidget.cpp \
    fftwwrapper.cpp \
    prefdialog.cpp \
    settings.cpp

HEADERS += \
    mainwindow.h \
    jackclient.h \
    spectrumwidget.h \
    fftwwrapper.h \
    prefdialog.h \
    settings.h
