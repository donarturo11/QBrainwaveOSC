#projectName(QBrainwaveOSC)

set(BLUETOOTHMANAGER_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/BluetoothManager.h
   ${CMAKE_CURRENT_SOURCE_DIR}/BluetoothManager.cpp
   )

set(DEVICEDISCOVERY_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceDiscovery.h
   ${CMAKE_CURRENT_SOURCE_DIR}/DeviceDiscovery.cpp
   )

set(SERVICEDISCOVERY_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/ServiceDiscovery.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ServiceDiscovery.cpp
   )

set(RFCOMMLISTENER_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/RfcommListener.h
   ${CMAKE_CURRENT_SOURCE_DIR}/RfcommListener.cpp
   )

set(BLUETOOTHINTERFACE_SOURCES
    ${BLUETOOTHMANAGER_SOURCES}
    ${DEVICEDISCOVERY_SOURCES}
    ${SERVICEDISCOVERY_SOURCES}
    ${RFCOMMLISTENER_SOURCES}
    PARENT_SCOPE
   )


