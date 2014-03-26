CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(aifc)

#--------------------------------------------------------------------------------------------------
# CMake extensions
#--------------------------------------------------------------------------------------------------
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(MSVC)
ELSEIF(COMPILER_SUPPORTS_CXX11)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
  MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
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
  "src/main.cpp"
)

SET(Include
  #"include/")
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