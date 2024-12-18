include(FindPackageHandleStandardArgs)

find_path(FFTW_INCLUDE_DIR NAMES fftw3.h REQUIRED)
find_library(FFTW_LIBRARY NAMES 
                               fftw3
                               libfftw3
                               fftw3-3
                               libfftw3-3
                               REQUIRED)

find_package_handle_standard_args(FFTW
 DEFAULT_MSG
  FFTW_INCLUDE_DIR
  FFTW_LIBRARY
)

mark_as_advanced(FFTW_LIBRARY
                 FFTW_INCLUDE_DIR)

if(FFTW_FOUND)
  set(FFTW_LIBRARIES    ${FFTW_LIBRARY})
  set(FFTW_INCLUDE_DIRS ${FFTW_INCLUDE_DIR})
  include_directories(${FFTW_INCLUDE_DIR} ${FFTW_INCLUDE_DIR})
  if (NOT TARGET fftw3)
    add_library(fftw3 UNKNOWN IMPORTED)
  endif()
  if (FFTW_LIBRARY)
    set_property(TARGET fftw3 APPEND PROPERTY
      IMPORTED_CONFIGURATIONS RELEASE
    )
    set_target_properties(fftw3 PROPERTIES
      IMPORTED_LOCATION_RELEASE "${FFTW_LIBRARY}"
    )
  endif()
  message("FFTW FOUND")
  message("FFTW_LIBRARIES: ${FFTW_LIBRARIES}")
  message("FFTW_INCLUDE_DIRS: ${FFTW_INCLUDE_DIRS}")
else()
  message("FFTW NOT FOUND")
endif()

