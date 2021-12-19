cmake_minimum_required(VERSION 3.0.0)
project(search)

set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wpedantic -Wextra -Werror")

option(BUILD_PARALLEL "Use parallelized search" OFF)

if (${BUILD_PARALLEL})
  add_subdirectory(parallel_lib)
  add_subdirectory(test_parallel)
else()
  add_subdirectory(serial_lib)
  add_subdirectory(test_serial)
endif()

#message("SEARCH_LIB_INCLUDE_DIRS = ${SEARCH_LIB_INCLUDE_DIRS}")
#message("SEARCH_LIB_LIBRARIES = ${SEARCH_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.cpp)

#target_include_directories(${PROJECT_NAME} PUBLIC ${SEARCH_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SEARCH_LIB_LIBRARIES})

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

