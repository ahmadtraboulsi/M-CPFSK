# Install script for directory: /Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK_demod/include/MFSK_demod

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MFSK_demod" TYPE FILE FILES
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK_demod/include/MFSK_demod/api.h"
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK_demod/include/MFSK_demod/MFSK_demod2.h"
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK_demod/include/MFSK_demod/MFSK_demod3.h"
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK_demod/include/MFSK_demod/symbol_timing_signal.h"
    )
endif()

