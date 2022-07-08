set(brasilcov_SOURCES
    main.cpp
    mainwindow.cpp
    statsmenu.cpp
    statsitem.cpp
    ../resources.qrc
)

add_executable(brasilcov ${brasilcov_SOURCES})

target_link_libraries(brasilcov
    Qt5::Core
    Qt5::Widgets
)