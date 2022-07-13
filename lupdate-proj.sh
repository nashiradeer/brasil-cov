#!/bin/bash

lupdate \
    resources.qrc \
    src/aboutwindow.ui src/aboutwindow.cpp \
    src/mainwindow.cpp src/mainwindow.ui \
    src/optionswindow.ui src/optionswindow.cpp \
    src/statsitem.ui src/statsitem.ui \
    src/statsmenu.cpp src/statsmenu.ui \
    -ts \
    lang/portugues.ts