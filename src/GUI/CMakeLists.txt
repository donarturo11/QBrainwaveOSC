#projectName(QBrainwaveOSC)

add_subdirectory(SettingsWidget)
add_subdirectory(GraphsWidget)

set(MAINWINDOW_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.ui
    )

set(GUI_SOURCES
    ${MAINWINDOW_SOURCES}
    ${SETTINGS_WIDGET_SOURCES}
    ${GRAPHS_WIDGET_SOURCES}
    PARENT_SCOPE
   )


