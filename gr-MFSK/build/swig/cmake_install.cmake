# Install script for directory: /Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/swig

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/_MFSK_swig.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK" TYPE MODULE FILES "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/swig/_MFSK_swig.so")
  if(EXISTS "$ENV{DESTDIR}/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/_MFSK_swig.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/_MFSK_swig.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/_MFSK_swig.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/MFSK_swig.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK" TYPE FILE FILES "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/swig/MFSK_swig.py")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/MFSK_swig.pyc;/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK/MFSK_swig.pyo")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/opt/local/Library/Frameworks/Python.framework/Versions/2.7/lib/python2.7/site-packages/MFSK" TYPE FILE FILES
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/swig/MFSK_swig.pyc"
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/swig/MFSK_swig.pyo"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MFSK/MFSK/swig" TYPE FILE FILES
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/swig/MFSK_swig.i"
    "/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/swig/MFSK_swig_doc.i"
    )
endif()

