INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MFSK_DEMOD MFSK_demod)

FIND_PATH(
    MFSK_DEMOD_INCLUDE_DIRS
    NAMES MFSK_demod/api.h
    HINTS $ENV{MFSK_DEMOD_DIR}/include
        ${PC_MFSK_DEMOD_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MFSK_DEMOD_LIBRARIES
    NAMES gnuradio-MFSK_demod
    HINTS $ENV{MFSK_DEMOD_DIR}/lib
        ${PC_MFSK_DEMOD_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MFSK_DEMOD DEFAULT_MSG MFSK_DEMOD_LIBRARIES MFSK_DEMOD_INCLUDE_DIRS)
MARK_AS_ADVANCED(MFSK_DEMOD_LIBRARIES MFSK_DEMOD_INCLUDE_DIRS)

