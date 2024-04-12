cmake_minimum_required(VERSION 3.23...3.27)
project(tao)

set(TAO_IS_BEING_BUILT CMake CACHE INTERNAL "")
set(TAO_SOURCE_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")
set(_TAO_CMAKE_DIR "${TAO_SOURCE_DIR}/cmake" CACHE INTERNAL "")

add_subdirectory(TAO_IDL)
add_subdirectory(tao)
# add_subdirectory(tao/AnyTypeCode)
add_subdirectory(tao/Valuetype)
