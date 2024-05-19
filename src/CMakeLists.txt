# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# Space It CMake file
#
################################################################################

# Packages #####################################################################
find_package(SDL2 REQUIRED)

if(WIN32)
  # This is not needed on Linux.
  find_package(SDL2_IMAGE REQUIRED)
else()
  # This is not needed on Windows.
  find_package(SDL2 CONFIG REQUIRED)
endif()

# Source files #################################################################
set(SID_GAME_SOURCES
  "${PROJECT_SOURCE_DIR}/src/config.c"
  "${PROJECT_SOURCE_DIR}/src/game.c"
  "${PROJECT_SOURCE_DIR}/src/main.c"
  
  "${PROJECT_SOURCE_DIR}/src/system/animation_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/event_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/input_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/memory_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/physics_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/rendering_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/resource_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/scene_system.c"
  "${PROJECT_SOURCE_DIR}/src/system/time_system.c"
)
    
target_sources(${SID_EXECUTABLE_NAME}
  PRIVATE
    ${SID_GAME_SOURCES}
)

# Compiling ####################################################################
target_include_directories(${SID_EXECUTABLE_NAME}
  PRIVATE
    ${VCPKG_INCLUDE_DIR}
    "${PROJECT_SOURCE_DIR}/sid_lib/include/"
    "${PROJECT_SOURCE_DIR}/src/"
)

target_link_libraries(${SID_EXECUTABLE_NAME}
  PRIVATE
    SDL2::SDL2
    ${SID_LIBRARY_NAME}
)

if(WIN32)
  target_link_libraries(${SID_EXECUTABLE_NAME}
    PRIVATE
      SDL2_image::SDL2_image
  )
endif()

if(LINUX)
  target_link_libraries(${SID_EXECUTABLE_NAME}
    PRIVATE
      # Put libraries here.
  )
endif()
