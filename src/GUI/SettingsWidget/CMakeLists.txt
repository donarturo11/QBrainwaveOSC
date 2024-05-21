#projectName(QBrainwaveOSC)

add_subdirectory(DeviceSettings)

set(DEVICECONFIG_WIDGET_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionWidget.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionWidget.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/ConnectionWidget.ui
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceSettingsWidget.h
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceSettingsWidget.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceSettingsWidget.ui
   ${DEVICESETTINGS_SOURCES}
   )

set(OSCCONFIG_WIDGET_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/OSCConfiguration.h
   ${CMAKE_CURRENT_SOURCE_DIR}/OSCConfiguration.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/OSCConfiguration.ui
   )
set(SETTINGS_WIDGET_SOURCES
    ${DEVICECONFIG_WIDGET_SOURCES}
    ${OSCCONFIG_WIDGET_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsWidget.h
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsWidget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/SettingsWidget.ui
    PARENT_SCOPE
   )