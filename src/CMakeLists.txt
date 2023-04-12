#projectName(QBrainwaveOSC)

add_subdirectory(GUI)
add_subdirectory(QThinkGear)
set(PROJECT_SOURCES
    ${GUI_SOURCES}
    ${QTHINKGEAR_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
   )


