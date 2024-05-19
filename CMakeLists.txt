# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

# ###############################################################################
#
# Main CMake file
#
# ###############################################################################

cmake_minimum_required(VERSION 3.21)

# CMake setup ##################################################################
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE on)

# Generic builds.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Multi-config builds.
if(NOT DEFINED CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES "Debug;Release;MinSizeRel;RelWithDebInfo" CACHE STRING "Available build configurations" FORCE)
endif()

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR})
endforeach()

# Global variables #############################################################
set(SID_COMPANY_NAME "Comet Games")
set(SID_PRODUCT_NAME "Space it, Dummy!")
set(SID_LIBRARY_HUMAN_NAME "Space it Lib")
set(SID_LIBRARY_DESCRIPTION "Library for the ${SID_PRODUCT_NAME} game")

# Executables & Libraries.
set(SID_LIBRARY_NAME "sid_lib")

if(NOT SID_IS_LIB_BUILD_ONLY)
  set(SID_EXECUTABLE_NAME "space_it")
endif()

# Other.
set(MESSAGE_PREFIX "[SID] ")
set(VCPKG_REPO "https://github.com/Microsoft/vcpkg.git")

# Build type.
if(NOT DEFINED CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "${MESSAGE_PREFIX}Build type: ${CMAKE_BUILD_TYPE}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_compile_definitions(SID_DEBUG)
endif()

# OS specifics #################################################################
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Vcpkg setup ##################################################################
string(TOLOWER ${CMAKE_BUILD_TYPE} VCPKG_BUILD_TYPE)
message(STATUS "${MESSAGE_PREFIX}Vcpkg Build type: ${CMAKE_BUILD_TYPE}")
set(ENV{VCPKG_FEATURE_FLAGS} "versions")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(NOT DEFINED VCPKG_ROOT)
    if(NOT DEFINED ENV{VCPKG_ROOT})
      message(FATAL_ERROR
        "${MESSAGE_PREFIX}CMAKE_TOOLCHAIN_FILE and VCPKG_ROOT are not set. "
        "Please define at least VCPKG_ROOT to your Vcpkg root directory. "
        "Aborting.")
    else()
      set(VCPKG_ROOT $ENV{VCPKG_ROOT})
    endif()
  endif()

  if(NOT EXISTS ${VCPKG_ROOT})
    if(NOT DEFINED IS_VCPKG_CLONE OR NOT IS_VCPKG_CLONE)
      message(FATAL_ERROR
       "${MESSAGE_PREFIX}Vcpkg does not exist at ${VCPKG_ROOT} and boolean "
       "IS_VCPKG_CLONE is not set to TRUE. Aborting.")
    endif()

    message(STATUS "${MESSAGE_PREFIX}Cloning Vcpkg in ${VCPKG_ROOT}...")
    execute_process(COMMAND git clone ${VCPKG_REPO} ${VCPKG_ROOT})
  else()
    message(STATUS "${MESSAGE_PREFIX}Updating Vcpkg at ${VCPKG_ROOT}...")
    execute_process(COMMAND git pull --ff-only WORKING_DIRECTORY ${VCPKG_ROOT})
  endif()

  if(WIN32)
   set(VCPKG_BIN ${VCPKG_ROOT}/vcpkg.exe)
   set(VCPKG_BOOTSTRAP_SCRIPT ${VCPKG_ROOT}/bootstrap-vcpkg.bat)
  else()
   set(VCPKG_BIN ${VCPKG_ROOT}/vcpkg)
   set(VCPKG_BOOTSTRAP_SCRIPT ${VCPKG_ROOT}/bootstrap-vcpkg.sh)
  endif()

  if(NOT EXISTS ${VCPKG_BIN})
    message(STATUS "${MESSAGE_PREFIX}Bootstrapping Vcpkg in ${VCPKG_ROOT}...")
    execute_process(
      COMMAND ${VCPKG_BOOTSTRAP_SCRIPT} WORKING_DIRECTORY ${VCPKG_ROOT}
    )
  endif()

  if(NOT EXISTS ${VCPKG_BIN})
    message(FATAL_ERROR
      "${MESSAGE_PREFIX}Something wrong happened while boostrapping Vcpkg. "
      "Aborting.")
  endif()

  if(WIN32)
    execute_process(
      COMMAND ${VCPKG_BIN} integrate install
    )
  endif()

  if(WIN32)
    set(CMAKE_TOOLCHAIN_FILE
      "${VCPKG_ROOT}\\scripts\\buildsystems\\vcpkg.cmake")
  else()
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
  endif()

  message(STATUS "${MESSAGE_PREFIX}CMAKE_TOOLCHAIN_FILE set to"
    " \"${CMAKE_TOOLCHAIN_FILE}\".")
endif()

# CMAKE_TOOLCHAIN_FILE might contain backslashes as path separators,
# which can be interpreted as escape characters...
if(WIN32)
  file(TO_CMAKE_PATH "${CMAKE_TOOLCHAIN_FILE}" CMAKE_TOOLCHAIN_FILE)
endif()

# Project ######################################################################
message(STATUS
  "${MESSAGE_PREFIX}Building ${CMAKE_PROJECT_NAME} "
  "to ${CMAKE_CURRENT_BINARY_DIR}...")

project("space_it"
  VERSION 0.1.0
  DESCRIPTION "A minimalist 2D fighting game coded in C, focused on spacing"
  LANGUAGES C
)

option(SID_IS_LIB_BUILD_ONLY "Build only the library" FALSE)

# Compiler specifics.
if(MSVC)
  # Disable any non-conformant code with Microsoft Visual C++.
  # As to why W4 is used: https://stackoverflow.com/questions/4001736/whats-up-with-the-thousands-of-warnings-in-standard-headers-in-msvc-wall#comment8922238_4001759
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /permissive- /W4 /WX")
else()
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -Werror")
endif()

if(SID_DEBUG_RELEASE)
  if(MSVC)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Zi")
    add_link_options("/INCREMENTAL:NO" "/DEBUG" "/OPT:REF" "/OPT:ICF")
  else()
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g -DNDEBUG")
  endif()
endif()

set(SID_NAME ${CMAKE_PROJECT_NAME})
string(REPLACE "." ";" VERSION_LIST "${PROJECT_VERSION}")
list(GET VERSION_LIST 0 SID_VERSION_MAJOR)
list(GET VERSION_LIST 1 SID_VERSION_MINOR)
list(GET VERSION_LIST 2 SID_VERSION_PATCH)

add_library(${SID_LIBRARY_NAME} OBJECT ${SID_LIB_SOURCES})

if(UNIX)
  target_compile_options(${SID_LIBRARY_NAME} PRIVATE "-fvisibility=hidden")
endif()

if(NOT SID_IS_LIB_BUILD_ONLY)
  add_executable(${SID_EXECUTABLE_NAME} ${SID_GAME_SOURCES})
endif()

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

if(NOT SID_IS_LIB_BUILD_ONLY)
  target_compile_definitions(${CMAKE_PROJECT_NAME}
    PUBLIC
      SID_NAME="${SID_NAME}"
      SID_VERSION_MAJOR=${SID_VERSION_MAJOR}
      SID_VERSION_MINOR=${SID_VERSION_MINOR}
      SID_VERSION_PATCH=${SID_VERSION_PATCH}
  )
endif()

# Vcpkg variables ##############################################################
set(VCPKG_BASE_DIR "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}")
set(VCPKG_INCLUDE_DIR "${VCPKG_BASE_DIR}/include")
set(VCPKG_LIBRARY_DIR "${VCPKG_BASE_DIR}/lib")

# Subdirectories ###############################################################
add_subdirectory("${PROJECT_SOURCE_DIR}/sid_lib")

if(NOT SID_IS_LIB_BUILD_ONLY)
  add_subdirectory("${PROJECT_SOURCE_DIR}/src")
endif()

add_library("${SID_LIBRARY_NAME}_static"
  STATIC
    $<TARGET_OBJECTS:${SID_LIBRARY_NAME}>)

set_target_properties("${SID_LIBRARY_NAME}_static"
  PROPERTIES
    OUTPUT_NAME ${SID_LIBRARY_NAME}
)

add_library("${SID_LIBRARY_NAME}_shared"
  SHARED
    $<TARGET_OBJECTS:${SID_LIBRARY_NAME}>
)

set_target_properties("${SID_LIBRARY_NAME}_shared" 
  PROPERTIES
    OUTPUT_NAME ${SID_LIBRARY_NAME}
    POSITION_INDEPENDENT_CODE ON
)

set_target_properties("${SID_LIBRARY_NAME}" 
  PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)

message(STATUS "${MESSAGE_PREFIX}Done.")
