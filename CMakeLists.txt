CMAKE_MINIMUM_REQUIRED(VERSION 2.8.11)

PROJECT(aifc)

# Use C++11 where appropriate
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR
   "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()

SET(Source
  "src/main.cpp"
)

SET(Include
  #"include/")
)

ADD_EXECUTABLE(aifc
  ${Source}
  ${Include})