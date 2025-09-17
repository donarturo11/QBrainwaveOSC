include(FindPackageHandleStandardArgs)

find_path(FFTW3_INCLUDE_DIR NAMES fftw3.h REQUIRED)
find_library(FFTW3_LIBRARY NAMES
                               fftw3
                               libfftw3
                               fftw3-3
                               libfftw3-3
                               REQUIRED)

find_package_handle_standard_args(FFTW3
 DEFAULT_MSG
  FFTW3_INCLUDE_DIR
  FFTW3_LIBRARY
)

mark_as_advanced(FFTW3_LIBRARY
                 FFTW3_INCLUDE_DIR)

if(FFTW3_FOUND)
  set(FFTW3_LIBRARIES    ${FFTW3_LIBRARY})
  set(FFTW3_INCLUDE_DIRS ${FFTW3_INCLUDE_DIR})
  include_directories(${FFTW3_INCLUDE_DIR} ${FFTW3_INCLUDE_DIR})
  if (NOT TARGET FFTW3::fftw3)
    add_library(FFTW3::fftw3 UNKNOWN IMPORTED)
  endif()
  if (FFTW3_LIBRARY)
    set_property(TARGET FFTW3::fftw3 APPEND PROPERTY
      IMPORTED_CONFIGURATIONS RELEASE
    )
    set_target_properties(FFTW3::fftw3 PROPERTIES
      IMPORTED_LOCATION_RELEASE "${FFTW3_LIBRARY}"
    )
  endif()
else()
  message("FFTW NOT FOUND")
endif()