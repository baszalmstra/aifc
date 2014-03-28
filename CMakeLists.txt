CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(aifc)

#--------------------------------------------------------------------------------------------------
# CMake extensions
#--------------------------------------------------------------------------------------------------
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
ENDIF()

#--------------------------------------------------------------------------------------------------
# Setup Dependencies
#--------------------------------------------------------------------------------------------------
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED)
FIND_PACKAGE(SDL2_image REQUIRED)

#--------------------------------------------------------------------------------------------------
# Setup source files
#--------------------------------------------------------------------------------------------------
SET(Source
  "src/application.cpp"
  "src/application.h"
  "src/battle.h"
  "src/battle.cc"
  "src/color.h"
  "src/faction_state.cpp"
  "src/faction_state.h"
  "src/main.cpp"
  "src/plugin_wrapper.cpp"
  "src/plugin_wrapper.h"
  "src/ship_state.cpp"
  "src/ship_state.h"
)

SET(Include
  "include/math_types.h"
  "include/ai_command.h"
  "include/ai_input.h"
  "include/ship_info.h"
  "include/float2.h"
  "include/ship_description.h"
  "include/thruster_description.h"
  "include/ai/i_ai.h"
  "include/ai/i_ai_plugin.h"
)

INCLUDE_DIRECTORIES(
  "include"
  ${SDL2_INCLUDE_DIR}
  ${SDL2_IMAGE_INCLUDE_DIRS})

#--------------------------------------------------------------------------------------------------
# Setup project
#--------------------------------------------------------------------------------------------------
ADD_EXECUTABLE(aifc
  ${Source}
  ${Include})

#--------------------------------------------------------------------------------------------------
# Setup project dependencies
#--------------------------------------------------------------------------------------------------
TARGET_LINK_LIBRARIES(aifc
  ${SDL2_LIBRARY}
  ${SDL2_IMAGE_LIBRARIES}
  ${OPENGL_gl_LIBRARY})

#--------------------------------------------------------------------------------------------------
# Test AI
#--------------------------------------------------------------------------------------------------
ADD_LIBRARY(testai SHARED test/testai.cpp test/testai.h test/ai_plugin.cpp test/ai_plugin.h)
