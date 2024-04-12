cmake_minimum_required(VERSION 3.23...3.27)
project(ace)

set(ACE_IS_BEING_BUILT CMake CACHE INTERNAL "")
set(ACE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "")
if(BUILD_SHARED_LIBS)
  set(ace_static_default TRUE)
else()
  set(ace_static_default FALSE)
endif()
option(ACE_STATIC "Build ACE as static libs" "${ace_static_default}")

add_subdirectory(ace)
add_subdirectory(apps/gperf)
