cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(WR)
  
include(CheckCXXCompilerFlag)
include(CheckCXXSourceCompiles)
include(CheckIncludeFile)
include(CheckIncludeFiles)
include(CheckTypeSize)
  
find_package(CopperSpice REQUIRED)
 
set(PACKAGE "WR")
set(PACKAGE_NAME "WR")
  
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_DIRECTORIES_BEFORE ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
  
# location for building binary files
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
  
add_subdirectory(src)

cs_copy_plugins(CsGui)