message("CMAKE_BINARY_DIR=${CMAKE_BINARY_DIR}")
message("CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message("CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY=${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR donarturo11)
set(CPACK_PACKAGE_DESCRIPTION "Simple program to training temperament systems")
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
#set(CPACK_PACKAGE_ICON ${CMAKE_SOURCE_DIR}/desktop/AppIcon.ico)
#set(CPACK_INSTALLED_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME};/")
#set(CPACK_SET_DESTDIR "ON")
set(CPACK_PACKAGING_INSTALL_PREFIX "")
if (APPLE)
    set(CPACK_GENERATOR Bundle)
    set(CPACK_BUNDLE_NAME ${PROJECT_NAME})
    set(CPACK_BUNDLE_PLIST Contents/Info.plist)
    set(CPACK_BUNDLE_ICON_FILE Contents/Resources/AppIcon.icns)
    set(CPACK_BUNDLE_ICON Contents/Resources/AppIcon.icns)
    set(CPACK_BUNDLE_APPLE_CERT_APP "donarturo11.github.io")
    set(CPACK_BUNDLE_APPLE_ENTITLEMENTS "desktop/entitlements.plist")
    #set(CPACK_BUNDLE_APPLE_CODESIGN_PARAMETER "-d -v -f")
elseif(WIN32)
    set(CPACK_GENERATOR 7Z NSIS)
    set(CPACK_INSTALLED_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/;/")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
    set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-installer")
    set(CPACK_ARCHIVE_FILE_NAME "${PROJECT_NAME}-Portable")
    set(CPACK_NSIS_DISPLAY_NAME "${PROJECT_NAME}")
    set(CPACK_NSIS_INSTALLED_ICON_NAME "${CMAKE_SOURCE_DIR}/desktop/AppIcon.ico")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/donarturo11/${PACKAGE_NAME}")
    set(CPACK_NSIS_ADD_REMOVE ON)
    set(CPACK_NSIS_INSTALLED_ICON_NAME ${PROJECT_NAME}/${PROJECT_NAME}.exe)
    
    set(CPACK_NSIS_FILE_NAME "${PROJECT_NAME}-installer")
    set(CPACK_NSIS_PACKAGE_NAME "${PROJECT_NAME}")
    if(MINGW)
       set(CPACK_NSIS_EXECUTABLE $ENV{MSYSTEM_PREFIX}/bin/makensis.exe)
    endif()
elseif(UNIX AND NOT APPLE)
    set(CPACK_GENERATOR TGZ)
endif()
include(CPack)
