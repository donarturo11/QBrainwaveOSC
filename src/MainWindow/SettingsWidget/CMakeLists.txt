#projectName(QBrainwaveOSC)

set(DEVICECONFIG_WIDGET_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceConfiguration.h
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceConfiguration.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceConfiguration.ui
   )

set(SETTINGS_WIDGET_SOURCES
    ${DEVICECONFIG_WIDGET_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsWidget.ui
    PARENT_SCOPE
   )