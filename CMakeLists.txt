cmake_minimum_required(VERSION 2.8)
project(POROSBIN)

set(PROJECT_NAME "porosbin")
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

if (DEFINED DEBUG)
  add_definitions(-DDEBUG=${DEBUG})
  set(CMAKE_BUILD_TYPE Debug)
  message("Building a debug release")
else()
  set(CMAKE_BUILD_TYPE Release)
  message("Building an optimized release")
endif()

# set up types
add_definitions(-DWILDRIVER_INDEX_TYPE=uint32_t)
add_definitions(-DWILDRIVER_DIMENSION_TYPE=uint32_t)
add_definitions(-DWILDRIVER_VALUE_TYPE=uint32_t)

# on mac
# add_definitions(-DHAVE_TYPE_TRAITS=1)

if (DEFINED DEVEL AND NOT DEVEL EQUAL 0)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weffc++") 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic") 
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# must be before including src
if (DEFINED TESTS AND NOT TESTS EQUAL 0)
  enable_testing()
endif()

add_subdirectory("wildriver")

include_directories("wildriver/include")

add_subdirectory("poros")

include_directories("poros/include")

add_subdirectory("src")


