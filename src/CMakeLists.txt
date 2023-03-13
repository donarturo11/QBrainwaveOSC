#projectName(QBrainwaveOSC)

add_subdirectory(MainWindow)
add_subdirectory(BluetoothInterface)
set(PROJECT_SOURCES
    ${MAINWINDOW_SOURCES}
    ${BLUETOOTHINTERFACE_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
   )


