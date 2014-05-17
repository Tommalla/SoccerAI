cmake_minimum_required(VERSION 2.8.9)

project(SoccerAI)

set (BASE_FLAGS "-Wall -std=c++11")
set (RELEASE_FLAGS "-O2 -DNDEBUG")
set (DEBUG_FLAGS "-ggdb -pg")
set (EVOLUTION_FLAGS "${RELEASE_FLAGS} -pthread -DNDEBUG")

set (FINAL_FLAGS "${BASE_FLAGS} ${EVOLUTION_FLAGS}")

set (CMAKE_CXX_FLAGS "${FINAL_FLAGS}")

set (EXECUTABLE_OUTPUT_PATH "${SoccerAI_BINARY_DIR}/bin")

add_subdirectory(src)