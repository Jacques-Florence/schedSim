cmake_minimum_required (VERSION 3.5)
project(SchedulingSimulator)
add_subdirectory(googletest)
enable_testing()
set(CMAKE_CXX_COMPILER c++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fopenmp" )
include_directories($(gtest_SOURCE_DIR)/include $(gtest_SOURCE_DIR))
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -W -Wall -Wextra -Werror -Wfloat-equal -Wswitch-default -Wno-parentheses -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_INSTALL_PREFIX ../simulator CACHE INTERNAL "")
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} /nv/hp20/jflorence8/glpk/lib)
include_directories(/nv/hp20/jflorence8/glpk/include)
include_directories( "${PROJECT_SOURCE_DIR}" )
add_subdirectory(utils)
add_subdirectory(tinyxml2)
add_subdirectory(scheduler)
add_subdirectory(analysis)
add_subdirectory(configuration)
add_subdirectory(mdp)
add_subdirectory(mdpGovernor)
add_subdirectory(rlScheduler)
add_executable(SchedulingSimulator main.cpp)
target_link_libraries(SchedulingSimulator
	rlScheduler
	scheduler
	mdp
	utils
	tinyxml2
	glpk)
install(TARGETS SchedulingSimulator DESTINATION bin)
install(PROGRAMS run.sh runSweep.sh cleanresults.sh getMissingFiles.py convergence.py all.sh DESTINATION .)
install(DIRECTORY DESTINATION scratch)
install(DIRECTORY DESTINATION data)

add_subdirectory(xml)


