cmake_minimum_required(VERSION 3.5)

project(QBrainwaveOSC VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include_directories(
   ${PROJECT_SOURCE_DIR}/src
   ${PROJECT_SOURCE_DIR}/src/MainWindow
   ${PROJECT_SOURCE_DIR}/src/MainWindow/SettingsWidget
   ${PROJECT_SOURCE_DIR}/src/MainWindow/MonitorWidget
)

option(FORCE_QT5 "Force qt5 install" OFF)
option(FORCE_QT6 "Force qt6 install" OFF)

if(FORCE_QT5)
    set(QT_VERSION_MAJOR 5)
    find_package(Qt5 REQUIRED COMPONENTS Core Widgets Bluetooth)
elseif(FORCE_QT6)
    set(QT_VERSION_MAJOR 6)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Bluetooth)
else()
    find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Bluetooth)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Bluetooth)
endif()

if (${QT_VERSION_MAJOR} EQUAL 5)
add_compile_definitions(QT5)
elseif (${QT_VERSION_MAJOR} EQUAL 6)
add_compile_definitions(QT6)
endif()

add_subdirectory(src)

# set icon
if(APPLE)
    set(APP_ICON_MACOSX "${CMAKE_CURRENT_SOURCE_DIR}/desktop/AppIcon.icns")
    set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES
           MACOSX_PACKAGE_LOCATION "Resources")
    set(RESOURCES ${RESOURCES} ${APP_ICON_MACOSX})
elseif(WIN32)
    enable_language("RC")
    set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/desktop/AppIcon.rc")
    set(RESOURCES ${RESOURCES} ${APP_ICON_RESOURCE_WINDOWS})
endif()

set(PROJECT_SOURCES
        ${RESOURCES}
        ${MAINWINDOW_SOURCES}
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    )


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(${PROJECT_NAME} SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${PROJECT_NAME}
            ${PROJECT_SOURCES}
        )
    endif()
endif()

IF(WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
ELSEIF(APPLE)
    set_property(TARGET ${PROJECT_NAME} PROPERTY MACOSX_BUNDLE true)
    set_target_properties(${PROJECT_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER org.donarturo11.${PROJECT_NAME}.com
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_ICON_FILE AppIcon.icns
    INSTALL_RPATH @executable_path/../Frameworks
    )
ENDIF()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Bluetooth)

if(MINGW)
    message("Installing for Mingw")
    include(GNUInstallDirs)
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_NAME}/lib/archive)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_NAME}/lib)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_NAME})
    install(FILES desktop/AppIcon.ico DESTINATION ${PROJECT_NAME})
elseif(UNIX AND (NOT APPLE))
    message("Installing for UNIX")
    include(GNUInstallDirs)
    set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
    set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
    install(FILES desktop/AppIcon.png RENAME ${PROJECT_NAME}.png DESTINATION ${CMAKE_INSTALL_PREFIX}/share/icons/hicolor/128/apps)
    install(FILES desktop/${PROJECT_NAME}.desktop DESTINATION ${CMAKE_INSTALL_PREFIX}/share/applications)
elseif(APPLE)
    message("Installing for macOS")
    install(FILES desktop/AppIcon.icns DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app/Contents/Resources)
endif()

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(CPackConfig)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif()
