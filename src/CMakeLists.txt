#projectName(QBrainwaveOSC)

add_subdirectory(GUI)
add_subdirectory(QBrainwaveInterface)
add_subdirectory(QThinkGear)
add_subdirectory(OSCSender)
set(PROJECT_SOURCES
    ${GUI_SOURCES}
    ${QTHINKGEAR_SOURCES}
    ${QBRAINWAVEINTERFACE_SOURCES}
    ${OSCSENDER_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
   )


