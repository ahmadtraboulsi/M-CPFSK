INCLUDE(FindPkgConfig)
PKG_CHECK_MODULES(PC_MFSK MFSK)

FIND_PATH(
    MFSK_INCLUDE_DIRS
    NAMES MFSK/api.h
    HINTS $ENV{MFSK_DIR}/include
        ${PC_MFSK_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    MFSK_LIBRARIES
    NAMES gnuradio-MFSK
    HINTS $ENV{MFSK_DIR}/lib
        ${PC_MFSK_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MFSK DEFAULT_MSG MFSK_LIBRARIES MFSK_INCLUDE_DIRS)
MARK_AS_ADVANCED(MFSK_LIBRARIES MFSK_INCLUDE_DIRS)

