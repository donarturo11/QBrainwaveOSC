#projectName(QBrainwaveOSC)

add_subdirectory(GUI)
add_subdirectory(ThinkGear)
set(PROJECT_SOURCES
    ${GUI_SOURCES}
    ${THINKGEAR_SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    PARENT_SCOPE
   )


