cmake_minimum_required(VERSION 3.23...3.27)
project(tao_anytypecode LANGUAGES CXX)

include(GNUInstallDirs)

# if(NOT "${_TAO_CMAKE_DIR}" IN_LIST CMAKE_MODULE_PATH)
#   list(APPEND CMAKE_MODULE_PATH "${_TAO_CMAKE_DIR}")
# endif()
# include(tao_idl)

add_library(TAO_AnyTypeCode
  # Alias_TypeCode.cpp
  Alias_TypeCode_Static.cpp
  Any.cpp
  # Any_Array_Impl_T.cpp
  Any_Basic_Impl.cpp
  # Any_Basic_Impl_T.cpp
  # Any_Dual_Impl_T.cpp
  Any_Impl.cpp
  # Any_Impl_T.cpp
  # Any_Special_Impl_T.cpp
  Any_SystemException.cpp
  Any_Unknown_IDL_Type.cpp
  AnyTypeCode_Adapter_Impl.cpp
  append.cpp
  BasicTypeTraits.cpp
  Empty_Param_TypeCode.cpp
  # Enum_TypeCode.cpp
  Enum_TypeCode_Static.cpp
  ExceptionA.cpp
  # Fixed_TypeCode.cpp
  Indirected_Type_TypeCode.cpp
  Marshal.cpp
  NVList.cpp
  NVList_Adapter_Impl.cpp
  # Objref_TypeCode.cpp
  Objref_TypeCode_Static.cpp
  # Recursive_Type_TypeCode.cpp
  # Sequence_TypeCode.cpp
  Sequence_TypeCode_Static.cpp
  skip.cpp
  # String_TypeCode.cpp
  String_TypeCode_Static.cpp
  # Struct_TypeCode.cpp
  Struct_TypeCode_Static.cpp
  SystemExceptionA.cpp
  True_RefCount_Policy.cpp
  TypeCode.cpp
  # TypeCode_Base_Attributes.cpp
  # TypeCode_Case_Base_T.cpp
  # TypeCode_Case_Enum_T.cpp
  # TypeCode_Case_T.cpp
  TypeCode_CDR_Extraction.cpp
  TypeCode_Constants.cpp
  TypeCodeA.cpp
  # Union_TypeCode.cpp
  Union_TypeCode_Static.cpp
  # Value_TypeCode.cpp
  Value_TypeCode_Static.cpp
  WrongTransactionA.cpp
)
add_library(TAO::AnyTypeCode ALIAS TAO_AnyTypeCode)
target_link_libraries(TAO_AnyTypeCode PUBLIC TAO)
