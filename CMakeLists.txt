# CMake master file for PSM
#
#

# Make sure they are using a recent version of CMake
cmake_minimum_required(VERSION 2.8)

# Project name
project(PSM)

# Include the macros file for this project
#include(${PROJECT_SOURCE_DIR}/cmake/macros.cmake)

# Enable ExternalProject CMake module
INCLUDE(ExternalProject)
# Set default ExternalProject root directory
set(EP_PREFIX ${CMAKE_BINARY_DIR}/dependencies)
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${EP_PREFIX})
SET( DEPENDENCIES_DIR ${CMAKE_BINARY_DIR}/dependencies)

# define the path of our additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake/Modules/)

# setup version numbers
set(PSM_VERSION_MAJOR 0)
set(PSM_VERSION_MINOR 1)
set(PSM_VERSION_PATCH 0)
set(PSM_VERSION "${MGE_VERSION_MAJOR}.${MGE_VERSION_MINOR}.${MGE_VERSION_PATCH}")

#Find external libraires
include_directories(
  "${PROJECT_SOURCE_DIR}/include"
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Build targets
SET( PSMCORE_TARGET_NAME "core")

set( PSM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set( PSM_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Properties
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# find external SFML libraries --- hmm, can make macro out of this! Too much repetition of code!
set(SFML_INSTALL_DIR ${DEPENDENCIES_DIR}/sfml/)
ExternalProject_Add(
    sfml
    GIT_REPOSITORY https://github.com/LaurentGomila/SFML.git
    TIMEOUT 10  
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SFML_INSTALL_DIR}
               -DCMAKE_CXX_FLAGS=${MSVC_COMPILER_DEFS}
               -DBUILD_SHARED_LIBS=ON
    # Wrap download, configure and build steps in a script to log output   
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

SET_PROPERTY(TARGET sfml PROPERTY FOLDER "external")

# Get include directory of external project
INCLUDE_DIRECTORIES(${SFML_INSTALL_DIR}/include)

# Get binary directory of external project
INCLUDE_DIRECTORIES(${SFML_INSTALL_DIR}/bin)
set(SFML_LIB_DIR ${SFML_INSTALL_DIR}/lib)

# External libraries easylogging
set(ELPP_INSTALL_DIR ${DEPENDENCIES_DIR}/easylogging/)
ExternalProject_Add(
    easyloggingpp
    GIT_REPOSITORY https://github.com/easylogging/easyloggingpp.git
    TIMEOUT 10  
    # Force separate output paths for debug and release builds to allow easy
    # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${ELPP_INSTALL_DIR}
    # Wrap download, configure and build steps in a script to log output   
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)

# External libraires
SET_PROPERTY(TARGET easyloggingpp PROPERTY FOLDER "external")

# Get include directory of external project
INCLUDE_DIRECTORIES(${ELPP_INSTALL_DIR}/include)

# add the PSM subdirectory
message("Configuring PSM...")
add_subdirectory(src/core)

# add the examples subdirectory
message("Configuring application...")
add_subdirectory(application)

