cmake_minimum_required(VERSION 3.22)
project(peakDetector VERSION 1.0.0 LANGUAGES CXX C)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set (MAIN_ROOT ${PROJECT_SOURCE_DIR}/../../)

find_package(Boost REQUIRED)

include_directories(
   ${MAIN_ROOT}/thirdparty/neurosky/lib/MinSet_Dev_tools/ThinkGear
   )

add_library(tgparser STATIC
  ${MAIN_ROOT}/thirdparty/neurosky/lib/MinSet_Dev_tools/ThinkGear/ThinkGearStreamParser.c
            )
add_library(thinkgear_core STATIC
      ${MAIN_ROOT}/src/QThinkGear/TGData.cpp
            )
include_directories(
   ${MAIN_ROOT}/src/QThinkGear/
   )

set (SOURCES
     ${PROJECT_SOURCE_DIR}/
     main.cpp
     PeakDetector.cpp
    )
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC thinkgear_core)
target_link_libraries(${PROJECT_NAME} PUBLIC tgparser)
target_link_libraries(${PROJECT_NAME} PUBLIC Boost::boost)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
