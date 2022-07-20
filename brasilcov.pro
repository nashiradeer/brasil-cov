TEMPLATE = app

TARGET = brasilcov
VERSION = 0.0.1.0

DESTDIR = build

RESOURCES = resources.qrc
RC_ICONS = icons/brasilcov.ico

QT = gui widgets network

SOURCES += src/main.cpp \
    src/core.cpp \
    src/mainwindow.cpp \
    src/aboutwindow.cpp \
    src/optionswindow.cpp \
    src/statsitem.cpp \
    src/statsmenu.cpp

HEADERS += src/core.h \
    src/mainwindow.h \
    src/aboutwindow.h \
    src/optionswindow.h \
    src/statsitem.h \
    src/statsmenu.h

FORMS += src/mainwindow.ui \
    src/aboutwindow.ui \
    src/optionswindow.ui \
    src/statsitem.ui \
    src/statsmenu.ui

TRANSLATIONS += lang/brasilcov_pt.ts
