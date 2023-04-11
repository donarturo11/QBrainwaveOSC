#projectName(QBrainwaveOSC)

add_subdirectory(MainWindow)
add_subdirectory(ThinkGear)
set(PROJECT_SOURCES
    ${MAINWINDOW_SOURCES}
    ${THINKGEAR_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
   )


