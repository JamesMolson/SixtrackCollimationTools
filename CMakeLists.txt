# force an out of source build to stop clutter
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
	message(STATUS "Tools require an out-of-source build.")
	message(STATUS "Please remove these files from ${CMAKE_BINARY_DIR} first:")
	message(STATUS "CMakeCache.txt")
	message(STATUS "CMakeFiles")
	message(STATUS "Once these files are removed, create a separate directory")
	message(STATUS "and run CMake from there")
	message(FATAL_ERROR "in-source build detected")
endif()

#Set the cmake version required
cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)

# Set the project name and options
PROJECT(BEAMLOSSPATTERN)

OPTION(ENABLE_SURVEY "Enable survey. Default ON" ON)
OPTION(ENABLE_CROSSING "Enable crossing. Default OFF" OFF)
OPTION(ENABLE_SAVELOST "Save the trajectories of the last turn of lost particles. Default OFF" OFF)

#Set version info
set(${PROJECT_NAME}_VERSION “2.0.0”)
set(${PROJECT_NAME}_VERSION_MAJOR “2”)
set(${PROJECT_NAME}_VERSION_MINOR “0”)
set(${PROJECT_NAME}_VERSION_PATCH "0")

#Add the source and includes
include_directories(${BEAMLOSSPATTERN_SOURCE_DIR}/SixtrackCollimationTools/)

#Additional Compiler flags
ADD_DEFINITIONS("-Wall -Wextra -pedantic")

#ENABLE_SURVEY
if(ENABLE_SURVEY)
	ADD_DEFINITIONS("-DENABLE_SURVEY")
endif(ENABLE_SURVEY)

#ENABLE_CROSSING
if(ENABLE_CROSSING)
	ADD_DEFINITIONS("-DENABLE_CROSSING")
endif(ENABLE_CROSSING)

#ENABLE_SAVELOST
if(ENABLE_SAVELOST)
	ADD_DEFINITIONS("-DENABLE_SAVELOST")
endif(ENABLE_SAVELOST)

add_subdirectory(SixtrackCollimationTools)
