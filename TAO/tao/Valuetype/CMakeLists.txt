cmake_minimum_required(VERSION 3.23...3.27)
project(libtao_valuetype LANGUAGES CXX)

include(GNUInstallDirs)

if(NOT "${_TAO_CMAKE_DIR}" IN_LIST CMAKE_MODULE_PATH)
  list(APPEND CMAKE_MODULE_PATH "${_TAO_CMAKE_DIR}")
endif()
include(tao_idl)

set(TAO_INCLUDE_DIR "${TAO_SOURCE_DIR}" CACHE INTERNAL "")

add_library(TAO_Valuetype
  AbstractBase.cpp
  AbstractBase_Invocation_Adapter.cpp
  AbstractBase_T.cpp
  ValueBase.cpp
  ValueFactory.cpp
  ValueFactory_Map.cpp
  Valuetype_Adapter_Factory_Impl.cpp
  Valuetype_Adapter_Impl.cpp
  Value_VarOut_T.cpp
)
add_library(TAO::Valuetype ALIAS TAO_Valuetype)
target_link_libraries(TAO_Valuetype PUBLIC TAO)

_tao_idl(
  TAO_Valuetype
  INCLUDE_BASE "${TAO_SOURCE_DIR}"
  IDL_FLAGS -SS -Sorb -GA -iC tao/Valuetype
  IDL_FILES StringValue.pidl
)

_tao_get_generated_output_dir(TAO_Valuetype gen_dir)
target_include_directories(TAO_Valuetype PRIVATE "${TAO_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" "${gen_dir}/tao")
target_include_directories(TAO_Valuetype SYSTEM INTERFACE "${TAO_SOURCE_DIR}")
