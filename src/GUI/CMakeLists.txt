#projectName(QBrainwaveOSC)

add_subdirectory(SettingsWidget)
add_subdirectory(MonitorWidget)

set(MAINWINDOW_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
    ${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.ui
    )

set(GUI_SOURCES
    ${MAINWINDOW_SOURCES}
    ${SETTINGS_WIDGET_SOURCES}
    ${MONITOR_WIDGET_SOURCES}
    PARENT_SCOPE
   )


