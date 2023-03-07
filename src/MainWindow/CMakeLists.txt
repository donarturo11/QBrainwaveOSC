#projectName(QBrainwaveOSC)

add_subdirectory(SettingsWidget)
set(MAINWINDOW_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.ui
    ${SETTINGS_WIDGET_SOURCES}
    PARENT_SCOPE
   )


