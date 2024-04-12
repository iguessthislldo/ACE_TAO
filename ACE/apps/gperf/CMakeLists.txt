cmake_minimum_required(VERSION 3.23...3.27)
project(ace_gperf LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  src/gperf.cpp
  src/Options.cpp
  src/Iterator.cpp
  src/Gen_Perf.cpp
  src/Key_List.cpp
  src/List_Node.cpp
  src/Hash_Table.cpp
  src/Bool_Array.cpp
  src/Vectors.cpp
  src/Version.cpp
)
add_executable("ACE::ace_gperf" ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PRIVATE ACE)
