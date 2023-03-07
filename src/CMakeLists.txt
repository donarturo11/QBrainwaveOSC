#projectName(QBrainwaveOSC)

add_subdirectory(MainWindow)
set(MAINWINDOW_SOURCES
    ${MAINWINDOW_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
   )


