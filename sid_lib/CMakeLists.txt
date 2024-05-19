# Copyright 2024 m4jr0. All Rights Reserved.
# Use of this source code is governed by the MIT
# license that can be found in the LICENSE file.

################################################################################
#
# Space It library CMake file
#
################################################################################

# Source files #################################################################
target_precompile_headers(${SID_LIBRARY_NAME}
  PRIVATE
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid_precompile.h"
)

configure_file(
  "${PROJECT_SOURCE_DIR}/sid_lib/sid_lib.rc.in"
  "${CMAKE_CURRENT_BINARY_DIR}/sid_lib.rc"
  @ONLY
)

set(SID_LIB_SOURCES
  PRIVATE
    "${CMAKE_CURRENT_BINARY_DIR}/sid_lib.rc"

    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/compilers.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/debug.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/define.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/event.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/input.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/os.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/sid_lib.h"
    "${PROJECT_SOURCE_DIR}/sid_lib/include/sid/type.h"
  
    "${PROJECT_SOURCE_DIR}/sid_lib/src/allocator.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/animation.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/date.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/file_system.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/graphics.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/hash.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/hashmap.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/log.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/math.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/memory.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/resource.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/ring_queue.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/string.c"
    "${PROJECT_SOURCE_DIR}/sid_lib/src/string_id.c"
)
    
target_sources(${SID_LIBRARY_NAME}
  PRIVATE
    ${SID_LIB_SOURCES}
)

# Compiling ####################################################################
target_include_directories(${SID_LIBRARY_NAME}
  PRIVATE
    ${VCPKG_INCLUDE_DIR}
    "${PROJECT_SOURCE_DIR}/sid_lib/include/"
)

# Linking ######################################################################
target_link_directories(${SID_LIBRARY_NAME}
  PRIVATE
    "${VCPKG_LIBRARY_DIR}"
)

target_link_libraries(${SID_LIBRARY_NAME}
  PRIVATE
  # Put libraries here.
)

if(WIN32)
  target_link_libraries(${SID_LIBRARY_NAME}
    PRIVATE
      # Put libraries here.
  )
endif()

if(LINUX)
  target_link_libraries(${SID_LIBRARY_NAME}
    PRIVATE
      # Put libraries here.
  )
endif()
