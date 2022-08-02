TEMPLATE = app

TARGET = brasilcov
VERSION = 0.0.1.0

DESTDIR = build

RESOURCES = resources.qrc
RC_ICONS = icons/brasilcov.ico

QT = gui widgets network

SOURCES += \
    src/core/application.cpp \
    src/core/dataitem.cpp \
    src/core/network.cpp \
    src/main.cpp \
    src/views/mainwindow.cpp \
    src/views/aboutwindow.cpp \
    src/views/optionswindow.cpp \
    src/views/statsitem.cpp \
    src/views/statsmenu.cpp

HEADERS += \
    src/core/application.h \
    src/core/dataitem.h \
    src/core/network.h \
    src/views/mainwindow.h \
    src/views/aboutwindow.h \
    src/views/optionswindow.h \
    src/views/statsitem.h \
    src/views/statsmenu.h

FORMS += \
    src/uis/mainwindow.ui \
    src/uis/aboutwindow.ui \
    src/uis/optionswindow.ui \
    src/uis/statsitem.ui \
    src/uis/statsmenu.ui

TRANSLATIONS += lang/brasilcov_pt.ts
